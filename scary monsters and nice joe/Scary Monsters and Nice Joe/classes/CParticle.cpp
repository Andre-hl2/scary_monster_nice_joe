
#include "../Main.hpp"
#include "CParticle.hpp"

#include "../core/FW_Entrada.h"

CParticle::CParticle(GerenteAtor& _gerente)
	:Ator(_gerente)
{

}

void CParticle::init()
{
	posX = 1+rand()%1024;
	posY = 778-(rand()%20);
	vspeed = -1*( 1+rand()%2);
}

void CParticle::redirect()
{
	hspeed = -1+rand()%2;
}

float CParticle::pegaX()
{
	return posX;
}

float CParticle::pegaY()
{
	return posY;
}

bool CParticle::estaNoJogo()
{
	return true;
}

void CParticle::inicializar()
{
	image = FW_carregaSprite(gerente.gameloop.renderer,"DATA/img/scenario/particle1.png",0,0);
	
	posX = 1+rand()%1024;
	posY = 1+rand()%768;

	vspeed = -3+rand()%2;
	hspeed = -4+rand()%8;

	tempo = 0;
}

void CParticle::atualizar()
{
	tempo++;

	if(tempo == 80)
	{
		tempo = 0;
		redirect();
	}

	posX += hspeed;
	posY += vspeed;
	
	if(posY < -32)
		init();
	
}

void CParticle::desenhar()
{
	FW_desenhaSprite(gerente.gameloop.renderer,image,0,posX,posY);
}

void CParticle::finalizar()
{
	FW_removeSprite(image);
}

CParticle::~CParticle()
{
	FW_removeSprite(image);
}
