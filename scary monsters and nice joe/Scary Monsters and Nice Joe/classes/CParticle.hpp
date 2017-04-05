
#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "../core/GerenteAtor.h"
#include "../core/Ator.h"
#include "../core/FW_Resource.h"

class CParticle : public Ator
{
public:
	CParticle(GerenteAtor& _gerente);

	void init();
	void redirect();

	float pegaX();
	float pegaY();
		
	bool estaNoJogo();
	void inicializar();		
	void atualizar();	
	void desenhar();
	void finalizar();

	~CParticle();
private:
	FW_Image* image;

	int tempo;

	float posX;
	float posY;

	float hspeed, vspeed;
};

#endif //__PARTICLE_H__