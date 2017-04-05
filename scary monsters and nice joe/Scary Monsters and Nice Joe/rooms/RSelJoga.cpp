
#include "../Main.hpp"

#include "RTesta.h"

#include "RPreMenu.h"
#include "RSelJoga.h"

#include "../core/FW_Entrada.h"


void RSelJoga::inicializar(GameLoop* _gameloop)
{
	gameloop = _gameloop;

	option = 1;

	background = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea3.png",0,0);

	fases = new CPreview*[15];

	perfil = FW_carregaPerfil("DATA/save.joe");

	fases[0] = new CPreview(gameloop,"DATA/stg/stg1.joe",48,224,&option,1);
	fases[1] = new CPreview(gameloop,"DATA/stg/stg2.joe",240,224,&option,2);
	fases[2] = new CPreview(gameloop,"DATA/stg/stg3.joe",432,224,&option,3);
	fases[3] = new CPreview(gameloop,"DATA/stg/stg4.joe",624,224,&option,4);
	fases[4] = new CPreview(gameloop,"DATA/stg/stg5.joe",816,224,&option,5);
	fases[5] = new CPreview(gameloop,"DATA/stg/stg6.joe",48,400,&option,6);
	fases[6] = new CPreview(gameloop,"DATA/stg/stg7.joe",240,400,&option,7);
	fases[7] = new CPreview(gameloop,"DATA/stg/stg8.joe",432,400,&option,8);
	fases[8] = new CPreview(gameloop,"DATA/stg/stg9.joe",624,400,&option,9);
	fases[9] = new CPreview(gameloop,"DATA/stg/stg10.joe",816,400,&option,10);
	fases[10] = new CPreview(gameloop,"DATA/stg/stg11.joe",48,546,&option,11);
	fases[11] = new CPreview(gameloop,"DATA/stg/stg12.joe",240,546,&option,12);
	fases[12] = new CPreview(gameloop,"DATA/stg/stg13.joe",432,546,&option,13);
	fases[13] = new CPreview(gameloop,"DATA/stg/stg14.joe",624,546,&option,14);
	fases[14] = new CPreview(gameloop,"DATA/stg/stg15.joe",816,546,&option,15);


	selecione = FW_carregaSprite( gameloop->renderer, "DATA/img/botoes/selecione1.png",0,0);
}

void RSelJoga::atualizar()
{
	FW_Botao* teclado = ENTRADA.pegaTecla();
	FW_Controle* controle = ENTRADA.pegaControle();

	if(teclado[FW_DIREITA].pressionado || controle->botoes[FWX_DRIGHT].pressionado || teclado[FW_D].pressionado)
		if(option < 15 && perfil->passou >= option+1)
			option++;

	if(teclado[FW_ESQUERDA].pressionado || teclado[FW_A].pressionado || controle->botoes[FWX_DLEFT].pressionado)
		if(option > 1)
			option--;

	if(teclado[FW_BAIXO].pressionado || teclado[FW_S].pressionado || controle->botoes[FWX_DDOWN].pressionado)
		if(option <= 10 && perfil->passou >= option+5)
			option+=5;

	if(teclado[FW_CIMA].pressionado || teclado[FW_W].pressionado || controle->botoes[FWX_DUP].pressionado)
		if(option >= 6 )
			option -=5;
}

void RSelJoga::desenhar()
{

	FW_desenhaSprite(gameloop->renderer, background, 0,0,0);

	FW_desenhaSprite( gameloop->renderer, selecione, 0, 512 - (545/2), 10);

	for (int i = 0;  i < 15;  i++)
	{
		fases[i]->draw();
	}
}

void RSelJoga::finalizar()
{
	delete[] fases;
}


Tela* RSelJoga::proximaTela()
{
	FW_Botao* teclado = ENTRADA.pegaTecla();
	FW_Controle* controle = ENTRADA.pegaControle();

	if(teclado[FW_ENTER].pressionado || teclado[FW_Z].pressionado || teclado[FW_ESPACO].pressionado || controle->botoes[FWX_A].pressionado)
	{
		return new RTesta(option);
	}
	
	if(teclado[FW_ESC].pressionado || controle->botoes[FWX_SELECT].pressionado)
		return new RPreMenu;

	if(teclado[FW_ENCERRA].pressionado)
		return nullptr;


	return this;
}
