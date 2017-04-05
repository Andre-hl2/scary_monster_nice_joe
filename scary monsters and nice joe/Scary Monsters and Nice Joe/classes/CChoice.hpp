
#include "CButton.hpp"
#include "../core/FW_Entrada.h"
#include "../core/FW_Resource.h"
#include "../core/GerenteAtor.h"
#include "../core/Ator.h"

class CChoice : public CButton
{

public:
	CChoice(GameLoop* _gameloop,char* caminhoImagem,int _posX,int _posY,int _tamX,int _tamY,int* _option,int _meuN);

	void draw2();

private:
	bool lighted;
	int* option;
	int meuN;
};