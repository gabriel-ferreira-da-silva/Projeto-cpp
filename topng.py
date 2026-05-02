#!/usr/bin/env python3
# ppm_viewer.py

import sys
from PIL import Image

def ppm_to_image(filename):
    """Converte PPM para PNG/JPEG"""
    with open(filename, 'r') as f:
        # Lê o cabeçalho
        format = f.readline().strip()
        while True:
            line = f.readline().strip()
            if not line.startswith('#'):
                break
        
        width, height = map(int, line.split())
        max_color = int(f.readline().strip())
        
        # Lê os pixels
        pixels = []
        for line in f:
            pixels.extend(map(int, line.split()))
    
    # Cria imagem PIL
    img = Image.new('RGB', (width, height))
    img.putdata([(pixels[i], pixels[i+1], pixels[i+2]) 
                 for i in range(0, len(pixels), 3)])
    
    return img

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Uso: {sys.argv[0]} <arquivo.ppm>")
        sys.exit(1)
    
    img = ppm_to_image(sys.argv[1])
    
    # Salva como PNG
    output = sys.argv[1].replace('.ppm', '.png')
    img.save(output)
    print(f"Convertido para {output}")
    
    # Opcional: mostrar a imagem
    # img.show()