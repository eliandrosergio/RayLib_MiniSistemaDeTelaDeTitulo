#include "hMain.hpp"

// Função que "desenha" as opções do menu (cada ponto 'x' de cada opção varia de 30 em 30 pixels).
void	drawTexts( void ) {
	DrawText("Novo Jogo", 60, 30, 30, BLACK); // texto, x, y, size, cor
	DrawText("Continuar", 60, 60, 30, BLACK); // texto, x, y, size, cor
	DrawText("Sair", 60, 90, 30, BLACK); // texto, x, y, size, cor
}

// Função para "desenhar" a tela de saida.
void	ftSair( void ) {
	const char*	texto = std::string("Até a proxima!").c_str();
	int			size = 20, posY = (GetScreenHeight() / 2) - 10;
	int			posX = (GetScreenWidth() / 2) - (MeasureText(texto, size) / 2);

	// "desenha" o texto de saida
	DrawText(texto, posX, posY, size, BLUE);
}

// Função para desenhar a tela do menu.
void	renderMenu( MenuStruct& ms ) {
	BeginDrawing(); // sinaliza o começo do processo de desenhar
	ClearBackground(RAYWHITE); // pinta toda a tela de branco

	// escolhe o que desenhar na tela
	if (ms.opcaoId == 3)
		ftSair();
	else if (!ms.opcaoEscolhida) {
		// desenha o selector (um triangulo na cor azul)
		DrawTriangle(ms.posSltV1, ms.posSltV2, ms.posSltV3, BLUE);
		drawTexts(); // chama a função para "desenhar" as opções
	}

	// sinaliza o termino do processo de desenhar
	EndDrawing();
}

// Função para receber um diferencial de posição (int) e atribui-lo a todos os pontos 'y' dos vetores do selector.
void	mudarPosSelector(  MenuStruct& ms, const int& pos ) {
	ms.posSltV1.y += pos;
	ms.posSltV2.y += pos;
	ms.posSltV3.y += pos;
}

// Função para ler a entrada do usuário e mudar a posição do selector de acordo.
void	readMenuInput( MenuStruct& ms ) {
	if (IsKeyPressed(KEY_UP)) {
		if (ms.posSltV3.y == ms.posOpcao02 || ms.posSltV3.y == ms.posOpcao03)
			mudarPosSelector(ms, -30); // diminui 30 pixels do y de cada vetor do selector
	}
	if (IsKeyPressed(KEY_DOWN)) {
		if (ms.posSltV3.y == ms.posOpcao01 || ms.posSltV3.y == ms.posOpcao02)
			mudarPosSelector(ms, 30); // aumenta 30 pixels do y de cada vetor do selector
	}
	if (IsKeyPressed(KEY_ENTER)) {
		if (ms.posSltV3.y == ms.posOpcao03)
			ms.opcaoId = 3;
		else if (ms.posSltV3.y == ms.posOpcao01 || ms.posSltV3.y == ms.posOpcao02) {
			if (ms.posSltV3.y == ms.posOpcao01)
				ms.opcaoId = 1;
			else if (ms.posSltV3.y == ms.posOpcao02)
				ms.opcaoId = 2;
			ms.opcaoEscolhida = true;
		}
	}
}

// Função para iniciar a struct do menu.
void	initMenuStruct( MenuStruct& ms ) {
	// define os vetores do triângulo que será o nosso selector
	ms.posSltV1 = {10, 20}; // x, y  v1*
	ms.posSltV2 = {10, 70}; // x, y         *v3
	ms.posSltV3 = {45, 44}; // x, y  v2*

	// bool para definir se uma opção foi escolhida ou não (sem ser a opção de sair)
	ms.opcaoEscolhida = false;

	// vetores das posições do v3 do selector em cada opção
	ms.posOpcao01 = 44;
	ms.posOpcao02 = 74;
	ms.posOpcao03 = 104;

	// nosso int para guardar a opção escolhida no menu
	ms.opcaoId = 0;
}

// Função que inicia o menu.
bool	startMenu( MenuStruct& ms ) {
	// loop para rodar enqunto a janela existir
	while (!WindowShouldClose()) {
		if (ms.opcaoEscolhida)
			break ;
		else if (ms.opcaoId != 3) {
			readMenuInput(ms);
			renderMenu(ms);
		} else
			break ;
	}

	// inicia o jogo
	if (ms.opcaoEscolhida)
		return (true);
	return (false);
}
