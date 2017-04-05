
#ifndef __CPREVIEW_H__
#define __CPREVIEW_H__

#include "CButton.hpp"
#include "../core/GameLoop.h"
#include "../core/FW_Resource.h"

//class GameLoop;

class CPreview
{

public:
	CPreview(GameLoop* _gameloop,char* caminho,int _posX,int _posY,int* _option, int _Mnum);

	bool pressed();

	void draw();

	~CPreview();
private:
	GameLoop* gameloop;
	FW_Save* save;
	FW_Perfil* perfil;

	FW_Image* bloqueado;

	int posX,
		posY;

	int Mnum;
	int* option;
};

#endif //__CPREVIEW_H__