
#include "../Main.hpp"
#include "CTile.hpp"


CTile::CTile(GerenteAtor& _gerente,int _posX,int _posY,int _tipo)
	:Ator(_gerente),posX(_posX),posY(_posY),tipo(_tipo)
{
	especie = TILE;

	indice = 0;
	box.h = 32;
	box.w = 32;
	box.x = posX;
	box.y = posY;
}

float CTile::pegaX()
{
	return posX;
}

float CTile::pegaY()
{
	return posY;
}

bool CTile::estaNoJogo()
{
	return true;
}

void CTile::inicializar()
{
	switch(tipo)
	{
	case 1:
		image = FW_carregaSprite(gerente.gameloop.renderer,"DATA/img/tiles/coral.png",32,32);
		indice = rand()%8;
		break;
	case 2:
		if(rand()%2 == 0)
			image = FW_carregaSprite(gerente.gameloop.renderer,"DATA/img/tiles/tileNeve.png",32,32);
		else
			image = FW_carregaSprite(gerente.gameloop.renderer,"DATA/img/tiles/tileNeve1.png",32,32);
		indice = rand()%2;
		tempoMax = 1+rand()%200;
		tempo = 0;
		break;
	case 3:
		image = FW_carregaSprite(gerente.gameloop.renderer,"DATA/img/tiles/tileRocha.png",32,32);
		indice = rand()%2;
		break;
	case 4:
		image = FW_carregaSprite(gerente.gameloop.renderer,"DATA/img/tiles/tilePreto.png",32,32);
		break;
	}
	

}

void CTile::atualizar()
{
	if(tipo == 2)
	{
		tempo++;
		if(tempo == tempoMax)
		{
			tempo = 0;
			indice = (indice==0)? 1 : 0;
		}
	}
}

void CTile::desenhar()
{
	FW_desenhaSprite(gerente.gameloop.renderer,image,indice,posX,posY);
}

void CTile::finalizar()
{
	FW_removeSprite(image);
}


CTile::~CTile()
{
	FW_removeSprite(image);
}