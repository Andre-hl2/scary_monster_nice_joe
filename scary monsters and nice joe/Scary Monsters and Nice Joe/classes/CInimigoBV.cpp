#include "CInimigoBV.hpp"

CInimigoBV::CInimigoBV(GerenteAtor& _gerente,int _posX,int _posY)
	:Ator(_gerente),posX(_posX),posY(_posY)
{
	box.w = 64;
	box.h = 64;
}

float CInimigoBV::pegaX()
{
	return posX;
}

float CInimigoBV::pegaY()
{
	return posY;
}


bool CInimigoBV::estaNoJogo()
{
	return vivo;
}

void CInimigoBV::inicializar()
{
	
	image = FW_carregaSprite(gerente.gameloop.renderer, "DATA/img/inimigos/inimigoBV.png", 64, 64);
	indice = 0;
	tempo = 0;
	dir = 1;
	especie = INIMIGO;

}

void CInimigoBV::atualizar()
{
	if(!gerente.isFree(box, 0, dir, TILE))
		dir*=-1;
	
	posY+=dir;

	box.x = posX;
	box.y = posY;
}


void CInimigoBV::desenhar()
{
	tempo++;
	if(tempo == 12)
	{
		tempo = 0;
		indice = (indice+1)%22;
	}

	FW_desenhaSprite(gerente.gameloop.renderer, image, indice, posX, posY);
}


void CInimigoBV::finalizar()
{
	FW_removeSprite(image);
}


CInimigoBV::~CInimigoBV()
{

}