#include "CInimigoBD.hpp"

CInimigoBD::CInimigoBD(GerenteAtor& _gerente,int _posX,int _posY)
	:Ator(_gerente),posX(_posX),posY(_posY)
{
	box.w = 64;
	box.h = 64;
}

float CInimigoBD::pegaX()
{
	return posX;
}

float CInimigoBD::pegaY()
{
	return posY;
}

bool CInimigoBD::estaNoJogo()
{
	return vivo;
}

void CInimigoBD::inicializar()
{
	indice = 0;
	tempo = 0;
	especie = INIMIGO;
	dir = 1;
	dir2 = 1;
	image = FW_carregaSprite(gerente.gameloop.renderer, "DATA/img/inimigos/inimigoBD.png", 64, 64);
}

void CInimigoBD::atualizar()
{
	if(!gerente.isFree(box, dir, 0, TILE))
	{
		dir*=-1;
	}

	if(!gerente.isFree(box, 0, dir2, TILE))
	{
		dir2*=-1;
	}

	posX+=dir;
	posY+=dir2;

	box.x = posX;
	box.y = posY;
}

void CInimigoBD::desenhar()
{

	tempo++;
	if(tempo == 16)
	{
		tempo = 0;
		indice = (indice+1)%13;
	}
	if(dir > 0)
		FW_desenhaSprite(gerente.gameloop.renderer, image, indice, posX, posY);
	else
		FW_DesenhaSpriteRot(gerente.gameloop.renderer,image,indice,posX,posY,0,true);
}

void CInimigoBD::finalizar()
{
	FW_removeSprite(image);
}

CInimigoBD::~CInimigoBD()
{

}