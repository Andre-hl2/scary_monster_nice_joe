#ifndef __RPREMENU_H__
#define __RPREMENU_H__

#include "../core/GerenteAtor.h"
#include "../core/Tela.h"
#include "../core/FW_Resource.h"
#include "../classes/CPlayer.h"

class RPreMenu : public Tela
{
public:
	RPreMenu();

	void inicializar(GameLoop* _gameloop);
	void atualizar();

	void desenhar();
	void finalizar();

	Tela* proximaTela();

private:
	GameLoop* gameloop;

	GerenteAtor* gerente;

	bool galvao;

	int fade;

	int tempo;

	int cobraTempo;
	int cobraQuadro;

	int cobraX,cobraY;

	bool desenhaCobra, desenhaJoe;

	int joeTempo;
	int joeQuadro;

	FW_Image* cobra;
	FW_Image* joe;
	FW_Image* cobraAnda;
};

#endif //__RPREMENU_H__