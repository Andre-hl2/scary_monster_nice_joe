
#include "../Main.hpp"

#include "../core/FW_Entrada.h"

#include "CMenu.hpp"
#include "RPreMenu.h"

#include "RLogo.h"

RLogo::RLogo()
{
	tempo = -1;
	fade = 255;
}

void RLogo::inicializar(GameLoop* _gameloop)
{
	SDL_ShowCursor(0);
	apareceno = true;
	desapareceno = false;
	galvao = false;
	gameloop = _gameloop;
	logo = FW_carregaSprite(gameloop->renderer,"DATA/img/logo.png",0,0);
}

void RLogo::atualizar()
{
	if(tempo > 0)
		tempo--;
	if(tempo == 0)
		desapareceno = true;

	if(apareceno)
	{
		if(fade >=4)
			fade-=4;
		else	
		{
			apareceno = false;
			tempo = 30;
		}
	}

	if(desapareceno)
	{
		if(fade <= 250)
			fade+=4;
		else
			galvao = true;
	}
}

void RLogo::desenhar()
{
	FW_desenhaSprite(gameloop->renderer,logo,0,500,468);

	SDL_SetRenderDrawBlendMode(gameloop->renderer,SDL_BLENDMODE_BLEND);

	SDL_Rect a;
	a.x = a.y = 0;

	a.w = 1024;
	a.h = 768;

	SDL_SetRenderDrawColor(gameloop->renderer,0,0,0,fade);

	SDL_RenderFillRect(gameloop->renderer,&a);
}

void RLogo::finalizar()
{
	FW_removeSprite(logo);
}

Tela* RLogo::proximaTela()
{
	FW_Botao* teclado = ENTRADA.pegaTecla();
	FW_Controle* controle = ENTRADA.pegaControle();

	if (galvao || teclado[FW_ENTER].pressionado || teclado[FW_Z].pressionado || teclado[FW_ESPACO].pressionado || controle->botoes[FWX_A].pressionado)
		return new RPreMenu;

	if(teclado[FW_ESC].pressionado || teclado[FW_ENCERRA].pressionado)
		return nullptr;

	return this;
}