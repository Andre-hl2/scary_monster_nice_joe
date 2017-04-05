#ifndef __GAMELOOP_H__
#define __GAMELOOP_H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "GerenciadorTelas.h"
#include <string>

class Tela;

class GameLoop
{
	private:
		Tela *tela;
		SDL_Window* window;
	public:

		//o renderer é publico pois evita vários problemas e facilita a vida do programador
		SDL_Renderer* renderer;

		GameLoop(Tela *_tela);
		bool executar(char* titulo, int largura=800, int altura=600,bool telaCheia = false);
		~GameLoop();
};

#endif //__GAMELOOP_H__

