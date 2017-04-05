
#include "../Main.hpp"

#include "../core/GameLoop.h"
#include "RGameOver.h"
#include "RSelCria.h"

#include "REdit.h"

#include "../core/FW_Entrada.h"
#include "../core/FW_Resource.h"

#include "../classes/CTile.hpp"

#include "CMenu.hpp"
#include "RPlay.h"
#include "RTesta.h"


RGameOver::RGameOver(char* _caminho,int _fase,int _morte)
	:caminho(_caminho),fase(_fase),morte(_morte)
{
	SDL_ShowCursor(1);

	fade = 255;
	boxFade.x = 0;
	boxFade.y = 0;
	boxFade.w = 1024;
	boxFade.h = 768;
}

void RGameOver::inicializar(GameLoop* _gameloop)
{
	gameloop = _gameloop;

	background = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/fimTempo.png",0,0);
	peixe = FW_carregaSprite(gameloop->renderer,"DATA/img/jogador/joe_normal.png",32,32);

	retry = new CButton(gameloop,"DATA/img/botoes/again.png",260,440,128,64);
	exit = new CButton(gameloop,"DATA/img/botoes/sair.png",580,440,128,64);

}

void RGameOver::atualizar()
{
}


void RGameOver::desenhar()
{	
	FW_Mouse* mouse = ENTRADA.pegaMouse();

	FW_desenhaSprite(gameloop->renderer,background,0,0,0);

	//FW_desenhaSprite(gameloop->renderer,peixe,0,mouse->x,mouse->y);

	exit->draw();
	retry->draw();

	if(fade > 1)
		fade-=.5;

	SDL_SetRenderDrawBlendMode(gameloop->renderer,SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(gameloop->renderer,0,0,0,fade);

	SDL_RenderFillRect(gameloop->renderer,&boxFade);

}

void RGameOver::finalizar()
{
	delete retry;
	delete exit;
	FW_removeSprite(background);
}

Tela* RGameOver::proximaTela()
{
	FW_Botao* teclado  = ENTRADA.pegaTecla();
	FW_Controle* controle = ENTRADA.pegaControle();

	if(retry->pressed() || teclado[FW_1].pressionado || controle->botoes[FWX_A].pressionado)
	{
		return new RTesta(fase,morte);
	}

	if(exit->pressed() || teclado[FW_2].pressionado || controle->botoes[FWX_B].pressionado || teclado[FW_ESC].pressionado)
		return new CMenu;
	

	return this;
}
