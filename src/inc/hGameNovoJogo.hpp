#ifndef HGAMENOVOJOGO_HPP
#define HGAMENOVOJOGO_HPP

#include "hMain.hpp"

// Funções para Novo Jogo
void	capturarEntradaCampo( std::string& campo, int maxCaracteres );
void	desenharCampo( const std::string& label, const std::string& conteudo, int posX, int posY, bool ativo );
void	ftNovoJogo( GameStruct& gs );
void	processarFormulario( GameStruct& gs );
bool	salvarDados( const std::string& nome, const std::string& idade );

#endif
