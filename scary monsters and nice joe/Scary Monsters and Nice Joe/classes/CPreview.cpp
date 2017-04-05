
#include "../Main.hpp"
#include "../core/GameLoop.h"
#include "../core/FW_Entrada.h"

#include "CPreview.hpp"

CPreview::CPreview(GameLoop* _gameloop,char* caminho,int _posX,int _posY, int* _option, int _Mnum)
	:gameloop(_gameloop),posX(_posX),posY(_posY),option(_option),Mnum(_Mnum)
{
	save = FW_CarregaJogo(caminho);
	perfil = FW_carregaPerfil("DATA/save.joe");

	if(perfil->passou == Mnum)
	{
		bloqueado= FW_carregaSprite(gameloop->renderer,"DATA/img/botoes/liberado.png",0,0);
	}
	else
	{
		bloqueado = FW_carregaSprite(gameloop->renderer, "DATA/img/botoes/bloqueado.png",0,0);
		SDL_SetTextureAlphaMod(bloqueado->texture,150);
	}	
}

bool CPreview::pressed()
{
	FW_Mouse* mouse = ENTRADA.pegaMouse();

	if( mouse->x > posX && mouse->x < posX+160 && mouse->y > posY && mouse->y < posY+120 && mouse->botoes[FW_MESQUERDO].pressionado && perfil->passou >= Mnum)
		return true;

	return false;
}

void CPreview::draw()
{
	if(save != NULL)
	{

		if(perfil->passou > Mnum)
		{

			if(*option == Mnum)
			{
				SDL_Rect a;
				a.x = posX- 5;
				a.y = posY -5;
				a.w = 170;
				a.h = 130;
				SDL_SetRenderDrawColor(gameloop->renderer,231,185,3,255);

				SDL_RenderFillRect(gameloop->renderer,&a);

			}

			for(int i=0;i<32;i++)
			{
				for(int j=0;j<24;j++)
				{
					SDL_Rect fill;
					fill.x = posX+(i*5);
					fill.y = posY+(j*5);
					fill.w = 5;
					fill.h = 5;
					switch(save->mapa[i][j])
					{
					case 1:
						SDL_SetRenderDrawColor(gameloop->renderer, 155,78,0,255);
						break;
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:						
						SDL_SetRenderDrawColor(gameloop->renderer, 255,0,0,255);
						break;
					case 99:
						SDL_SetRenderDrawColor(gameloop->renderer,255,255,255,255);
						break;
					case 100:
						SDL_SetRenderDrawColor(gameloop->renderer,255,255,0,255);
						break;
					default:
						SDL_SetRenderDrawColor(gameloop->renderer, 0,0,150,255);
						break;
					}
					SDL_RenderFillRect(gameloop->renderer, &fill);
				}			
			}
		}
		else
		{
			if(perfil->passou == Mnum)
			{
				if(*option == Mnum)
				{
					SDL_Rect a;
					a.x = posX- 5;
					a.y = posY -5;
					a.w = 170;
					a.h = 130;
					SDL_SetRenderDrawColor(gameloop->renderer,231,185,3,255);

					SDL_RenderFillRect(gameloop->renderer,&a);

				}
			}
			FW_desenhaSprite(gameloop->renderer,bloqueado,0,posX,posY);
		}
	}
}

CPreview::~CPreview()
{
	FW_removeSprite(bloqueado);
	delete save;
}