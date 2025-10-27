#ifndef HGAMECONTINUARJOGO_HPP
#define HGAMECONTINUARJOGO_HPP

#include "hMain.hpp"

// Funções para Continuar Jogo
bool	arquivoSaveExiste( void );
bool	carregarDados( std::string& nome, std::string& idade );
void	ftContinuar( GameStruct& gs );

#endif
