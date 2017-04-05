#include "CInimigoH.hpp"

CInimigoH::CInimigoH(GerenteAtor& _gerente,int _posX,int _posY)
	:Ator(_gerente),posX(_posX),posY(_posY)
{
	box.w = 32;
	box.h = 32;
}

float CInimigoH::pegaX()
{
	return posX;
}

float CInimigoH::pegaY()
{
	return posY;
}

bool CInimigoH::estaNoJogo()
{
	return vivo;
}

void CInimigoH::inicializar()
{
	indice = 0;
	tempo = 0;
	especie = INIMIGO;
	dir = 2;
	image = FW_carregaSprite(gerente.gameloop.renderer, "DATA/img/inimigos/inimigoH.png", 32, 32);
}

void CInimigoH::atualizar()
{
	if(!gerente.isFree(box, dir, 0, TILE))
		dir*=-1;

	posX+=dir;

	box.x = posX;
	box.y = posY;
}

void CInimigoH::desenhar()
{
	tempo++;
	if(tempo ==  12)
	{
		tempo = 0;
		indice = (indice+1)%6;
	}
	if(dir > 0)
		FW_desenhaSprite(gerente.gameloop.renderer, image, indice, posX, posY);
	else
		FW_DesenhaSpriteRot(gerente.gameloop.renderer,image,indice,posX,posY,0,true);
}

void CInimigoH::finalizar()
{
	FW_removeSprite(image);
}

CInimigoH::~CInimigoH()
{

}