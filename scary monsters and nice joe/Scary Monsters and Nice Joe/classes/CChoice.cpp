
#include "../Main.hpp"

#include "CChoice.hpp"


CChoice::CChoice(GameLoop* _gameloop,char* caminhoImagem,int _posX,int _posY,int _tamX,int _tamY,int* _option,int _meuN)
	:CButton(_gameloop,caminhoImagem,_posX,_posY,_tamX,_tamY),option(_option),meuN(_meuN)
{
}

void CChoice::draw2()
{
	if(*option == meuN)
	{
		FW_desenhaSprite(gameloop->renderer,image,1,posX,posY);
	}
	else
	{
		FW_desenhaSprite(gameloop->renderer,image,0,posX,posY);
	}
}