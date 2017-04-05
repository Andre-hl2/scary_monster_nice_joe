#ifndef __CINIMIGOBV_H__
#define __CINIMIGOBV_H__

#include "../core/Ator.h"
#include "../core/GerenteAtor.h"
#include "../core/FW_Resource.h"

class CInimigoBV : public Ator
{
public:
	CInimigoBV(GerenteAtor& _gerente,int _posX,int _posY);

	float pegaX();
	float pegaY();
	bool estaNoJogo();
	void inicializar();		
	void atualizar();	
	void desenhar();
	void finalizar();

	~CInimigoBV();
private:
	FW_Image* image;
	int posX;
	int posY;
	float dir;
	int indice;
	int tempo;
	bool vivo;
};

#endif // __CINIMIGOV_H__