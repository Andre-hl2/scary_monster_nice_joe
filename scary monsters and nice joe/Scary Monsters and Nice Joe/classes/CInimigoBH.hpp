#ifndef __CINIMIGOBH_H__
#define __CINIMIGOBH_H__

#include "../core/Ator.h"
#include "../core/GerenteAtor.h"
#include "../core/FW_Resource.h"

class CInimigoBH : public Ator
{
public:
	CInimigoBH(GerenteAtor& _gerente,int _posX,int _posY);

	float pegaX();
	float pegaY();
	bool estaNoJogo();
	void inicializar();		
	void atualizar();	
	void desenhar();
	void finalizar();

	~CInimigoBH();
private:
	FW_Image* image;
	int posX;
	int posY;
	float dir;
	int indice;
	int tempo;
	bool vivo;
};



#endif // __CINIMIGO_H__
