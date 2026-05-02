#ifndef CAMERA_H
#define CAMERA_H

#include "Ponto.h"
#include "Vetor.h"
#include "/home/gab/Desktop/faculdade/pg/projeto-cpp/Projeto-cpp/utils/Scene/sceneSchema.hpp"  // Inclui a definição de CameraData

class Camera {
public:
    /**
     * Representa uma câmera pinhole para ray casting.
     * Construtor recebe diretamente a struct CameraData
     */
    Camera(const CameraData& cam_data);

    /**
     * Calcula a direção do raio correspondente ao pixel (i, j)
     */
    Vetor getRayDirection(int i, int j) const;

    // Getters (úteis para debug)
    const Ponto& getCameraPosition() const { return C; }
    const Ponto& getLookAt() const { return M; }
    const Vetor& getUpVector() const { return Vup; }
    const Vetor& getU() const { return U; }
    const Vetor& getV() const { return V; }
    const Vetor& getW() const { return W; }
    double getScreenDistance() const { return d; }
    int getWidth() const { return hres; }
    int getHeight() const { return vres; }

private:
    // Parâmetros da câmera
    Ponto C;        // Posição da câmera (lookfrom)
    Ponto M;        // Ponto para onde a câmera olha (lookat)
    Vetor Vup;      // Vetor "para cima"
    double d;       // Distância até o plano de projeção
    
    int hres;       // Resolução horizontal (largura)
    int vres;       // Resolução vertical (altura)
    
    // Base ortonormal da câmera
    Vetor U;        // Eixo horizontal (direita)
    Vetor V;        // Eixo vertical (cima)
    Vetor W;        // Eixo de profundidade (oposto à direção de visão)
    
    // Parâmetros do plano de imagem
    double pixel_size;      // Tamanho de cada pixel em unidades do mundo
    Ponto screen_center;    // Centro do plano de projeção
    Ponto upper_left;       // Canto superior esquerdo da tela
};

#endif // CAMERA_H