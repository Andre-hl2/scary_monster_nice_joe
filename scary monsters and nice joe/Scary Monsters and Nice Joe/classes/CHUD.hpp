
#ifndef __CHUD_H__
#define __CHUD_H__

#include "../core/GameLoop.h"
#include "../core/FW_Resource.h"

class CHUD
{
public:
	CHUD(GameLoop& _gameloop,FW_Save& _save,int _fase);

	void atualiza();

	void desenha();

	~CHUD();

private:
	GameLoop& gameloop;
	FW_Save& save;

	FW_Image* HUD;
	FW_Image* numFase;
	FW_Image* joemorto;
	FW_Image* relogio;
	FW_Image* ponteiro;

	int quadroRelogio;
	int tempoRelogio;

	int fase;

	float graus;
	float adiciona;
};

#endif //__CHUD_H__