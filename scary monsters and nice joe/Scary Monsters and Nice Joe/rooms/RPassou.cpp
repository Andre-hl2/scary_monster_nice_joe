
#include "RPassou.h"
#include "../core/FW_Entrada.h"
#include "RSelJoga.h"
#include "RTesta.h"
#include "RPreMenu.h"

RPassou::RPassou(int _fase)
	:fase(_fase)
{
}

void RPassou::inicializar(GameLoop* _gameloop)
{
	gameloop = _gameloop;

	background = FW_carregaSprite(gameloop->renderer,"DATA/img/backgrounds/passou.png",0,0);

	perfil = FW_carregaPerfil("DATA/save.joe");

	if(fase+1 > perfil->passou)
	{
		perfil->passou = fase+1;
		FW_SalvaPerfil("DATA/save.joe",*perfil);
	}

	next = new CButton(gameloop,"DATA/img/botoes/next.png",260,550,128,64);
	exit = new CButton(gameloop,"DATA/img/botoes/sair.png",580,550,128,64);
}

void RPassou::atualizar()
{
}

void RPassou::desenhar()
{
	FW_desenhaSprite(gameloop->renderer,background,0,0,0);
	
	exit->draw();
	next->draw();
}

void RPassou::finalizar()
{
	FW_removeSprite(background);
	delete exit;
	delete next;
}

Tela* RPassou::proximaTela()
{
	FW_Botao* teclado = ENTRADA.pegaTecla();
	FW_Mouse* mouse = ENTRADA.pegaMouse();
	FW_Controle* controle = ENTRADA.pegaControle();

	if(controle->botoes[FWX_A].pressionado || teclado[FW_ENTER].pressionado || mouse->botoes[FW_MESQUERDO].pressionado || teclado[FW_ESPACO].pressionado || next->pressed())
	{
		if(fase < 15)
			return new RTesta(fase+1);
		else
			return new RPreMenu;
	}

	if(controle->botoes[FWX_B].pressionado || teclado[FW_ESC].pressionado || mouse->botoes[FW_MDIREITO].pressionado || teclado[FW_Z].pressionado || exit->pressed())
		return new RSelJoga;

	return this;
}