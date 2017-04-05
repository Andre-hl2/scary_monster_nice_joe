#include "CFimJogo.hpp"

CFimJogo::CFimJogo(GerenteAtor& _gerente,int _posX,int _posY)
	:Ator(_gerente),posX(_posX),posY(_posY)
{
	box.w = 32;
	box.h = 32;
}

float CFimJogo::pegaX()
{
	return posX;
}

float CFimJogo::pegaY()
{
	return posY;
}

bool CFimJogo::estaNoJogo()
{
	return true;
}

void CFimJogo::inicializar()
{
	especie = FIMJOGO;
	image = FW_carregaSprite(gerente.gameloop.renderer, "DATA/img/jogador/fimJogo.png", 32, 32);
	galvao = 0;
}

void CFimJogo::atualizar()
{
	if(!gerente.isFree(box,0,0,JOGADOR))
	{
		galvao = true;
	}

	box.x = posX;
	box.y = posY;
}

void CFimJogo::desenhar()
{
	FW_desenhaSprite(gerente.gameloop.renderer, image, 0, posX, posY);
}

void CFimJogo::finalizar()
{
	FW_removeSprite(image);
}

CFimJogo::~CFimJogo()
{
}