# 🎮 Porongo Pong

**Porongo Pong** é uma recriação para estudo do clássico jogo de Pong desenvolvida em **C++** com a biblioteca gráfica **SFML**. O jogo simula física, sistema de pontuação, colisão com jogadores e paredes, e utiliza estrutura orientada a objetos.

## 🚀 Estudos envolvidos

- Física ( MRUV, MRU)
- Colisão com bordas e jogadores
- SFML: Renderização 2D, Eventos do teclado
- Estrutura modular orientada a objetos

## 🎮 Controles

| Jogador | Subir       | Descer     |
|--------:|:-----------:|:----------:|
| Player 1 | W           | S          |
| Player 2 | ↑ (Seta Cima) | ↓ (Seta Baixo) |

## ⚙️ Requisitos

- Compilador com suporte a C++17
- [SFML 2.5+](https://www.sfml-dev.org/)
- [CMake 3.15+](https://cmake.org/)

## 🔧 Compilação

### Linux/macOS

```bash
git clone https://github.com/seu-usuario/porongo-pong.git
cd porongo-pong
mkdir build && cd build
cmake ..
make
./PorongoPong
``` 

### Windows

```bash
git clone https://github.com/seu-usuario/porongo-pong.git
cd porongo-pong
mkdir build && cd build
cmake ..
cmake --build .
PorongoPong.exe
```
