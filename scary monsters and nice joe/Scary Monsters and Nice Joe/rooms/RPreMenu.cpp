
#include "../Main.hpp"

#include "../core/FW_Entrada.h"

#include "CMenu.hpp"

#include "RPreMenu.h"

RPreMenu::RPreMenu()
{
	tempo = -1;
	fade = 255;
	cobraTempo = cobraQuadro = 0;
	joeQuadro = joeTempo = 0;
	desenhaCobra = desenhaJoe = false;
	cobraX = -250;
	cobraY = 64;
}

void RPreMenu::inicializar(GameLoop* _gameloop)
{
	SDL_ShowCursor(0);
	galvao = false;
	gameloop = _gameloop;
	joe = FW_carregaSprite(gameloop->renderer,"DATA/img/menu/nicejoe.png",270,160);
	cobra = FW_carregaSprite(gameloop->renderer,"DATA/img/menu/cobra_anima.png",250,200);
	cobraAnda = FW_carregaSprite(gameloop->renderer,"DATA/img/menu/cobra_anda.png",250,200);
	//logo = FW_carregaSprite(gameloop->renderer,"DATA/img/logo.png",0,0);
}

void RPreMenu::atualizar()
{
	tempo++;

	if(fade > 4)
		fade-=4;

	if(!desenhaCobra)
	{
		if(cobraX < ((909/2) - 125))
			cobraX += 4;
		else
		{
			desenhaCobra = true;
			cobraQuadro = 0;
			cobraTempo = 0;
		}
	}
}

void RPreMenu::desenhar()
{
	cobraTempo++;

	if(cobraTempo == 5)
	{
		cobraTempo = 0;
		if(!desenhaCobra)
			cobraQuadro = (cobraQuadro+1)%4;
		else
			if(cobraQuadro<20)
				cobraQuadro++;
	}

	if(cobraQuadro == 20)
		desenhaJoe = true;

	if(!desenhaCobra)
	{
		FW_desenhaSprite(gameloop->renderer,cobraAnda,cobraQuadro,cobraX,cobraY);
	}
	else
		FW_desenhaSprite(gameloop->renderer,cobra,cobraQuadro,cobraX,cobraY);

	if(desenhaJoe)
	{
		joeTempo++;
		if(joeTempo == 5)
		{
			joeTempo = 0;
			joeQuadro++;
		}

		if(joeQuadro == 14)
			galvao = true;

		FW_desenhaSprite(gameloop->renderer,joe,joeQuadro,cobraX+96,cobraY+112);
	}


	SDL_SetRenderDrawBlendMode(gameloop->renderer,SDL_BLENDMODE_BLEND);

	SDL_Rect a;
	a.x = a.y = 0;

	a.w = 1024;
	a.h = 768;

	SDL_SetRenderDrawColor(gameloop->renderer,0,0,0,fade);

	SDL_RenderFillRect(gameloop->renderer,&a);
}

void RPreMenu::finalizar()
{
	//FW_removeSprite(logo);
}

Tela* RPreMenu::proximaTela()
{
	FW_Botao* teclado = ENTRADA.pegaTecla();
	FW_Controle* controle = ENTRADA.pegaControle();

	if (galvao)
		return new CMenu;

	if(teclado[FW_ESC].pressionado || teclado[FW_ENCERRA].pressionado || teclado[FW_Z].pressionado || teclado[FW_ENTER].pressionado || teclado[FW_ESPACO].pressionado || controle->botoes[FWX_A].pressionado)
		return new CMenu;

	return this;
}