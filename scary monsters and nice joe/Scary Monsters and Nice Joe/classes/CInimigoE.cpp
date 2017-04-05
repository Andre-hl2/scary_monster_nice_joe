#include "CInimigoE.hpp"

CInimigoE::CInimigoE(GerenteAtor& _gerente,int _posX,int _posY)
	:Ator(_gerente),posX(_posX),posY(_posY)
{
	box.w = 32;
	box.h = 32;
}

	float CInimigoE::pegaX()
	{
		return posX;
	}

	float CInimigoE::pegaY()
	{
		return posY;
	}

	bool CInimigoE::estaNoJogo()
	{
		return vivo;
	}

	void CInimigoE::inicializar()
	{
		indice = 0;
		tempo = 0;
		especie = INIMIGO;
		dir = 2;
		image = FW_carregaSprite(gerente.gameloop.renderer, "DATA/img/inimigos/inimigoE.png", 32, 32);
	}

	void CInimigoE::atualizar()
	{
		
	}

	void CInimigoE::desenhar()
	{
		FW_desenhaSprite(gerente.gameloop.renderer, image, indice, posX, posY);
	}

	void CInimigoE::finalizar()
	{
		FW_removeSprite(image);
	}

	CInimigoE::~CInimigoE()
	{

	}