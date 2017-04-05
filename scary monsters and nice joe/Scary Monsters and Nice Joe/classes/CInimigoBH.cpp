#include "CInimigoBH.hpp"

CInimigoBH::CInimigoBH(GerenteAtor& _gerente,int _posX,int _posY)
	:Ator(_gerente),posX(_posX),posY(_posY)
{
	box.w = 64;
	box.h = 64;
}

float CInimigoBH::pegaX()
{
	return posX;
}

float CInimigoBH::pegaY()
{
	return posY;
}

bool CInimigoBH::estaNoJogo()
{
	return vivo;
}

void CInimigoBH::inicializar()
{
	indice = 0;
	tempo = 0;
	especie = INIMIGO;
	dir = 1;
	image = FW_carregaSprite(gerente.gameloop.renderer, "DATA/img/inimigos/inimigoBH.png", 64, 64);
}

void CInimigoBH::atualizar()
{
	if(!gerente.isFree(box, dir, 0, TILE))
		dir*=-1;

	posX+=dir;

	box.x = posX;
	box.y = posY;
}

void CInimigoBH::desenhar()
{
	tempo++;
	if(tempo == 12)
	{
		tempo = 0;
		indice = (indice+1)%6;
	}

	if(dir >0)
		FW_desenhaSprite(gerente.gameloop.renderer, image, indice, posX, posY);
	else
		FW_DesenhaSpriteRot(gerente.gameloop.renderer,image,indice,posX,posY,0,true);
}

void CInimigoBH::finalizar()
{
	FW_removeSprite(image);
}

CInimigoBH::~CInimigoBH()
{

}