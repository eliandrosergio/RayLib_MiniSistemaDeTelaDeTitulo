#include "hMain.hpp"

// Função auxiliar para capturar entrada de texto
void	capturarEntradaCampo( std::string& campo, int maxCaracteres ) {
	// Captura todos os caracteres pressionados
	int tecla = GetCharPressed();
	while (tecla > 0) {
		// Aceita apenas caracteres imprimíveis (32-125 ASCII)
		if ((tecla >= 32) && (tecla <= 125) && (campo.length() < maxCaracteres)) {
			campo += (char)tecla;
		}
		tecla = GetCharPressed();
	}

	// Backspace para apagar
	if (IsKeyPressed(KEY_BACKSPACE) && !campo.empty()) {
		campo.pop_back();
	}
}

// Função para desenhar um campo de input.
void	desenharCampo( const std::string& label, const std::string& conteudo, int posX, int posY, bool ativo ) {
	int larguraCampo = 300;
	int alturaCampo = 30;

	// Desenha o label
	DrawText(label.c_str(), posX, posY - 25, 20, DARKGRAY);

	// Desenha o retângulo do campo
	Color corBorda = ativo ? BLUE : LIGHTGRAY;
	DrawRectangleLines(posX, posY, larguraCampo, alturaCampo, corBorda);

	// Desenha o fundo do campo
	Color corFundo = ativo ? (Color){230, 240, 255, 255} : RAYWHITE;
	DrawRectangle(posX + 1, posY + 1, larguraCampo - 2, alturaCampo - 2, corFundo);

	// Desenha o texto dentro do campo
	DrawText(conteudo.c_str(), posX + 10, posY + 7, 18, BLACK);

	// Desenha cursor piscando se o campo estiver ativo
	if (ativo) {
		int larguraTexto = MeasureText(conteudo.c_str(), 18);
		// Pisca a cada 30 frames (0.5 segundos a 60 FPS)
		if ((GetTime() * 2) - (int)(GetTime() * 2) < 0.5) {
			DrawText("_", posX + 10 + larguraTexto, posY + 7, 18, BLACK);
		}
	}
}

// Função para desenhar a tela de "Novo Jogo" com formulário.
void	ftNovoJogo( GameStruct& gs ) {
	// Título
	const char* titulo = "Cadastro de Jogador";
	int tituloSize = 24;
	int tituloX = (GetScreenWidth() / 2) - (MeasureText(titulo, tituloSize) / 2);
	DrawText(titulo, tituloX, 20, tituloSize, DARKBLUE);
	
	// Desenha os campos
	desenharCampo("Nome:", gs.nomeJogador, 50, 70, gs.campoAtivo == 0);
	desenharCampo("Idade:", gs.idadeJogador, 50, 130, gs.campoAtivo == 1);
	
	// Instruções
	DrawText("Use TAB ou ENTER para navegar", 50, 175, 12, GRAY);
	DrawText("Pressione ENTER no ultimo campo para salvar", 50, 190, 12, GRAY);
}

// Função para processar entrada do formulário.
void	processarFormulario( GameStruct& gs ) {
	// Captura entrada no campo ativo
	if (gs.campoAtivo == 0) {
		capturarEntradaCampo(gs.nomeJogador, 30);
	} else if (gs.campoAtivo == 1) {
		// Para idade, aceita apenas números
		int tecla = GetCharPressed();
		while (tecla > 0) {
			if ((tecla >= '0') && (tecla <= '9') && (gs.idadeJogador.length() < 3)) {
				gs.idadeJogador += (char)tecla;
			}
			tecla = GetCharPressed();
		}
		
		// Backspace
		if (IsKeyPressed(KEY_BACKSPACE) && !gs.idadeJogador.empty()) {
			gs.idadeJogador.pop_back();
		}
	}

	// TAB para avançar campo
	if (IsKeyPressed(KEY_TAB)) {
		if (gs.campoAtivo == 0) {
			gs.campoAtivo = 1;  // Vai para idade
		} else if (gs.campoAtivo == 1) {
			gs.campoAtivo = 0;  // Volta para nome
		}
	}

	// ENTER para avançar ou salvar
	if (IsKeyPressed(KEY_ENTER)) {
		if (gs.campoAtivo == 0) {
			gs.campoAtivo = 1;  // Vai para idade
		} else if (gs.campoAtivo == 1) {
			// Valida se os campos não estão vazios
			if (!gs.nomeJogador.empty() && !gs.idadeJogador.empty()) {
				gs.formularioCompleto = true;
				// Salva os dados no arquivo
				std::cout << "Dados salvos: " << gs.nomeJogador << ", " << gs.idadeJogador << std::endl;
			}
		}
	}
}

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

	if (gs.isGameOver)
		ftFimDoJogo();
	else if (gs.ms.opcaoId == 1 && !gs.formularioCompleto)
		ftNovoJogo(gs);
	else if (gs.formularioCompleto) {
		// Mensagem de confirmação
		const char* msg = "Dados salvos com sucesso!";
		int msgSize = 20;
		int msgX = (GetScreenWidth() / 2) - (MeasureText(msg, msgSize) / 2);
		DrawText(msg, msgX, 90, msgSize, GREEN);
		
		// Após 2 segundos, encerra
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
	gs.campoAtivo = 0;  // Começa no campo nome
	gs.formularioCompleto = false;
}

// Função para iniciar o game após a escolha no menu.
void	startGame( MenuStruct& ms ) {
	SetWindowSize(Game_Width, Game_Height);

	GameStruct		gs;
	initGameStruct(gs, ms);

	while (!WindowShouldClose()) {
		if (!gs.isGameOver) {
			// processar input antes de renderizar
			readGameInput(gs);
			renderGame(gs);
		}
		else
			break ;
	}
}
