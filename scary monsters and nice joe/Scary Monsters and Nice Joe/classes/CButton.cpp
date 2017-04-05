
#include "../Main.hpp"
#include "../core/FW_Entrada.h"

#include "CButton.hpp"

CButton::CButton(GameLoop* _gameloop,char* caminhoImagem,int _posX,int _posY,int _tamX,int _tamY)
	:gameloop(_gameloop),posX(_posX),posY(_posY),tamX(_tamX),tamY(_tamY)
{
	image = FW_carregaSprite(gameloop->renderer,caminhoImagem,tamX,tamY);
}

bool CButton::pressed()
{
	FW_Mouse* mouse = ENTRADA.pegaMouse();

	return(( mouse->x > posX && mouse->x < posX+tamX && mouse->y > posY && mouse->y < posY + tamY && mouse->botoes[FW_MESQUERDO].pressionado));
	
}

void CButton::draw()
{
	FW_desenhaSprite(gameloop->renderer,image,0,posX,posY);
}

CButton::~CButton()
{
	FW_removeSprite( image );
}