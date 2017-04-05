
#include "../Main.hpp"

#include "RCreate.h"

#include "RPreMenu.h"
#include "RSelCria.h"

#include "../core/FW_Entrada.h"


void RSelCria::inicializar(GameLoop* _gameloop)
{
	gameloop = _gameloop;

	option = 1;

	background = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/underSea3.png",0,0);

	fases = new CPreview*[15];

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

	selecione = FW_carregaSprite( gameloop->renderer, "DATA/img/botoes/selecione.png",0,0);
}

void RSelCria::atualizar()
{
	FW_Botao* teclado = ENTRADA.pegaTecla();
	FW_Controle* controle = ENTRADA.pegaControle();

	if(teclado[FW_DIREITA].pressionado || controle->botoes[FWX_DRIGHT].pressionado || teclado[FW_D].pressionado)
		if(option < 15)
			option++;

	if(teclado[FW_ESQUERDA].pressionado || teclado[FW_A].pressionado || controle->botoes[FWX_DLEFT].pressionado)
		if(option > 1)
			option--;

	if(teclado[FW_BAIXO].pressionado || teclado[FW_S].pressionado || controle->botoes[FWX_DDOWN].pressionado)
		if(option <= 10)
			option+=5;

	if(teclado[FW_CIMA].pressionado || teclado[FW_W].pressionado || controle->botoes[FWX_DUP].pressionado)
		if(option >= 6)
			option -=5;
}

void RSelCria::desenhar()
{

	FW_desenhaSprite(gameloop->renderer, background, 0,0,0);

	FW_desenhaSprite( gameloop->renderer, selecione, 0, 512 - (545/2), 10);

	for (int i = 0;  i < 15;  i++)
	{
		fases[i]->draw();
	}
}

void RSelCria::finalizar()
{
}


Tela* RSelCria::proximaTela()
{
	FW_Botao* teclado = ENTRADA.pegaTecla();
	FW_Controle* controle = ENTRADA.pegaControle();

	if(teclado[FW_ENTER].pressionado || teclado[FW_Z].pressionado || teclado[FW_ESPACO].pressionado || controle->botoes[FWX_A].pressionado)
	{
		switch(option)
		{
		case 1:
			return new RCreate("DATA/stg/stg1.joe");
			break;
		case 2:
			return new RCreate("DATA/stg/stg2.joe");
			break;
		case 3:
			return new RCreate("DATA/stg/stg3.joe");
			break;
		case 4:
			return new RCreate("DATA/stg/stg4.joe");
			break;
		case 5:
			return new RCreate("DATA/stg/stg5.joe");
			break;
		case 6:
			return new RCreate("DATA/stg/stg6.joe");
			break;
		case 7:
			return new RCreate("DATA/stg/stg7.joe");
			break;
		case 8:
			return new RCreate("DATA/stg/stg8.joe");
			break;
		case 9:
			return new RCreate("DATA/stg/stg9.joe");
			break;
		case 10:
			return new RCreate("DATA/stg/stg10.joe");
			break;
		case 11:
			return new RCreate("DATA/stg/stg11.joe");
			break;
		case 12:
			return new RCreate("DATA/stg/stg12.joe");
			break;
		case 13:
			return new RCreate("DATA/stg/stg13.joe");
			break;
		case 14:
			return new RCreate("DATA/stg/stg14.joe");
			break;
		case 15:
			return new RCreate("DATA/stg/stg15.joe");
			break;
		}
	}

	if(fases[0]->pressed() || teclado[FW_1].pressionado)
		return new RCreate("DATA/stg/stg1.joe");
	if(fases[1]->pressed() || teclado[FW_2].pressionado)
		return new RCreate("DATA/stg/stg2.joe");
	if(fases[2]->pressed() || teclado[FW_3].pressionado)
		return new RCreate("DATA/stg/stg3.joe");
	if(fases[3]->pressed() || teclado[FW_4].pressionado)
		return new RCreate("DATA/stg/stg4.joe");
	if(fases[4]->pressed() || teclado[FW_5].pressionado)
		return new RCreate("DATA/stg/stg5.joe");
	if(fases[5]->pressed() || teclado[FW_6].pressionado)
		return new RCreate("DATA/stg/stg6.joe");
	if(fases[6]->pressed() || teclado[FW_7].pressionado)
		return new RCreate("DATA/stg/stg7.joe");
	if(fases[7]->pressed() || teclado[FW_8].pressionado)
		return new RCreate("DATA/stg/stg8.joe");
	if(fases[8]->pressed() || teclado[FW_9].pressionado)
		return new RCreate("DATA/stg/stg9.joe");
	if(fases[9]->pressed() || teclado[FW_0].pressionado)
		return new RCreate("DATA/stg/stg10.joe");
	if(fases[10]->pressed())
		return new RCreate("DATA/stg/stg11.joe");
	if(fases[11]->pressed())
		return new RCreate("DATA/stg/stg12.joe");
	if(fases[12]->pressed())
		return new RCreate("DATA/stg/stg13.joe");
	if(fases[13]->pressed())
		return new RCreate("DATA/stg/stg14.joe");
	if(fases[14]->pressed())
		return new RCreate("DATA/stg/stg15.joe");

	if(teclado[FW_ESC].pressionado || controle->botoes[FWX_SELECT].pressionado)
		return new RPreMenu;

	if(teclado[FW_ENCERRA].pressionado)
		return nullptr;

	return this;
}
