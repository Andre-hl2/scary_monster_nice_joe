#ifndef __CONTROLEX_H__
#define __CONTROLEX_H__

//constantes para os botoes do controle
#define CONTROLEX_DPAD_CIMA				0x0001
#define CONTROLEX_DPAD_BAIXO			0x0002
#define CONTROLEX_DPAD_ESQUERDA			0x0004
#define CONTROLEX_DPAD_DIREITA			0x0008
#define CONTROLEX_START					0x0010
#define CONTROLEX_BACK					0x0020
#define CONTROLEX_ANALOGICO_ESQUERDO	0x0040
#define CONTROLEX_ANALOGICO_DIREITO     0x0080
#define CONTROLEX_OMBRO_ESQUERDO		0x0100
#define CONTROLEX_OMBRO_DIREITO			0x0200
#define CONTROLEX_A						0x1000
#define CONTROLEX_B						0x2000
#define CONTROLEX_X						0x4000
#define CONTROLEX_Y						0x8000

// Essa classe suporta apenas 1 controle


#include <Windows.h>
#include <XInput.h>

class ControleX
{
private:
	//estado atual do controle
	XINPUT_STATE estadoControle;
	//o numero do controle
	int numControle;
	//controlador de tempo de vibração
	int tempo;
	//analogicos
	float RX,RY,LX,LY;
public:
	//construtor
	ControleX();
	//retorna o atual estado do controle
	XINPUT_STATE pegaEstado();
	//checa se o controle está plugado
	bool plugado();
	//função para vibrar o controle
	void vibrar(int _tempo=0,float _motorEsq=0.0f ,float _motorDir=0.0f);
	//checa se um botão está pressionado
	bool pressionado(WORD botao);
	//pega analogicos
	int pegaRX();
	int pegaRY();
	int pegaLX();
	int pegaLY();

};

#endif // __CONTROLEX_H__