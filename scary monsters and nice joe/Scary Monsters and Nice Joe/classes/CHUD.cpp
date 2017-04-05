
#include "../Main.hpp"

#include "CHUD.hpp"

CHUD::CHUD(GameLoop& _gameloop,FW_Save& _save,int _fase)
	:gameloop(_gameloop),save(_save),fase(_fase)
{
	HUD =	   FW_carregaSprite(gameloop.renderer,"DATA/img/scenario/HUD.png",0,0);
	numFase =  FW_carregaSprite(gameloop.renderer,"DATA/img/scenario/numFase.png",64,64);
	joemorto = FW_carregaSprite(gameloop.renderer,"DATA/img/scenario/joeMorto.png",0,0);
	relogio =  FW_carregaSprite(gameloop.renderer,"DATA/img/scenario/relogio.png",64,64);
	ponteiro = FW_carregaSprite(gameloop.renderer,"DATA/img/scenario/ponteiro.png",0,0);

	quadroRelogio = 0;
	tempoRelogio = 0;

	graus = 0;
	float temp = (save.tempo*60);
	adiciona = 360/temp;
}


void CHUD::atualiza()
{
	graus+=adiciona;

	if(save.tempo < 30)
	{
		tempoRelogio++;
		if(tempoRelogio==30)
		{
			tempoRelogio = 0;
			quadroRelogio  = (quadroRelogio==1)? 0 : 1;
		}
	}
}


void CHUD::desenha()
{
	FW_desenhaSprite(gameloop.renderer,HUD,0,0,0);
	FW_desenhaSprite(gameloop.renderer,joemorto,0,833,4);
	FW_desenhaSprite(gameloop.renderer,numFase,fase,30,4);
	FW_desenhaSprite(gameloop.renderer,relogio,quadroRelogio,450,4);

	FW_DesenhaSpriteRot(gameloop.renderer,ponteiro,0,450,4,graus);
}


CHUD::~CHUD()
{
	FW_removeSprite(    HUD   );
	FW_removeSprite( joemorto );
	FW_removeSprite( relogio  );
	FW_removeSprite( ponteiro );
}
