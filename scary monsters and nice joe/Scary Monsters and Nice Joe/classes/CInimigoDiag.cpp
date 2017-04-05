#include "CInimigoDiag.hpp"

CInimigoDiag::CInimigoDiag(GerenteAtor& _gerente,int _posX,int _posY)
	:Ator(_gerente),posX(_posX),posY(_posY)
{
	box.w = 32;
	box.h = 32;
}

float CInimigoDiag::pegaX()
{
	return posX;
}

float CInimigoDiag::pegaY()
{
	return posY;
}

bool CInimigoDiag::estaNoJogo()
{
	return vivo;
}

void CInimigoDiag::inicializar()
{
	indice = 0;
	tempo = 0;
	especie = INIMIGO;
	dir = 2;
	dir2 = 2;
	image = FW_carregaSprite(gerente.gameloop.renderer, "DATA/img/inimigos/inimigoDiag.png", 32, 32);
}

void CInimigoDiag::atualizar()
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

void CInimigoDiag::desenhar()
{
	tempo++;
	if(tempo ==  12)
	{
		tempo = 0;
		indice = (indice+1)%5;
	}

	FW_desenhaSprite(gerente.gameloop.renderer, image, indice, posX, posY);
}

void CInimigoDiag::finalizar()
{
	FW_removeSprite(image);
}

CInimigoDiag::~CInimigoDiag()
{

}