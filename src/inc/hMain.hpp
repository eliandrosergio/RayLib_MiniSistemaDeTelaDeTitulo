#ifndef HMAIN_HPP
#define HMAIN_HPP

// libs c e cpp
#include <raylib.h> // para usar o raylib e permitir quase tudo
#include <vector> // para usar vetores
#include <iostream> // para usar o std::cout, std::cerr e std::string

// proto de structs em libs locais
struct	MenuStruct; // struct principal do menu
struct	GameStruct; // struct principal do jogo

// libs locais
#include "hMenu.hpp"
#include "hGame.hpp"

// defines
#define FPS 60 // valor dos frames por segundo

#endif
