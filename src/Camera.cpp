#include "Camera.h"
#include <cmath>

Camera::Camera(const CameraData& cam_data)
    : C(cam_data.lookfrom), 
      M(cam_data.lookat), 
      Vup(cam_data.upVector), 
      d(cam_data.screen_distance),
      hres(cam_data.image_width), 
      vres(cam_data.image_height) {
    
    // Calcula o vetor W (oposto à direção de visão)
    // No código Python: direcao_w = self.C - self.M
    Vetor direcao_w = C - M;
    W = direcao_w.normalize();
    
    // Calcula o vetor U (horizontal/direita)
    // No código Python: direcao_u = self.Vup.cross(self.W)
    Vetor direcao_u = Vup.cross(W);
    U = direcao_u.normalize();
    
    // Calcula o vetor V (vertical/cima)
    // No código Python: self.V = self.W.cross(self.U)
    V = W.cross(U);
    
    // Tamanho do pixel (largura da tela = 1.0)
    pixel_size = 1.0 / hres;
    double screen_width = 1.0;
    double screen_height = vres * pixel_size;
    
    // Centro do plano de projeção (d unidades à frente da câmera)
    // No código Python: self.screen_center = self.C - (self.W * self.d)
    screen_center = C - (W * d);
    
    // Canto superior esquerdo da tela
    // No código Python: self.upper_left = self.screen_center - (self.U * (screen_width / 2.0)) + (self.V * (screen_height / 2.0))
    upper_left = screen_center - (U * (screen_width / 2.0)) + (V * (screen_height / 2.0));
}

Vetor Camera::getRayDirection(int i, int j) const {
    // Deslocamento horizontal (ao longo de U)
    // No código Python: deslocamento_x = self.U * ((i + 0.5) * self.pixel_size)
    Vetor deslocamento_x = U * ((i + 0.5) * pixel_size);
    
    // Deslocamento vertical (ao longo de V)
    // No código Python: deslocamento_y = self.V * ((j + 0.5) * self.pixel_size)
    Vetor deslocamento_y = V * ((j + 0.5) * pixel_size);
    
    // Ponto central do pixel na tela
    // No código Python: pixel_center = self.upper_left + deslocamento_x - deslocamento_y
    Ponto pixel_center = upper_left + deslocamento_x - deslocamento_y;
    
    // Vetor da câmera até o pixel
    // No código Python: direcao = pixel_center - self.C
    Vetor direcao = pixel_center - C;
    
    // Retorna normalizado
    // No código Python: return direcao.normalize()
    return direcao.normalize();
}