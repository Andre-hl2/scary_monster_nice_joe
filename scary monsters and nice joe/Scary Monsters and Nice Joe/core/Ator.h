#pragma once

//defines para especies de ator
#define JOGADOR 1
#define INIMIGO 2
#define TILE	3
#define BONUS	4
#define FIMJOGO 5

#include <SDL.h>

class GerenteAtor;

class Ator
{
	//protected:
public:
		GerenteAtor& gerente;
		SDL_Rect box;

	public:		
		//especie de ator
		int especie;
		Ator(GerenteAtor& _gerente);

		virtual float pegaX()		= 0;
		virtual float pegaY()		= 0;
		
		virtual bool estaNoJogo()	= 0;
		virtual void inicializar()	= 0;		
		virtual void atualizar()	= 0;	
		virtual void desenhar()		= 0;
		virtual void finalizar()	= 0;
		virtual ~Ator() {};
};

