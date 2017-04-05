
#include "../Main.hpp"

#include "../core/FW_Entrada.h"
#include "../core/FW_Resource.h"

#include "RPlay.h"
#include "RSelJoga.h"
#include "RGameOver.h"

#include "../classes/CFimJogo.hpp"
#include "../classes/CInimigoV.hpp"
#include "../classes/CInimigoH.hpp"
#include "../classes/CInimigoDiag.hpp"
#include "../classes/CInimigoBH.hpp"
#include "../classes/CInimigoBV.hpp"
#include "../classes/CInimigoBD.hpp"
#include "../core/GameLoop.h"

#include "../classes/CParticle.hpp"
#include "../classes/CTile.hpp"

RPlay::RPlay(char* _caminho)
	:caminho(_caminho)
{
	acabou = 150;
	textureLuz = 255;
}


void RPlay::inicializar(GameLoop* _gameloop)
{
	gameloop = _gameloop;

	fase = FW_CarregaJogo(caminho);
	
	gerente = new GerenteAtor(*gameloop);

	SDL_Surface* Btemp = IMG_Load("DATA/img/background.png");
	SDL_Surface* Ftemp = IMG_Load("DATA/img/frontground.png");

	frontgound = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/frontground.png",0,0);

	HUD = FW_carregaSprite(gameloop->renderer,"DATA/img/scenario/HUD.png",0,0);

	peixe = new CPlayer(*gerente,32,96);

	RESOURCE.tocaMusica("musica.wav");

	for(int i=0;i<70;i++)
	{
		gerente->adicionar(new CParticle(*gerente));
	}

	//carrega arquivo
	

	//cria os tiles
	for(int i=0;i<32;i++)
	{
		for(int j=0;j<24;j++)
		{
			switch(fase->mapa[i][j])
			{
				case 1:
					gerente->adicionar(new CTile(*gerente,i*32,j*32));
					break;
				case 2:
					gerente->adicionar(new CInimigoV(*gerente, i*32, j*32));
					break;
				case 3:
					gerente->adicionar(new CInimigoH(*gerente, i*32, j*32));
					break;
				case 4:
					gerente->adicionar(new CInimigoDiag(*gerente, i*32, j*32));
					break;
				case 5:
					gerente->adicionar(new CInimigoBH(*gerente, i*32,j*32));
					break;
				case 6:
					gerente->adicionar(new CInimigoBV(*gerente,i*32,j*32));
					break;
				case 7:
					gerente->adicionar(new CInimigoBD(*gerente,i*32,j*32));
					break;
				case 99:
					interruptor = new CFimJogo(*gerente,i*32,j*32);
					gerente->adicionar(interruptor);
					break;

			}
		}

	}

	//muda o fundo
	switch(fase->fundo)
	{
	case 1:
		background = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea1.png",0,0);
		break;
	case 2:
		background = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea2.png",0,0);
		break;
	case 3:
		background = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea3.png",0,0);
		break;
	case 4:
		background = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea4.png",0,0);
		break;
	case 5:
		background = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea5.png",0,0);
		break;
	case 6:
		background = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea6.png",0,0);
		break;
	}

	desenhaLuz = false;

	gerente->adicionar( peixe );
	
}

void RPlay::atualizar()
{
	FW_Botao* teclado = ENTRADA.pegaTecla();
	FW_Mouse* mouse = ENTRADA.pegaMouse();
	FW_Controle* controle = ENTRADA.pegaControle();

	gerente->atualizar();

	if(mouse->botoes[FW_MMEIO].pressionado || controle->botoes[FWX_R3].pressionado)
		desenhaLuz = (desenhaLuz)? false : true;
}

void RPlay::desenhar()
{

	FW_desenhaSprite(gameloop->renderer,background,0,0,0);

	gerente->desenhar();

	if(desenhaLuz)
		FW_desenhaSprite(gameloop->renderer,frontgound,0,peixe->pegaX() - 1008, peixe->pegaY() - 752);

	FW_desenhaSprite(gameloop->renderer,HUD,0,0,0);

}

void RPlay::finalizar()
{
	FW_removeSprite( background );
	FW_removeSprite( frontgound );
	
	RESOURCE.removeMusica();

	delete gerente;
}

Tela* RPlay::proximaTela()
{
	FW_Botao* tecla = ENTRADA.pegaTecla();
	FW_Controle* controle = ENTRADA.pegaControle();

	if(tecla[FW_ESC].pressionado || tecla[FW_ENCERRA].pressionado || acabou==0 || controle->botoes[FWX_SELECT].pressionado)
		return new RSelJoga;

	if(!peixe->vivo)
		return new RGameOver(caminho,0,0);

	if(peixe->galvao)
	{
		acabou--;
		if(textureLuz > 4)
		{
			textureLuz-=4;
			SDL_SetTextureAlphaMod(frontgound->texture,textureLuz);
		}
	}

	return this;
}
