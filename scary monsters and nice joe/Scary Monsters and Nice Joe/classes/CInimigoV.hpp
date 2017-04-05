#ifndef __CINIMIGOV_H__
#define __CINIMIGOV_H__

#include "../core/Ator.h"
#include "../core/GerenteAtor.h"
#include "../core/FW_Resource.h"

class CInimigoV : public Ator
{
public:
	CInimigoV(GerenteAtor& _gerente,int _posX,int _posY);

	float pegaX();
	float pegaY();
	bool estaNoJogo();
	void inicializar();		
	void atualizar();	
	void desenhar();
	void finalizar();

	~CInimigoV();
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