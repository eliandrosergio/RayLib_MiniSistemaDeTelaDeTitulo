#include "hMain.hpp"

// Função para "desenhar" a tela de fim do jogo.
void	ftFimDoJogo( void ) {
	const char*	texto = "Fim do Jogo!";
	int			size = 20, posY = (GetScreenHeight() / 2) - 10;
	int			posX = (GetScreenWidth() / 2) - (MeasureText(texto, size) / 2);
	DrawText(texto, posX, posY, size, BLUE);
}

// Função para desenhar a tela do jogo.
void	renderGame( GameStruct& gs ) {
	BeginDrawing();
	ClearBackground(RAYWHITE);

	if (gs.isGameOver) {
		ftFimDoJogo();
	}
	else if (gs.ms.opcaoId == 1 && !gs.formularioCompleto) {
		// Novo Jogo - Formulário
		ftNovoJogo(gs);
	}
	else if (gs.ms.opcaoId == 2 && gs.formularioCompleto) {
		// Continuar - Exibe dados carregados
		ftContinuar(gs);
	}
	else if (gs.formularioCompleto && gs.ms.opcaoId == 1) {
		// Mensagem de confirmação após salvar
		const char* msg = "Dados salvos com sucesso!";
		int msgSize = 20;
		int msgX = (GetScreenWidth() / 2) - (MeasureText(msg, msgSize) / 2);
		DrawText(msg, msgX, 90, msgSize, GREEN);
		
		static double tempoConfirmacao = 0;
		if (tempoConfirmacao == 0) tempoConfirmacao = GetTime();
		if (GetTime() - tempoConfirmacao > 2.0) {
			gs.isGameOver = true;
		}
	}
	else {
		gs.isGameOver = true;
	}

	EndDrawing();
}

// Função para ler a entrada do usuário.
void	readGameInput( GameStruct& gs ) {
	if (gs.ms.opcaoId == 1 && !gs.formularioCompleto) {
		processarFormulario(gs);
	}
}

// Função para iniciar a struct do jogo.
void	initGameStruct( GameStruct& gs, MenuStruct& ms ) {
	gs.ms = ms;
	gs.isGameOver = false;
	
	// Inicializa dados do formulário
	gs.nomeJogador = "";
	gs.idadeJogador = "";
	gs.campoAtivo = 0;
	gs.formularioCompleto = false;
	
	// Se escolheu "Continuar" (opção 2)
	if (ms.opcaoId == 2) {
		if (arquivoSaveExiste()) {
			// Tenta carregar os dados
			if (carregarDados(gs.nomeJogador, gs.idadeJogador)) {
				gs.formularioCompleto = true;
			} else {
				// Se falhou ao carregar, redireciona para novo jogo
				std::cerr << "Arquivo corrompido, redirecionando para Novo Jogo..." << std::endl;
				gs.ms.opcaoId = 1;
			}
		} else {
			// Se não existe save, redireciona para novo jogo
			std::cout << "Nenhum save encontrado, redirecionando para Novo Jogo..." << std::endl;
			gs.ms.opcaoId = 1;
		}
	}
}

// Função para iniciar o game após a escolha no menu.
void	startGame( MenuStruct& ms ) {
	SetWindowSize(Game_Width, Game_Height);

	GameStruct		gs;
	initGameStruct(gs, ms);

	while (!WindowShouldClose()) {
		if (!gs.isGameOver) {
			readGameInput(gs);
			renderGame(gs);
		}
		else
			break ;
	}
}
