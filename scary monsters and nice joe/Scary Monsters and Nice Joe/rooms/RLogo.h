#ifndef __RLOGO_H__
#define __RLOGO_H__

#include "../core/GerenteAtor.h"
#include "../core/Tela.h"
#include "../core/FW_Resource.h"
#include "../classes/CPlayer.h"

class RLogo : public Tela
{
public:
	RLogo();

	void inicializar(GameLoop* _gameloop);
	void atualizar();

	void desenhar();
	void finalizar();

	Tela* proximaTela();

private:
	GameLoop* gameloop;

	GerenteAtor* gerente;
	
	bool apareceno;
	bool desapareceno;

	bool galvao;

	int fade;

	int tempo;

	FW_Image* logo;
};

#endif //__RLOGO_H__