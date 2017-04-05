#include "ControleX.hpp"

ControleX::ControleX()
{
	numControle = 0;
}

XINPUT_STATE ControleX::pegaEstado()
{
	// Reinicia a memoria
	ZeroMemory(&estadoControle, sizeof(XINPUT_STATE));

	// Pega o estado atual do controle
	XInputGetState(numControle, &estadoControle);


	//diminui a variavel tempo, responsavel por controlar o tempo de vibração
	if(tempo > 0)
		tempo--;
	//executa uma função para fazer o controle parar de vibrar quando acabar o tempo
	if(tempo == 0)
		vibrar(-1);

	

	//analogicos
	LX = estadoControle.Gamepad.sThumbLX;
	LY = estadoControle.Gamepad.sThumbLY;

	RX = estadoControle.Gamepad.sThumbRX;
	RY = estadoControle.Gamepad.sThumbRY;

	return estadoControle;
}

bool ControleX::plugado()
{
	// Reinicia a memoria
	ZeroMemory(&estadoControle,sizeof(XINPUT_STATE));

	// Pega o estado atual do controle
	DWORD ChecaPlugado = XInputGetState(numControle,&estadoControle);

	//checa se o controle está conectado

	if(ChecaPlugado == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ControleX::vibrar(int _tempo,float _motorEsq,float _motorDir)
{
	//checagem de inputs da função e conversão para o XINPUT_VIBRATE

	//checa o maximo
	if(_motorEsq > 100)
		_motorEsq = 100;

	if(_motorDir > 100)
		_motorDir = 100;

	//checa o minimo
	if(_motorEsq < 0)
		_motorEsq = 0;

	if(_motorDir < 0)
		_motorDir = 0;


	// o XINPUT_VIBRATION aceita valores de  0-65535, mas essa função recebe valores de 0-100

	// converção de escalas
	float motorDir = (65535 * _motorDir) / 100;
	float motorEsq = (65535 * _motorEsq) / 100;
	

	//Cria um estado de vibração
	XINPUT_VIBRATION vibracao;

	//zera a vibração
	ZeroMemory(&vibracao,sizeof(XINPUT_VIBRATION));

	//atribui valores para a vibração
	vibracao.wLeftMotorSpeed = motorEsq;
	vibracao.wRightMotorSpeed = motorDir;
	tempo = _tempo;

	//função para vibrar o controle
	XInputSetState(numControle,&vibracao);

}

bool ControleX::pressionado(WORD botao)
{
	//retorna se o botao esta pressionado
	return ( (estadoControle.Gamepad.wButtons & botao) != 0 );
}

int ControleX::pegaLX()
{
	return (LX/32767)*100;
}
int ControleX::pegaLY()
{
	return (LY/32767)*100;
}
int ControleX::pegaRX()
{
	return (RX/32767)*100;
}
int ControleX::pegaRY()
{
	return (RY/32767)*100;
}