#ifndef __CINIMIGOBD_H__
#define __CINIMIGOBD_H__

#include "../core/Ator.h"
#include "../core/GerenteAtor.h"
#include "../core/FW_Resource.h"

class CInimigoBD : public Ator
{
public:
	CInimigoBD(GerenteAtor& _gerente,int _posX,int _posY);

	float pegaX();
	float pegaY();
	bool estaNoJogo();
	void inicializar();		
	void atualizar();	
	void desenhar();
	void finalizar();

	~CInimigoBD();
private:
	FW_Image* image;
	int posX;
	int posY;
	float dir, dir2;
	int indice;
	int tempo;
	bool vivo;
};



#endif // __CINIMIGO_H__
