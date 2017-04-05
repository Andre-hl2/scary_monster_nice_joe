
#ifndef __RSELCRIA_H__
#define __RSELCRIA_H__

#include "../core/Tela.h"
#include "../core/GerenteAtor.h"
#include "../classes/CButton.hpp"
#include "../classes/CPreview.hpp"


class RSelCria: public Tela
{
public:

	void inicializar(GameLoop* _gameloop);
	void atualizar();
	void desenhar();
	void finalizar();

	Tela* proximaTela();

private:
	GameLoop* gameloop;

	CPreview** fases;

	FW_Image* background;

	FW_Image* selecione;

	int option;
};

#endif //__RSELCRIA_H__