

#ifndef __CTILE_H__
#define __CTILE_H__


#include "../core/GerenteAtor.h"
#include "../core/Ator.h"
#include "../core/FW_Resource.h"

class CTile: public Ator
{
public:
	CTile(GerenteAtor& _gerente,int _posX,int _posY,int _tipo = 1);

	float pegaX();
	float pegaY();
		
	bool estaNoJogo();
	void inicializar();		
	void atualizar();	
	void desenhar();
	void finalizar();

	~CTile();
private:

	FW_Image* image;

	int tipo;

	int tempo;
	int tempoMax;

	int indice;

	int posX;
	int posY;

};

#endif // __CTILE_H__