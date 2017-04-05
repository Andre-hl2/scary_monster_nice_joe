#include "CInimigoV.hpp"

CInimigoV::CInimigoV(GerenteAtor& _gerente,int _posX,int _posY)
	:Ator(_gerente),posX(_posX),posY(_posY)
{
	box.w = 32;
	box.h = 32;
}

float CInimigoV::pegaX()
{
	return posX;
}

float CInimigoV::pegaY()
{
	return posY;
}


bool CInimigoV::estaNoJogo()
{
	return vivo;
}

void CInimigoV::inicializar()
{
	
	image = FW_carregaSprite(gerente.gameloop.renderer, "DATA/img/inimigos/inimigoV.png", 32, 32);
	indice = 0;
	tempo = 0;
	dir = 2;
	especie = INIMIGO;

}

void CInimigoV::atualizar()
{
	if(!gerente.isFree(box, 0, dir, TILE))
		dir*=-1;
	
	posY+=dir;

	box.x = posX;
	box.y = posY;
}


void CInimigoV::desenhar()
{
	tempo++;
	if(tempo == 12)
	{
		tempo = 0;
		indice = (indice+1)%6;

	}
	FW_desenhaSprite(gerente.gameloop.renderer, image, indice, posX, posY);
}


void CInimigoV::finalizar()
{
	FW_removeSprite(image);
}


CInimigoV::~CInimigoV()
{

}