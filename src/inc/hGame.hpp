#ifndef HGAME_HPP
#define HGAME_HPP

#include "hMain.hpp"

#define Game_Width 400 // valor da largura da tela do jogo
#define Game_Height 200 // valor da altura da tela do jogo

// struct principal do jogo
struct	GameStruct {
	MenuStruct	ms;
	bool		isGameOver;
};

// game.cpp
void	startGame( MenuStruct& ms );

#endif
