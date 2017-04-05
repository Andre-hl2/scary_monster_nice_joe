
#include "../Main.hpp"
#include "../core/GameLoop.h"
#include "RSelEdit.h"

#include "REdit.h"

#include "../core/FW_Entrada.h"
#include "../core/FW_Resource.h"

#include "../classes/CTile.hpp"
#include "../classes/CEditor.hpp"

#define ESCOLHENDO  1
#define EDITANDO	2

void bucketTile2(FW_Save* fase,int x, int y,int valorMouse);

REdit::REdit(char* _caminho)
	:caminho(_caminho)
{
}


void REdit::inicializar(GameLoop* _gameloop)
{
	estado = EDITANDO;

	gameloop = _gameloop;

	SDL_ShowCursor(1);

	fase = FW_CarregaJogo(caminho);

	gerente = new GerenteAtor(*gameloop);

	SDL_Surface* Btemp = IMG_Load("DATA/img/background.png");
	
	//HUD
	HUD = FW_carregaSprite(gameloop->renderer,"DATA/img/scenario/hud.png",0,0);
	sFundo = new CButton(gameloop,"DATA/img/botoes/editor/b_Fundo.png",208,16,64,32);
	sTile = new CButton(gameloop,"DATA/img/botoes/editor/b_Parede.png",688,16,64,32);
	sMusica = new CButton(gameloop,"DATA/img/botoes/editor/b_Musica.png",528,16,64,32);
	sInimigo = new CButton(gameloop,"DATA/img/botoes/editor/b_Inimigo.png",368,16,64,32);
	sTempo = new CButton(gameloop,"DATA/img/botoes/editor/tempo.png",848,16,64,32);
	sSalvar = new CButton(gameloop,"DATA/img/botoes/editor/salvar.png",48,16,64,32);

	//Backgrounds
	background1 = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea1.png",0,0);
	background2 = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea2.png",0,0);
	background3 = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea3.png",0,0);
	background4 = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea4.png",0,0);
	background5 = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea5.png",0,0);
	background6 = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea6.png",0,0);

	//itens fixos
	peixe = FW_carregaSprite(gerente->gameloop.renderer,"DATA/img/jogador/joe_normal.png",32,32);
	fim =	FW_carregaSprite(gerente->gameloop.renderer,"DATA/img/jogador/fimJogo.png",32,32);

	//Tiles
	tileCoral = FW_carregaSprite(gameloop->renderer,"DATA/img/tiles/coralCria.png",0,0);
	tileCoralA = FW_carregaSprite(gameloop->renderer,"DATA/img/tiles/coralCria.png",0,0);

	SDL_SetTextureAlphaMod(tileCoralA->texture,150);

	tileNeve = FW_carregaSprite(gameloop->renderer,"DATA/img/tiles/tileNeve.png",32,32);
	tileNeveA = FW_carregaSprite(gameloop->renderer,"DATA/img/tiles/tileNeve.png",32,32);

	SDL_SetTextureAlphaMod(tileNeveA->texture,150);

	tileRocha = FW_carregaSprite(gameloop->renderer,"DATA/img/tiles/tileRocha.png",32,32);
	tileRochaA = FW_carregaSprite(gameloop->renderer,"DATA/img/tiles/tileRocha.png",32,32);

	SDL_SetTextureAlphaMod(tileRochaA->texture,150);

	tilePreto = FW_carregaSprite(gameloop->renderer,"DATA/img/tiles/tilePreto.png",32,32);
	tilePretoA = FW_carregaSprite(gameloop->renderer,"DATA/img/tiles/tilePreto.png",32,32);

	SDL_SetTextureAlphaMod(tilePretoA->texture,100);

	//Inimigos
	inimigoV =  FW_carregaSprite(gameloop->renderer, "DATA/img/inimigos/inimigoV.png", 32,32);
	inimigoVA = FW_carregaSprite(gameloop->renderer, "DATA/img/inimigos/inimigoV.png",32,32);

	SDL_SetTextureAlphaMod(inimigoVA->texture, 150);

	inimigoH =  FW_carregaSprite(gameloop->renderer, "DATA/img/inimigos/inimigoH.png", 32,32);
	inimigoHA = FW_carregaSprite(gameloop->renderer, "DATA/img/inimigos/inimigoH.png", 32,32);

	SDL_SetTextureAlphaMod(inimigoHA->texture, 150);

	inimigoDiag =  FW_carregaSprite(gameloop->renderer, "DATA/img/inimigos/inimigoDiag.png", 32,32);
	inimigoDiagA = FW_carregaSprite(gameloop->renderer, "DATA/img/inimigos/inimigoDiag.png", 32,32);

	SDL_SetTextureAlphaMod(inimigoDiagA->texture, 150);
	
	inimigoBH = FW_carregaSprite(gameloop->renderer,"DATA/img/inimigos/inimigoBH.png",64,64);
	inimigoBHA = FW_carregaSprite(gameloop->renderer,"DATA/img/inimigos/inimigoBH.png",64,64);

	SDL_SetTextureAlphaMod( inimigoBHA->texture,150);

	inimigoBV = FW_carregaSprite(gameloop->renderer,"DATA/img/inimigos/inimigoBV.png",64,64);
	inimigoBVA = FW_carregaSprite(gameloop->renderer,"DATA/img/inimigos/inimigoBV.png",64,64);

	SDL_SetTextureAlphaMod( inimigoBVA->texture,150);

	inimigoBD = FW_carregaSprite(gameloop->renderer,"DATA/img/inimigos/inimigoBD.png",64,64);
	inimigoBDA = FW_carregaSprite(gameloop->renderer,"DATA/img/inimigos/inimigoBD.png",64,64);

	SDL_SetTextureAlphaMod( inimigoBDA->texture,150);

}

void REdit::atualizar()
{
	FW_Botao* teclado = ENTRADA.pegaTecla();
	FW_Mouse* mouse = ENTRADA.pegaMouse();
	gerente->atualizar();

	switch(estado)
	{
	case EDITANDO:
		{

			if(teclado[FW_ESPACO].pressionado || sSalvar->pressed())
			{
				FW_SalvaJogo(caminho,*fase);
			}
				
			if(mouse->botoes[FW_MESQUERDO].ativo)
			{
				fase->mapa[ mouse->x / 32][ mouse->y/32] = valorMouse;
			}

			if(mouse->botoes[FW_MDIREITO].ativo)
			{
				fase->mapa[ mouse->x/32][ mouse->y/32] = 0;
			}

			if(mouse->botoes[FW_MMEIO].pressionado)
			{
				bucketTile2(fase,mouse->x/32,mouse->y/32,valorMouse);
			}

			if(sFundo->pressed())
			{
				gerente->adicionar(new CEditor(*gerente,fase,208,-400,FUNDO,&estado));
				estado = ESCOLHENDO;
			}

			if(sMusica->pressed())
			{
				gerente->adicionar(new CEditor(*gerente,fase,528,-400,MUSICA,&estado));
				estado = ESCOLHENDO;
			}

			if(sTile->pressed())
			{
				gerente->adicionar(new CEditor(*gerente,fase,688,-400,PAREDE,&estado,&valorMouse));
				estado = ESCOLHENDO;
			}

			if(sInimigo->pressed())
			{
				gerente->adicionar(new CEditor(*gerente,fase,368,-400,INIMIGOS,&estado,&valorMouse));
				estado = ESCOLHENDO;
			}

			if(sTempo->pressed())
			{
				gerente->adicionar(new CEditor(*gerente,fase,368,-400,TEMPO,&estado));
				estado = ESCOLHENDO;
			}

		}
		break;
	case ESCOLHENDO:
		{
		}
		break;
	}

	fase->mapa[30][21] = 99;
	fase->mapa[1][3] = 100;

	for(int i=0;i<32;i++)
	{
		for(int j=0;j<24;j++)
		{
			if(i==0 || i==31 || j==0 || j==23 || j == 22 || j == 1 || j == 2)
				fase->mapa[i][j] = 1;
		}
	}
}

void bucketTile2(FW_Save* fase,int x, int y,int valorMouse)
{

	fase->mapa[x][y] = valorMouse;

	if(fase->mapa[x][y-1] == 0)
		bucketTile2(fase,x,y-1,valorMouse);

	if(fase->mapa[x-1][y] == 0)
		bucketTile2(fase,x-1,y,valorMouse);

	if(fase->mapa[x+1][y] == 0)
		bucketTile2(fase,x+1,y,valorMouse);
	
	if(fase->mapa[x][y+1] == 0)
		bucketTile2(fase,x,y+1,valorMouse);

	
}

void REdit::desenhar()
{

	FW_Mouse* mouse = ENTRADA.pegaMouse();

	switch(fase->fundo)
	{
	case 1:
		FW_desenhaSprite( gameloop->renderer, background1, 0, 0, 0);
		break;
	case 2:
		FW_desenhaSprite( gameloop->renderer, background2, 0, 0, 0);
		break;
	case 3:
		FW_desenhaSprite( gameloop->renderer, background3, 0, 0, 0);
		break;
	case 4:
		FW_desenhaSprite( gameloop->renderer, background4, 0, 0, 0);
		break;
	case 5:
		FW_desenhaSprite( gameloop->renderer, background5, 0, 0, 0);
		break;
	case 6:
		FW_desenhaSprite( gameloop->renderer, background6, 0, 0, 0);
		break;
	}

	
	
	for(int i=0;i<32;i++)
	{
		for(int j=0;j<24;j++)
		{
			switch(fase->mapa[i][j])
			{
			case 1: 
				switch(fase->tile)
				{
				case 1:
					FW_desenhaSprite(gameloop->renderer,tileCoral,0,i*32,j*32); 
					break;
				case 2:
					FW_desenhaSprite(gameloop->renderer,tileNeve,0,i*32,j*32);
					break;
				case 3:
					FW_desenhaSprite(gameloop->renderer,tileRocha,0,i*32,j*32);
					break;
				case 4:
					FW_desenhaSprite(gameloop->renderer,tilePreto,0,i*32,j*32);
					break;

				}
				break;
			case 2: 
				FW_desenhaSprite(gameloop->renderer, inimigoV, 0, i*32, j*32); 
				break;
			case 3:
				FW_desenhaSprite(gameloop->renderer, inimigoH, 0, i*32, j*32);
				break;
			case 4:
				FW_desenhaSprite(gameloop->renderer, inimigoDiag, 0, i*32, j*32);
				break;
			case 5:
				FW_desenhaSprite(gameloop->renderer, inimigoBH, 0, i*32, j*32);
				break;
			case 6:
				FW_desenhaSprite(gameloop->renderer, inimigoBV, 0, i*32, j*32);
				break;
			case 7:
				FW_desenhaSprite(gameloop->renderer, inimigoBD, 0, i*32, j*32);
				break;
			case 99:
				FW_desenhaSprite(gameloop->renderer, fim, 0, i*32,j*32);
				break;
			case 100:
				FW_desenhaSprite(gameloop->renderer,peixe,0,i*32,j*32);
				break;
			}	
		}
	}

	

	switch(valorMouse)
	{
	case 1: 
		switch(fase->tile)
		{
		case 1:
			FW_desenhaSprite(gameloop->renderer,tileCoralA,0,(mouse->x/32)*32,(mouse->y/32)*32);
			break;
		case 2:
			FW_desenhaSprite(gameloop->renderer,tileNeveA,0,(mouse->x/32)*32,(mouse->y/32)*32);
			break;
		case 3:
			FW_desenhaSprite(gameloop->renderer,tileRochaA,0,(mouse->x/32)*32,(mouse->y/32)*32);
			break;
		case 4:
			FW_desenhaSprite(gameloop->renderer,tilePretoA,0,(mouse->x/32)*32,(mouse->y/32)*32);
			break;
		}
		break;
	case 2:
		FW_desenhaSprite(gameloop->renderer, inimigoVA,0, (mouse->x/32)*32,(mouse->y/32)*32);
		break;
	case 3: 
		FW_desenhaSprite(gameloop->renderer, inimigoHA,0, (mouse->x/32)*32, (mouse->y/32)*32);
		break;
	case 4:
		FW_desenhaSprite(gameloop->renderer, inimigoDiagA,0, (mouse->x/32)*32, (mouse->y/32)*32);
		break;
	case 5:
		FW_desenhaSprite(gameloop->renderer, inimigoBHA,0, (mouse->x/32)*32, (mouse->y/32)*32);
		break;
	case 6:
		FW_desenhaSprite(gameloop->renderer, inimigoBVA,0, (mouse->x/32)*32, (mouse->y/32)*32);
		break;
	case 7:
		FW_desenhaSprite(gameloop->renderer, inimigoBDA,0, (mouse->x/32)*32, (mouse->y/32)*32);
		break;

	}
	SDL_Rect fill;

	fill.x = (mouse->x/32)*32;
	fill.y = (mouse->y/32)*32;
	fill.w = 32;
	fill.h = 32;

	

	

	for(int i=0;i<32;i++)
	{
		SDL_SetRenderDrawColor(gameloop->renderer,100,100,100,200);
		SDL_RenderDrawLine(gameloop->renderer,i*32,0,i*32,1024);
		SDL_RenderDrawLine(gameloop->renderer,0,i*32,1024,i*32);
	}

	SDL_SetRenderDrawColor(gameloop->renderer,0,150,0,150);

	//SDL_RenderDrawRect(gameloop->renderer,&fill);	

	gerente->desenhar();


	FW_desenhaSprite(gameloop->renderer,HUD,0,0,0);
	sFundo->draw();
	sTile->draw();
	sMusica->draw();
	sInimigo->draw();
	sTempo->draw();
	sSalvar->draw();

}

void REdit::finalizar()
{
	FW_removeSprite( HUD );

	FW_removeSprite( background1 );
	FW_removeSprite( background2 );
	FW_removeSprite( background3 );
	FW_removeSprite( background4 );
	FW_removeSprite( background5 );

	FW_removeSprite( peixe );
	FW_removeSprite( tileCoral );
	FW_removeSprite( tileCoralA );
	FW_removeSprite( tileNeve );
	FW_removeSprite( tileNeveA );
	FW_removeSprite( tileRocha );
	FW_removeSprite( tileRochaA );
	FW_removeSprite( tilePreto );
	FW_removeSprite( tilePretoA );
	FW_removeSprite( inimigoV );
	FW_removeSprite( inimigoVA);
	FW_removeSprite( inimigoDiag );
	FW_removeSprite( inimigoDiagA);
	FW_removeSprite( inimigoH );
	FW_removeSprite( inimigoHA);
	FW_removeSprite( inimigoBH );
	FW_removeSprite( inimigoBHA);
	FW_removeSprite( inimigoBV );
	FW_removeSprite( inimigoBVA);
	FW_removeSprite( inimigoBD );
	FW_removeSprite( inimigoBDA);
	SDL_ShowCursor(1);

	delete sTile;
	delete sFundo;
	delete sMusica;
	delete sInimigo;
	delete sTempo;
	delete sSalvar;

	delete gerente;
}

Tela* REdit::proximaTela()
{
	FW_Botao* tecla = ENTRADA.pegaTecla();

	if(tecla[FW_ESC].pressionado || tecla[FW_ENCERRA].pressionado)
		return new RSelEdit;

	return this;
}
