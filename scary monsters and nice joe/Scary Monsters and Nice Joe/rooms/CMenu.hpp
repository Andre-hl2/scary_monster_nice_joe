
#ifndef __CMENU_H__
#define __CMENU_H__

#include "../core/Tela.h"
#include "../core/GerenteAtor.h"
#include "../classes/CButton.hpp"
#include "../classes/CChoice.hpp"


class CMenu : public Tela
{
public:

	void inicializar(GameLoop* _gameloop);
	void atualizar();
	void desenhar();
	void finalizar();

	Tela* proximaTela();

private:
	GameLoop* gameloop;

	GerenteAtor* gerente;

	CChoice* play, *create, *edit, *testa;

	FW_Image* peixe;
	int indicePeixe;
	int tempoPeixe;

	FW_Image* background;

	int option;
	//int indicePeixe;

	int fade;
	SDL_Rect boxFade;

	FW_Image* cobra;
	FW_Image* joe;
};

#endif //__CMENU_H__