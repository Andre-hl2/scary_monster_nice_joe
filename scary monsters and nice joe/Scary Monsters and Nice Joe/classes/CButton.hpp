
#ifndef __CBUTTON_H__
#define __CBUTTON_H__

#include "../core/GameLoop.h"
#include "../core/FW_Resource.h"

class CButton
{
public:

	CButton(GameLoop* _gameloop,char* caminhoImagem,int _posX,int _posY,int _tamX,int _tamY);

	bool pressed();

	void draw();

	~CButton();

	int posX,
		posY;

	GameLoop* gameloop;
	FW_Image* image;
	
	int	tamX,
		tamY;
};


#endif// __CBUTTON_H__