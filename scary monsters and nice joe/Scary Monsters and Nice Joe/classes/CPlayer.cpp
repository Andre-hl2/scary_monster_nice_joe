
#include "../Main.hpp"
#include "CPlayer.h"

#include "../core/FW_Entrada.h"

CPlayer::CPlayer(GerenteAtor& _gerente,int _posX,int _posY)
	:Ator(_gerente),posX(_posX),posY(_posY)
{
	especie = JOGADOR;
	box.h = 24;	
	box.w = 24;
	box.x = posX+4;
	box.y = posY+4;
}

float CPlayer::pegaX()
{
	return posX;
}

float CPlayer::pegaY()
{
	return posY;
}
		
bool CPlayer::estaNoJogo()
{
	return true;
}

void CPlayer::inicializar()
{
	image = FW_carregaSprite(gerente.gameloop.renderer,"DATA/img/jogador/joe_normal.png",32,32);
	aviso = FW_carregaSprite(gerente.gameloop.renderer,"DATA/img/jogador/aviso.png",0,0);
	indice = 0;
	tempo = 0;
	dir = 0;
	vivo = true;
	desenhaAviso = false;
	angleAviso = 0;
	galvao = false;
}

void CPlayer::atualizar()
{
	//atualiza posição
	FW_Botao* teclado = ENTRADA.pegaTecla();
	FW_Mouse* mouse	  = ENTRADA.pegaMouse();
	FW_Controle* controle = ENTRADA.pegaControle();

	if(teclado[FW_CIMA].ativo || teclado[FW_W].ativo || controle->botoes[FWX_DUP].ativo || controle->Lthumb_y > 50)
		if(gerente.isFree(box,0,-4,TILE))
			if( posY > 0 )
				posY-= 4;

	if(teclado[FW_DIREITA].ativo || teclado[FW_D].ativo || controle->botoes[FWX_DRIGHT].ativo || controle->Lthumb_x > 50)
	{
		dir = 0;
		if(gerente.isFree(box,4,0,TILE))
			if(posX < 1024)
				posX += 4;
	}

	if(teclado[FW_BAIXO].ativo || teclado[FW_S].ativo || controle->botoes[FWX_DDOWN].ativo || controle->Lthumb_y < -50)
		if(gerente.isFree(box,0,4,TILE))
			if(posY < 768)
				posY += 4;

	if(teclado[FW_ESQUERDA].ativo || teclado[FW_A].ativo || controle->botoes[FWX_DLEFT].ativo || controle->Lthumb_x < -50)
	{
		dir = 1;
		if(gerente.isFree(box,-4,0,TILE))
			if(posX > 0)
				posX -= 4;
	}

	if(!gerente.isFree(box,0,0,INIMIGO))
		vivo = false;

	if(!gerente.isFree(box,0,0,FIMJOGO))
	{
		galvao = true;
	}

	//atualiza animação
	tempo++;
	if(tempo == 15)
	{
		tempo = 0;
		indice = (indice+1)%8;
	}

	Ator* proximo = gerente.pegaProximo(this,150,INIMIGO);

	if(proximo != nullptr)
	{
		desenhaAviso = true;
		float offsetX = proximo->pegaX() - posX;
		float offsetY = proximo->pegaY() - posY;

		float radian = atan2(offsetY,offsetX); 

		angleAviso = radian*180/3.1415;
	}
	else
	{
		desenhaAviso = false;
	}

	//atualiza caixa de colisão
	box.x = posX+4;
	box.y = posY+4;
}

void CPlayer::desenhar()
{

	if(desenhaAviso)
		FW_DesenhaSpriteRot(gerente.gameloop.renderer,aviso,0,posX-34, posY-32,angleAviso);

	FW_desenhaSprite(gerente.gameloop.renderer,image, (dir == 0)? indice : indice+8  ,posX,posY);	
}

void CPlayer::finalizar()
{
	FW_removeSprite( image );
}

CPlayer::~CPlayer()
{
	FW_removeSprite( image );
}