#include "hMain.hpp"

// Função que inicia o jogo como um todo.
void	initGame( void ) {
	// cria a janela (width, height, titulo)
	InitWindow(Menu_Width, Menu_Height, "Tela Inicial com RayLib e C++");
	SetTargetFPS(FPS); // difine o tempo do Frames-Por-Segundo

	// nossa struct do menu
	MenuStruct		ms;
	initMenuStruct(ms);

	// inicia o menu
	if (startMenu(ms)) {
		WaitTime(0.6); // dá uma pausa de 0.6 segundos
		startGame(ms); // inicia o jogo
	} else
		WaitTime(2); // dá uma pausa de 2 segundos

	// fecha a janela
	CloseWindow();
}

// O nosso main.
int		main( void ) {
	initGame();
	return (0);
}
