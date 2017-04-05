#ifndef __CINIMIGODIAG_H__
#define __CINIMIGODIAG_H__

#include "../core/Ator.h"
#include "../core/GerenteAtor.h"
#include "../core/FW_Resource.h"

class CInimigoDiag : public Ator
{
public:
	CInimigoDiag(GerenteAtor& _gerente,int _posX,int _posY);

	float pegaX();
	float pegaY();
	bool estaNoJogo();
	void inicializar();		
	void atualizar();	
	void desenhar();
	void finalizar();

	~CInimigoDiag();
private:
	FW_Image* image;
	int posX;
	int posY;
	int dir, dir2;
	int indice;
	int tempo;
	bool vivo;
};



#endif // __CINIMIGO_H__
