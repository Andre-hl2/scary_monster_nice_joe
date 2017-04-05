
#include "../Main.hpp"

#include "RSelCria.h"
#include "RSelJoga.h"
#include "RSelEdit.h"
#include "RTesta.h"

#include "CMenu.hpp"

#include "../classes/CParticle.hpp"

#include "../core/FW_Entrada.h"


void CMenu::inicializar(GameLoop* _gameloop)
{
	SDL_ShowCursor(0);
	
	gameloop = _gameloop;

	gerente = new GerenteAtor(*gameloop);
	
	option = 1;

	peixe = FW_carregaSprite(gameloop->renderer,"DATA/img/jogador/joe_normal.png",32,32);

	tempoPeixe = 0;
	indicePeixe = 0;

	background = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea3.png",0,0);

	play = new CChoice(gameloop, "DATA/img/botoes/joga.png",400,450,200,100,&option,1);
	edit = new CChoice(gameloop, "DATA/img/botoes/edita.png",400,500,200,100,&option,2);
	create = new CChoice(gameloop, "DATA/img/botoes/cria.png",400,550,200,100,&option,3);
	testa = new CChoice(gameloop, "DATA/img/botoes/testa.png",400,600,200,100,&option,4);

	cobra = FW_carregaSprite(gameloop->renderer,"DATA/img/menu/cobra_anima.png",250,200);
	joe = FW_carregaSprite(gameloop->renderer,"DATA/img/menu/nicejoe.png",270,160);

	for(int i=0;i<30;i++)
	{
		gerente->adicionar(new CParticle(*gerente));
	}

	fade = 255;
	boxFade.x = 0;
	boxFade.y = 0;
	boxFade.w = 1024;
	boxFade.h = 768;

}

void CMenu::atualizar()
{
	gerente->atualizar();

	FW_Botao* teclado = ENTRADA.pegaTecla();
	FW_Controle* controle = ENTRADA.pegaControle();

	if(controle->plugado)
	{
		if(controle->botoes[FWX_DUP].pressionado)
			if(option > 1)
				option--;
		if(controle->botoes[FWX_DDOWN].liberado)
			if(option < 4)
				option++;
	}

	if(teclado[FW_CIMA].pressionado || teclado[FW_W].pressionado)
		if(option > 1)
			option--;

	if(teclado[FW_BAIXO].pressionado || teclado[FW_S].pressionado)
		if(option < 4)
			option++;
}

void CMenu::desenhar()
{
	FW_desenhaSprite( gameloop->renderer, background, 0,0,0);

	gerente->desenhar();

	tempoPeixe++;
	if(tempoPeixe >= 15)
	{
		tempoPeixe = 0;
		indicePeixe = (indicePeixe+1)%8;
	}

	
	switch(option)
	{
	case 1:
		FW_desenhaSprite(gameloop->renderer,peixe,indicePeixe, 370, 500-16);
		break;
	case 2:
		FW_desenhaSprite(gameloop->renderer,peixe,indicePeixe, 370, 550-16);
		break;
	case 3:
		FW_desenhaSprite(gameloop->renderer,peixe,indicePeixe, 370, 600-16);
		break;
	case 4:
		FW_desenhaSprite(gameloop->renderer,peixe,indicePeixe, 370, 650-16);
	}
	

	play->draw2();
	create->draw2();
	edit->draw2();
	testa->draw2();

	if(fade > 1)
		fade-=.5;

	SDL_SetRenderDrawBlendMode(gameloop->renderer,SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(gameloop->renderer,0,0,0,fade);

	SDL_RenderFillRect(gameloop->renderer,&boxFade);

	FW_desenhaSprite(gameloop->renderer,cobra,20,(909/2)-125,64);
	FW_desenhaSprite(gameloop->renderer,joe,13,((909/2)-125)+96,64+112);
}

void CMenu::finalizar()
{
	delete play;
	delete create;
	delete edit;
	delete testa;
	delete gerente;
	FW_removeSprite( background );
	FW_removeSprite( peixe );
}


Tela* CMenu::proximaTela()
{
	FW_Botao* teclado = ENTRADA.pegaTecla();
	FW_Controle* controle = ENTRADA.pegaControle();

	if(teclado[FW_ESPACO].pressionado || teclado[FW_ENTER].pressionado || teclado[FW_Z].pressionado || controle->botoes[FWX_A].pressionado)
	{
		switch(option)
		{
		case 1:
			return new RSelJoga;
			break;
		case 2:
			return new RSelEdit;
			break;
		case 3:
			break;
		case 4:
			return nullptr;
			break;
		}
	}


	if(teclado[FW_ESC].pressionado || controle->botoes[FWX_SELECT].pressionado)
		return nullptr;


	return this;
}
