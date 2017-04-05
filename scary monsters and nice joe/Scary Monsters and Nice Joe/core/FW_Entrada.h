
#ifndef __FW_ENTRADA_H__
#define __FW_ENTRADA_H__

#include <SDL.h>
#include "ControleX.hpp"

#define ENTRADA FW_Entrada::getInstance()

//defines para o indice do objeto teclas
#define FW_MAX_TECLAS	26
#define FW_CIMA		0
#define FW_DIREITA	1
#define FW_BAIXO	2
#define FW_ESQUERDA	3
#define FW_Z		4
#define FW_X		5
#define FW_C		6
#define FW_A		7
#define FW_S		8
#define FW_D		9
#define FW_W		10
#define FW_ESPACO	11
#define FW_ENTER	12
#define FW_CONTROL	13

#define FW_1		14
#define FW_2		15
#define FW_3		16
#define FW_4		17
#define FW_5		18
#define FW_6		19
#define FW_7		20
#define FW_8		21
#define FW_9		22
#define FW_0		23

#define FW_ESC		24
#define FW_ENCERRA	25

//defines para o indice do objeto mouse
#define FW_MDIREITO	0
#define FW_MESQUERDO 1
#define FW_MMEIO	2

//defines para o indice do objeto controle
#define FWX_A		0
#define FWX_B		1
#define FWX_X		2
#define FWX_Y		3
#define FWX_DUP		4
#define FWX_DRIGHT	5
#define FWX_DDOWN	6
#define FWX_DLEFT	7
#define FWX_RB		8
#define FWX_LB		9
#define FWX_L3		10
#define FWX_R3		11
#define FWX_START	12
#define FWX_SELECT	13

//struct para botoes
struct FW_Botao
{
	bool pressionado;
	bool liberado;
	bool ativo;
};

//struct para o mouse
struct FW_Mouse
{
	int x;
	int y;
	FW_Botao botoes[3];
};

struct FW_Controle
{
	bool plugado;

	FW_Botao botoes[14];

	int Lthumb_x;
	int Lthumb_y;
	int Rthumb_x;
	int Rthumb_y;

	ControleX controle;

};

class FW_Entrada
{
public:
	static FW_Entrada& getInstance();

	FW_Mouse* pegaMouse();
	FW_Botao* pegaTecla();
	FW_Controle* pegaControle();
	
	void atualiza();
private:
	static FW_Entrada* Instance;

	FW_Botao tecla[FW_MAX_TECLAS];
	FW_Mouse mouse;
	FW_Controle controle;

	FW_Entrada() {}

	void processaTecla(FW_Botao* tecla, SDL_Event event);

	void processaControle( bool pressionado, int indice);
};

#endif //__FW_ENTRADA_H__