
#ifndef __RPLAY_H__
#define __RPLAY_H__

#include "../classes/CFimJogo.hpp"
#include "../core/GerenteAtor.h"
#include "../core/Tela.h"
#include "../core/FW_Resource.h"
#include "../classes/CPlayer.h"

class RPlay : public Tela
{
public:

	RPlay(char* _caminho);

	void inicializar(GameLoop* _gameloop);
	void atualizar();
	void desenhar();
	void finalizar();

	Tela* proximaTela();

private:
	GerenteAtor* gerente;

	CPlayer* peixe;
	CFimJogo* interruptor;

	FW_Image* tileCoral, *tileNeve;

	FW_Save* fase;

	FW_Image* HUD;

	bool desenhaLuz;

	char* caminho;

	GameLoop* gameloop;

	FW_Image* background;
	FW_Image* frontgound;

	int acabou;
	int textureLuz;

};

#endif // __RPLAY_H__