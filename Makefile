CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2 -I. -Isrc
LDFLAGS =

# Diretórios
SRC_DIR = src
UTILS_DIR = utils/Scene

# Arquivos fonte (todos os .cpp com os caminhos corretos)
SOURCES = main.cpp \
          $(SRC_DIR)/Camera.cpp \
          $(SRC_DIR)/Geometry.cpp \
          $(SRC_DIR)/Ponto.cpp \
          $(SRC_DIR)/Vetor.cpp \
          $(UTILS_DIR)/sceneParser.cpp \
          $(UTILS_DIR)/jsonParser.cpp

# Arquivos header (dependências)
HEADERS = $(SRC_DIR)/Camera.h \
          $(SRC_DIR)/Geometry.h \
          $(SRC_DIR)/Ponto.h \
          $(SRC_DIR)/Vetor.h \
          $(UTILS_DIR)/sceneSchema.hpp

# Executável
TARGET = out

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) utils/input/sampleScene.json > saida.ppm

.PHONY: all clean run