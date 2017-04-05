
#ifndef __CPLAYER_H__
#define __CPLAYER_H__

#include "../core/Ator.h"
#include "../core/GerenteAtor.h"
#include "../core/FW_Resource.h"

class CPlayer : public Ator
{
public:
	bool vivo;
	bool galvao;

	CPlayer(GerenteAtor& _gerente,int _posX,int _posY);

	float pegaX();
	float pegaY();
		
	bool estaNoJogo();
	void inicializar();		
	void atualizar();	
	void desenhar();
	void finalizar();

	~CPlayer();
private:
	FW_Image* image;
	FW_Image* aviso;
	int posX;
	int posY;
	int dir;
	int indice;
	int tempo;
	float angleAviso;
	bool desenhaAviso;
};

#endif //__CPLAYER_H__