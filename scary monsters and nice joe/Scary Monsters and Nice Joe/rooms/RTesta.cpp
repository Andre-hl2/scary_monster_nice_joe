
#include "../Main.hpp"

#include "../core/FW_Entrada.h"
#include "../core/FW_Resource.h"

#include "RTesta.h"
#include "RPreMenu.h"
#include "RGameOver.h"
#include "RPassou.h"

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

RTesta::RTesta(int _fase,int _morte)
	:Nfase(_fase),morte(_morte)
{
	acabou = 150;
	textureLuz = 255;
}


void RTesta::inicializar(GameLoop* _gameloop)
{
	gameloop = _gameloop;


	tempoFase = 0;

	switch(Nfase)
	{
	case 1:
		caminho = "DATA/stg/stg1.joe";
		break;
	case 2:
		caminho = "DATA/stg/stg2.joe";
		break;
	case 3:
		caminho = "DATA/stg/stg3.joe";
		break;
	case 4:
		caminho = "DATA/stg/stg4.joe";
		break;
	case 5:
		caminho = "DATA/stg/stg5.joe";
		break;
	case 6:
		caminho = "DATA/stg/stg6.joe";
		break;
	case 7:
		caminho = "DATA/stg/stg7.joe";
		break;
	case 8:
		caminho = "DATA/stg/stg8.joe";
		break;
	case 9:
		caminho = "DATA/stg/stg9.joe";
		break;
	case 10:
		caminho = "DATA/stg/stg10.joe";
		break;
	case 11:
		caminho = "DATA/stg/stg11.joe";
		break;
	case 12:
		caminho = "DATA/stg/stg12.joe";
		break;
	case 13:
		caminho = "DATA/stg/stg13.joe";
		break;
	case 14:
		caminho = "DATA/stg/stg14.joe";
		break;
	case 15:
		caminho = "DATA/stg/stg15.joe";
		break;
	}

	fase = FW_CarregaJogo(caminho);
	
	gerente = new GerenteAtor(*gameloop);

	hud = new CHUD(*gameloop,*fase,Nfase-1);

	SDL_Surface* Btemp = IMG_Load("DATA/img/background.png");
	SDL_Surface* Ftemp = IMG_Load("DATA/img/frontground.png");

	frontgound = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/frontground.png",0,0);


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
					gerente->adicionar(new CTile(*gerente,i*32,j*32,fase->tile));
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

	desenhaLuz = true;

	gerente->adicionar( peixe );

	SDL_Color cor = {255,255,255 };
	char text[10];
	sprintf(text,"%d",morte);
	texto = FW_CarregaTextoFonte(gameloop->renderer,"DATA/arial.tff",text,cor);
	
}

void RTesta::atualizar()
{
	FW_Botao* teclado = ENTRADA.pegaTecla();
	FW_Mouse* mouse = ENTRADA.pegaMouse();
	FW_Controle* controle = ENTRADA.pegaControle();

	gerente->atualizar();

	if(mouse->botoes[FW_MMEIO].pressionado || controle->botoes[FWX_R3].pressionado)
		desenhaLuz = (desenhaLuz)? false : true;

	hud->atualiza();

	tempoFase++;
	if(tempoFase == 60)
	{
		fase->tempo--;
		tempoFase = 0;
	}
}

void RTesta::desenhar()
{

	FW_desenhaSprite(gameloop->renderer,background,0,0,0);

	gerente->desenhar();

	if(desenhaLuz)
		FW_desenhaSprite(gameloop->renderer,frontgound,0,peixe->pegaX() - 1008, peixe->pegaY() - 752);

	hud->desenha();

	FW_desenhaSprite(gameloop->renderer,texto,0, 913,10);
}

void RTesta::finalizar()
{
	FW_removeSprite( background );
	FW_removeSprite( frontgound );
	
	RESOURCE.removeMusica();

	delete gerente;
}

Tela* RTesta::proximaTela()
{
	FW_Botao* tecla = ENTRADA.pegaTecla();
	FW_Controle* controle = ENTRADA.pegaControle();

	if(tecla[FW_ESC].pressionado || tecla[FW_ENCERRA].pressionado || controle->botoes[FWX_SELECT].pressionado)
		return new RPreMenu;


	if( acabou==0)
	{
		return new RPassou(Nfase);
	}

	if(!peixe->vivo)
		return new RTesta(Nfase,morte+1);

	if(fase->tempo <= 0)
		return new RGameOver(caminho,Nfase,morte);

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
