
#ifndef _RTESTA_H__
#define _RTESTA_H__

#include "../classes/CFimJogo.hpp"
#include "../core/GerenteAtor.h"
#include "../core/Tela.h"
#include "../core/FW_Resource.h"
#include "../classes/CPlayer.h"
#include "../classes/CHUD.hpp"

class RTesta : public Tela
{
public:

	RTesta(int _fase,int _morte = 0);

	void inicializar(GameLoop* _gameloop);
	void atualizar();
	void desenhar();
	void finalizar();

	Tela* proximaTela();

private:
	GerenteAtor* gerente;

	CPlayer* peixe;
	CFimJogo* interruptor;

	CHUD* hud;

	FW_Image* tileCoral, *tileNeve;

	FW_Save* fase;

	bool desenhaLuz;

	char* caminho;

	GameLoop* gameloop;

	FW_Image* texto;

	FW_Image* background;
	FW_Image* frontgound;

	int acabou;
	int textureLuz;

	int Nfase;

	int tempoFase;

	int morte;
};

#endif // _RTESTA_H__