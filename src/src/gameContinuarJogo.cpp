#include "hMain.hpp"

// Função para verificar se o arquivo de save existe
bool	arquivoSaveExiste( void ) {
	struct stat buffer;
	return (stat("save.txt", &buffer) == 0);
}

// Função para carregar os dados do arquivo
bool	carregarDados( std::string& nome, std::string& idade ) {
	std::ifstream arquivo("save.txt");
	
	if (!arquivo.is_open()) {
		std::cerr << "Erro ao abrir arquivo de save!" << std::endl;
		return false;
	}
	
	std::string linha;
	if (std::getline(arquivo, linha)) {
		// Procura o separador '|'
		size_t pos = linha.find('|');
		if (pos != std::string::npos) {
			nome = linha.substr(0, pos);
			idade = linha.substr(pos + 1);
			arquivo.close();
			std::cout << "Dados carregados: " << nome << ", " << idade << std::endl;
			return true;
		}
	}
	
	arquivo.close();
	return false;
}

// Função para desenhar a tela de "Continuar" com os dados carregados
void	ftContinuar( GameStruct& gs ) {
	// Título
	const char* titulo = "Dados do Jogador";
	int tituloSize = 24;
	int tituloX = (GetScreenWidth() / 2) - (MeasureText(titulo, tituloSize) / 2);
	DrawText(titulo, tituloX, 20, tituloSize, DARKBLUE);
	
	// Linha separadora
	DrawLine(30, 50, GetScreenWidth() - 30, 50, LIGHTGRAY);
	
	// Exibe os dados de forma bonita
	DrawText("Nome:", 50, 70, 20, DARKGRAY);
	DrawText(gs.nomeJogador.c_str(), 50, 95, 22, BLACK);
	
	DrawText("Idade:", 50, 130, 20, DARKGRAY);
	DrawText(gs.idadeJogador.c_str(), 50, 155, 22, BLACK);
	
	// Instruções
	DrawText("Pressione ESC para sair", 50, 180, 12, GRAY);
}
