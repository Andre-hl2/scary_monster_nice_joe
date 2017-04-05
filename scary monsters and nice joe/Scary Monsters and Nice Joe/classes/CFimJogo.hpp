
#ifndef __CFIMJOGO_H__
#define __CFIMJOGO_H__

#include "../core/Ator.h"
#include "../core/GerenteAtor.h"
#include "../core/FW_Resource.h"

class CFimJogo : public Ator
{
public:
	bool galvao;

	CFimJogo(GerenteAtor& _gerente,int _posX,int _posY);

	float pegaX();
	float pegaY();
		
	bool estaNoJogo();
	void inicializar();		
	void atualizar();	
	void desenhar();
	void finalizar();

	~CFimJogo();
private:
	FW_Image* image;
	int posX;
	int posY;
};

#endif //__CFIMJOGO_H__