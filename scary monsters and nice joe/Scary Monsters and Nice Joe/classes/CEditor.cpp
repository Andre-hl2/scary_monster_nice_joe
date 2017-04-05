
#include "../Main.hpp"

#include "../core/FW_Entrada.h"
#include "../core/FW_Resource.h"

#include "CEditor.hpp"

CEditor::CEditor(GerenteAtor& _gerente,FW_Save* _save,int _posX,int _posY, int _tipo,int* _estado,int* _valorMouse)
	:Ator(_gerente),save(_save),posX(_posX),posY(_posY),preY(_posY),tipo(_tipo),gEstado(_estado),valorMouse(_valorMouse)
{
}

float CEditor::pegaX()
{
	return posX;
}

float CEditor::pegaY()
{
	return posY;
}

		
bool CEditor::estaNoJogo()
{
	return vivo;
}

void CEditor::inicializar()
{
	vivo = true;

	estado = DESCENDO;

	quadro = FW_carregaSprite(gerente.gameloop.renderer,"DATA/img/botoes/editor/quadro.png",0,0);

	switch(tipo)
	{
	case FUNDO:
		botoes = new CButton*[6];
		numBotoes = 6;
		botoes[0] = new CButton(&gerente.gameloop,"DATA/img/backgrounds/underSea1.png",posX+32,posY+32,64,64);
		botoes[1] = new CButton(&gerente.gameloop,"DATA/img/backgrounds/underSea2.png",posX+160,posY+32,64,64);
		botoes[2] = new CButton(&gerente.gameloop,"DATA/img/backgrounds/underSea3.png",posX+32,posY+160,64,64);
		botoes[3] = new CButton(&gerente.gameloop,"DATA/img/backgrounds/underSea4.png",posX+160,posY+160,64,64);
		botoes[4] = new CButton(&gerente.gameloop,"DATA/img/backgrounds/underSea5.png",posX+32,posY+288,64,64);
		botoes[5] = new CButton(&gerente.gameloop,"DATA/img/backgrounds/underSea6.png",posX+160,posY+288,64,64);
		for(int i=0;i<6;i++)
		{
			botoes[i]->image->src.w = 1024;
			botoes[i]->image->src.h = 768;
			botoes[i]->image->dst.w = botoes[i]->image->dst.h = 64;
		}
		break;
	case PAREDE:
		botoes = new CButton*[4];
		numBotoes = 4;
		botoes[0] = new CButton(&gerente.gameloop,"DATA/img/tiles/coralCria.png",posX+32,posY+32,64,64);
		botoes[1] = new CButton(&gerente.gameloop,"DATA/img/tiles/tileNeve.png",posX+160,posY+32,64,64);
		botoes[2] = new CButton(&gerente.gameloop,"DATA/img/tiles/tileRocha.png",posX+32,posY+160,64,64);
		botoes[3] = new CButton(&gerente.gameloop,"DATA/img/tiles/tilePreto.png",posX+160,posY+160,64,64);
		for(int i=0;i<4;i++)
		{
			botoes[i]->image->src.w = 32;
			botoes[i]->image->src.h = 32;
			botoes[i]->image->dst.w = botoes[i]->image->dst.h = 64;
		}
		break;
	case MUSICA:
		botoes = new CButton*[4];
		numBotoes = 4;
		botoes[0] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/1.png",posX+32,posY+32,64,64);
		botoes[1] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/2.png",posX+160,posY+32,64,64);
		botoes[2] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/3.png",posX+32,posY+160,64,64);
		botoes[3] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/4.png",posX+160,posY+160,64,64);
		break;
	case INIMIGOS:
		botoes = new CButton*[6];
		numBotoes = 6;
		botoes[0] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/inimigo1.png",posX+32,posY+32,64,64);
		botoes[1] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/inimigo2.png",posX+160,posY+32,64,64);
		botoes[2] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/inimigo3.png",posX+32,posY+160,64,64);
		botoes[3] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/inimigo4.png",posX+160,posY+160,64,64);
		botoes[4] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/inimigo5.png",posX+32,posY+288,64,64);
		botoes[5] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/inimigo6.png",posX+160,posY+288,64,64);
		break;
	case TEMPO:
		botoes = new CButton*[6];
		numBotoes = 6;
		botoes[0] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/t30.png",posX+32,posY+32,64,64);
		botoes[1] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/t100.png",posX+160,posY+32,64,64);
		botoes[2] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/t130.png",posX+32,posY+160,64,64);
		botoes[3] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/t200.png",posX+160,posY+160,64,64);
		botoes[4] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/t230.png",posX+32,posY+288,64,64);
		botoes[5] = new CButton(&gerente.gameloop,"DATA/img/botoes/editor/t300.png",posX+160,posY+288,64,64);
		break;
	}
}
		
void CEditor::atualizar()
{
	FW_Mouse* mouse = ENTRADA.pegaMouse();

	switch(estado)
	{
	case DESCENDO:
		if(posY-preY >= 384+96)
			estado = NADA;

		posY+=16;
		for(int i=0;i<numBotoes;i++)
		{
			botoes[i]->posY+=16;
		}
		if(mouse->botoes[FW_MESQUERDO].pressionado)
			estado = SUBINDO;
		break;
	case NADA:
		switch(tipo)
		{
		case FUNDO:
			if(botoes[0]->pressed())
				save->fundo = 1;
			if(botoes[1]->pressed())
				save->fundo = 2;
			if(botoes[2]->pressed())
				save->fundo = 3;
			if(botoes[3]->pressed())
				save->fundo = 4;
			if(botoes[4]->pressed())
				save->fundo = 5;
			if(botoes[5]->pressed())
				save->fundo = 6;
			break;
		case PAREDE:
			*valorMouse = 1;
			if(botoes[0]->pressed())
				save->tile = 1;
			if(botoes[1]->pressed())
				save->tile = 2;
			if(botoes[2]->pressed())
				save->tile = 3;
			if(botoes[3]->pressed())
				save->tile = 4;
			break;
		case MUSICA:
			if(botoes[0]->pressed())
				save->musica = 1;
			if(botoes[1]->pressed())
				save->musica = 2;
			if(botoes[2]->pressed())
				save->musica = 3;
			if(botoes[3]->pressed())
				save->musica = 4;
			break;
		case INIMIGOS:
			if(botoes[0]->pressed())
				*valorMouse = 2;
			if(botoes[1]->pressed())
				*valorMouse = 6;
			if(botoes[2]->pressed())
				*valorMouse = 3;
			if(botoes[3]->pressed())
				*valorMouse = 5;
			if(botoes[4]->pressed())
				*valorMouse = 4;
			if(botoes[5]->pressed())
				*valorMouse = 7;
			break;
		case TEMPO:
			if(botoes[0]->pressed())
				save->tempo = 30;
			if(botoes[1]->pressed())
				save->tempo = 60;
			if(botoes[2]->pressed())
				save->tempo = 90;
			if(botoes[3]->pressed())
				save->tempo = 120;
			if(botoes[4]->pressed())
				save->tempo = 150;
			if(botoes[5]->pressed())
				save->tempo = 180;
			break;
		}

		if(mouse->botoes[FW_MESQUERDO].pressionado)
		{
			estado = SUBINDO;
		}
		break;
	case SUBINDO:
		if(posY > preY)
		{
			posY-=16;
			for(int i=0;i<numBotoes;i++)
				botoes[i]->posY-=16;
		}
		else
		{
			vivo = false;
			*gEstado = 2;
		}
		break;
		
	}
}

void CEditor::desenhar()
{
	FW_desenhaSprite(gerente.gameloop.renderer,quadro,0,posX,posY);

	for(int i=0;i<numBotoes;i++)
	{
		botoes[i]->draw();
	}
}

void CEditor::finalizar()
{
	FW_removeSprite(quadro);
	for(int i=0;i<numBotoes;i++)
	{
		delete botoes[i];
	}
	delete botoes;

}
