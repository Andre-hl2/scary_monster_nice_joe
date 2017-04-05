#include "../Main.hpp"

#include "FW_Entrada.h"
#include "GameLoop.h"
#include "Tela.h"

#include <iostream>
#include <stdio.h>

using namespace std;


GameLoop::GameLoop(Tela* _tela)
	: tela(_tela)
{
}

bool GameLoop::executar(char* titulo, int largura, int altura,bool telaCheia)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Enable VSync
		if( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" ) )
		{
			printf( "Warning: VSync not enabled!" );
		}

		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Seed random
		srand( SDL_GetTicks() );

		//Create window
		if(telaCheia)
			window = SDL_CreateWindow( titulo, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, largura, altura, SDL_WINDOW_FULLSCREEN );
		else
			window = SDL_CreateWindow( titulo, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, largura, altura, SDL_WINDOW_SHOWN );

		SDL_Surface* icon = IMG_Load("DATA/img/icon.ico");

		SDL_SetWindowIcon(window,icon);

		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }

				 //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	GerenciadorTelas gerenciador(tela,this);

	while (!gerenciador.acabou())
	{

		//Clear screen
		SDL_SetRenderDrawColor( renderer,0,0,0,255);
		SDL_RenderClear( renderer );

		//atualiza a entrada de dados
		ENTRADA.atualiza();

		//funções referentes ao gerenciador de tela
		gerenciador.atualizar();
		gerenciador.desenhar();


		//Update screen
		SDL_RenderPresent( renderer);

		//função para padronizar o FPS

		// Inicializa e pega o tempo atual (só faz isso a primeira vez)
		static Uint32 tempoAnterior=0;
		// -- Espera 16ms entre cada quadro --      
		// Variável para o tempo atual
		int espera=(1000/60)-SDL_GetTicks()+tempoAnterior;
		if(espera > 0)
		   SDL_Delay(espera);
		tempoAnterior=SDL_GetTicks();
	}

	//Destroy window	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

	return true;
}

GameLoop::~GameLoop()
{
}