#ifndef __CINIMIGOE_H__
#define __CINIMIGOE_H__

#include "../core/Ator.h"
#include "../core/GerenteAtor.h"
#include "../core/FW_Resource.h"

class CInimigoE : public Ator
{
public:
	CInimigoE(GerenteAtor& _gerente,int _posX,int _posY);

	float pegaX();
	float pegaY();
	bool estaNoJogo();
	void inicializar();		
	void atualizar();	
	void desenhar();
	void finalizar();

	~CInimigoE();
private:
	FW_Image* image;
	int posX;
	int posY;
	int dir;
	int indice;
	int tempo;
	bool vivo;
};

#endif // __CINIMIGOV_H__