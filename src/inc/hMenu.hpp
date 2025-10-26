#ifndef HMENU_HPP
#define HMENU_HPP

#define Menu_Width 250 // valor da largura da tela do menu
#define Menu_Height 150 // valor da altura da tela do menu

// struct principal do menu
struct	MenuStruct {
	Vector2		posSltV1;
	Vector2		posSltV2;
	Vector2		posSltV3;

	bool		opcaoEscolhida;
	float		posOpcao01;
	float		posOpcao02;
	float		posOpcao03;
	int			opcaoId;
};

// menu.cpp
bool	startMenu( MenuStruct& ms );
void	initMenuStruct( MenuStruct& ms );

#endif
