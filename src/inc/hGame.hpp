#ifndef HGAME_HPP
#define HGAME_HPP

#include "hMain.hpp"

#define Game_Width 400 // valor da largura da tela do jogo
#define Game_Height 250 // valor da altura da tela do jogo

// struct principal do jogo
struct	GameStruct {
	MenuStruct	ms;
	bool		isGameOver;
	
	// Dados do formulário
	std::string nomeJogador;
	std::string idadeJogador;
	int			campoAtivo;  // 0 = nome, 1 = idade
	bool		formularioCompleto;
};

// game.cpp
void	startGame( MenuStruct& ms );

#endif
