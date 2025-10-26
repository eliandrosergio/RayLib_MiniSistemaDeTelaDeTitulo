#include "hMain.hpp"

// Função para "desenhar" a tela de fim do jogo.
void	ftFimDoJogo( void ) {
	const char*	texto = std::string("Fim do Jogo!").c_str();
	int			size = 20, posY = (GetScreenHeight() / 2) - 10;
	int			posX = (GetScreenWidth() / 2) - (MeasureText(texto, size) / 2);

	// "desenha" o texto do fim do jogo
	DrawText(texto, posX, posY, size, BLUE);
}

// Função para desenhar a tela de "Novo Jogo".
void	ftNovoJogo( void ) {
	DrawText("Vamos coletar seus dados.", 60, 30, 20, BLACK);
}

// Função para desenhar a tela do jogo.
void	renderGame( GameStruct& gs ) {
	BeginDrawing();  // sinaliza o começo do processo de desenhar
	ClearBackground(RAYWHITE); // pinta toda a tela de branco

	if (gs.isGameOver)
		ftFimDoJogo();
	else if (gs.ms.opcaoId == 1)
		ftNovoJogo();
	else {
		gs.isGameOver = true;
	}

	// sinaliza o termino do processo de desenhar
	EndDrawing();
}

// Função para ler a entrada do usuário.
void	readGameInput( GameStruct& gs ) {}

// Função para iniciar a struct do jogo.
void	initGameStruct( GameStruct& gs, MenuStruct& ms ) {
	// guarda os valores da MenuStruct
	gs.ms = ms;

	// diz se o jogo já terminou ou não
	gs.isGameOver = false;
}

// Função para iniciar o game após a escolha no menu.
void	startGame( MenuStruct& ms ) {
	// redefine o tamanho da tela
	SetWindowSize(Game_Width, Game_Height);

	// nossa struct do menu
	GameStruct		gs;
	initGameStruct(gs, ms);

	// loop para rodar enqunto a janela existir
	while (!WindowShouldClose()) {
		if (!gs.isGameOver)
			renderGame(gs);
		else
			break ;
	}
}
