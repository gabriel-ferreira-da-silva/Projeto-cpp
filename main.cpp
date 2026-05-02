#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <chrono>
#include "utils/Scene/sceneSchema.hpp"
#include "utils/Scene/sceneParser.cpp"
#include "src/Camera.h"
#include "src/Geometry.h"



int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <caminho_para_cena.json> > saida.ppm" << std::endl;
        return 1;
    }
    
    std::string scene_file = argv[1];
    
    SceneData scene_data;
    try {
        scene_data = SceneJsonLoader::loadFile(scene_file);
        std::cerr << "Arquivo carregado com sucesso!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao carregar o arquivo: " << e.what() << std::endl;
        return 1;
    }
    
    Camera cam(scene_data.camera);
    
    std::cout << "P3" << std::endl;
    std::cout << cam.getWidth() << " " << cam.getHeight() << std::endl;
    std::cout << "255" << std::endl;
    
    auto start_time = std::chrono::high_resolution_clock::now();
    
    for (int j = 0; j < cam.getHeight(); j++) {
        std::cerr << "Renderizando linha " << j << "/" << cam.getHeight() << "..." << "\r";
        std::cerr.flush();
        
        for (int i = 0; i < cam.getWidth(); i++) {
            Vetor ray_dir = cam.getRayDirection(i, j);
            
            double closest_t = INF;
            ColorData hit_color;
            bool hit_anything = false;
            
            // IMPORTANTE: remova o 'const' aqui se não for necessário
            // ou mantenha e use cópias
            for (const auto& obj : scene_data.objects) {
                double t = INF;
                
                if (obj.objType == "sphere") {
                    Ponto centro = obj.relativePos;
                    // Faça uma cópia segura dos dados
                    double raio = 0.0;
                    if (obj.numericData.find("radius") != obj.numericData.end()) {
                        raio = obj.numericData.at("radius");  // at() é const, operator[] não é
                    }
                    t = intersect_sphere(cam.getCameraPosition(), ray_dir, centro, raio);
                    
                } else if (obj.objType == "plane") {
                    Ponto ponto_plano = obj.relativePos;
                    Vetor normal;
                    
                    // Use find e at() que são const-correct
                    if (obj.vetorPointData.find("normal") != obj.vetorPointData.end()) {
                        normal = obj.vetorPointData.at("normal");
                    } else if (obj.vetorPointData.find("direction") != obj.vetorPointData.end()) {
                        normal = obj.vetorPointData.at("direction");
                    } else {
                        normal = Vetor(0, 1, 0);
                    }
                    
                    normal = normal.normalize();
                    t = intersect_plane(cam.getCameraPosition(), ray_dir, ponto_plano, normal);
                }
                
                if (t < closest_t) {
                    closest_t = t;
                    hit_color = obj.material.color;
                    hit_anything = true;
                }
            }
            
            if (hit_anything) {
                int r = static_cast<int>(255.999 * hit_color.r);
                int g = static_cast<int>(255.999 * hit_color.g);
                int b = static_cast<int>(255.999 * hit_color.b);
                
                r = std::max(0, std::min(255, r));
                g = std::max(0, std::min(255, g));
                b = std::max(0, std::min(255, b));
                
                std::cout << r << " " << g << " " << b << std::endl;
            } else {
                std::cout << "0 0 0" << std::endl;
            }
        }
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    
    std::cerr << std::endl << "Renderização concluída com sucesso!" << std::endl;
    std::cerr << "Tempo total: " << duration.count() << " segundos" << std::endl;
    
    return 0;
}