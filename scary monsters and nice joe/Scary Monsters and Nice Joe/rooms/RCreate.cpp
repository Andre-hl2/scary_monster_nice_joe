
#include "../Main.hpp"
#include "../core/GameLoop.h"
#include "RSelCria.h"

#include "RCreate.h"

#include "../core/FW_Entrada.h"
#include "../core/FW_Resource.h"

#include "../classes/CTile.hpp"


void bucketTile(FW_Save* fase,int x, int y,int valorMouse);

RCreate::RCreate(char* _caminho)
	:caminho(_caminho)
{
}


void RCreate::inicializar(GameLoop* _gameloop)
{
	gameloop = _gameloop;

	SDL_ShowCursor(0);

	fase = FW_limpaSave();

	gerente = new GerenteAtor(*gameloop);

	SDL_Surface* Btemp = IMG_Load("DATA/img/background.png");
	
	//Backgrounds
	background1 = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea1.png",0,0);
	background2 = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea2.png",0,0);
	background3 = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea3.png",0,0);

	//itens fixos
	peixe = FW_carregaSprite(gerente->gameloop.renderer,"DATA/img/jogador/joe_normal.png",32,32);
	fim =	FW_carregaSprite(gerente->gameloop.renderer,"DATA/img/jogador/fimJogo.png",32,32);

	//Tiles
	tileCoral = FW_carregaSprite(gameloop->renderer,"DATA/img/tiles/coralCria.png",0,0);
	tileA = FW_carregaSprite(gameloop->renderer,"DATA/img/tiles/coralCria.png",0,0);

	SDL_SetTextureAlphaMod(tileA->texture,150);

	//Inimigos
	inimigoV =  FW_carregaSprite(gameloop->renderer, "DATA/img/inimigos/inimigoV.png", 0,0);
	inimigoVA = FW_carregaSprite(gameloop->renderer, "DATA/img/inimigos/inimigoV.png", 0,0);

	SDL_SetTextureAlphaMod(inimigoVA->texture, 150);

	inimigoH =  FW_carregaSprite(gameloop->renderer, "DATA/img/inimigos/inimigoH.png", 0,0);
	inimigoHA = FW_carregaSprite(gameloop->renderer, "DATA/img/inimigos/inimigoH.png", 0,0);

	SDL_SetTextureAlphaMod(inimigoHA->texture, 150);

	inimigoDiag =  FW_carregaSprite(gameloop->renderer, "DATA/img/inimigos/inimigoDiag.png", 0,0);
	inimigoDiagA = FW_carregaSprite(gameloop->renderer, "DATA/img/inimigos/inimigoDiag.png", 0,0);

	SDL_SetTextureAlphaMod(inimigoDiagA->texture, 150);
	
	inimigoBH = FW_carregaSprite(gameloop->renderer,"DATA/img/inimigos/inimigoBH.png",0,0);
	inimigoBHA = FW_carregaSprite(gameloop->renderer,"DATA/img/inimigos/inimigoBH.png",0,0);

	SDL_SetTextureAlphaMod( inimigoBHA->texture,150);

	inimigoBV = FW_carregaSprite(gameloop->renderer,"DATA/img/inimigos/inimigoBV.png",0,0);
	inimigoBVA = FW_carregaSprite(gameloop->renderer,"DATA/img/inimigos/inimigoBV.png",0,0);

	SDL_SetTextureAlphaMod( inimigoBVA->texture,150);

	inimigoBD = FW_carregaSprite(gameloop->renderer,"DATA/img/inimigos/inimigoBD.png",0,0);
	inimigoBDA = FW_carregaSprite(gameloop->renderer,"DATA/img/inimigos/inimigoBD.png",0,0);

	SDL_SetTextureAlphaMod( inimigoBDA->texture,150);



	fase->fundo = 1;

	valorMouse = 1;
	
}

void RCreate::atualizar()
{
	FW_Botao* teclado = ENTRADA.pegaTecla();
	FW_Mouse* mouse = ENTRADA.pegaMouse();
	gerente->atualizar();

	if(teclado[FW_ESPACO].pressionado)
		FW_SalvaJogo(caminho,*fase);


	if(teclado[FW_1].pressionado)
		valorMouse = 1;

	if(teclado[FW_2].pressionado)
		valorMouse = 2;

	if(teclado[FW_3].pressionado)
		valorMouse = 3;

	if(teclado[FW_4].pressionado)
		valorMouse = 4;

	if(teclado[FW_5].pressionado)
		valorMouse = 5;

	if(teclado[FW_6].pressionado)
		valorMouse = 6;

	if(teclado[FW_7].pressionado)
		valorMouse = 7;

	
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
		bucketTile(fase,mouse->x/32,mouse->y/32,valorMouse);
	}


	//fundo
	if(teclado[FW_Z].pressionado)
		fase->fundo = 1;
	if(teclado[FW_X].pressionado)
		fase->fundo = 2;
	if(teclado[FW_C].pressionado)
		fase->fundo = 3;

	fase->mapa[30][21] = 99;
	fase->mapa[1][3] = 100;
}

void bucketTile(FW_Save* fase,int x, int y,int valorMouse)
{

	fase->mapa[x][y] = valorMouse;

	if(fase->mapa[x][y-1] == 0)
		bucketTile(fase,x,y-1,valorMouse);

	if(fase->mapa[x-1][y] == 0)
		bucketTile(fase,x-1,y,valorMouse);

	if(fase->mapa[x+1][y] == 0)
		bucketTile(fase,x+1,y,valorMouse);
	
	if(fase->mapa[x][y+1] == 0)
		bucketTile(fase,x,y+1,valorMouse);

	
}

void RCreate::desenhar()
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
	}
	gerente->desenhar();
	
	for(int i=0;i<32;i++)
	{
		for(int j=0;j<24;j++)
		{
			switch(fase->mapa[i][j])
			{
			case 1: 
				FW_desenhaSprite(gameloop->renderer,tileCoral,0,i*32,j*32); 
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
		FW_desenhaSprite(gameloop->renderer,tileA,0,(mouse->x/32)*32,(mouse->y/32)*32);
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

}

void RCreate::finalizar()
{
	FW_removeSprite( background1 );
	FW_removeSprite( background2 );
	FW_removeSprite( background3 );

	FW_removeSprite( peixe );
	FW_removeSprite( tileCoral );
	FW_removeSprite( tileA );
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
	delete gerente;
}

Tela* RCreate::proximaTela()
{
	FW_Botao* tecla = ENTRADA.pegaTecla();

	if(tecla[FW_ESC].pressionado || tecla[FW_ENCERRA].pressionado)
		return new RSelCria;

	return this;
}
