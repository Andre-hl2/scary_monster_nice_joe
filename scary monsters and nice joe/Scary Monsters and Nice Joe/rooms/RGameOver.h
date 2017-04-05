
#ifndef __RGAMEOVER_H__
#define __RGAMEOVER_H__

#include "../core/Tela.h"
#include "../core/GerenteAtor.h"
#include "../classes/CButton.hpp"

class RGameOver : public Tela
{
public:
	RGameOver(char* _caminho,int _fase,int _morte);

	void inicializar(GameLoop* _gameloop);
	void atualizar();

	void desenhar();
	void finalizar();

	Tela* proximaTela();

private:

	CButton* retry;
	CButton* exit;

	GameLoop* gameloop;

	FW_Image* background;
	
	FW_Image* peixe;

	char* caminho;
	int fase;
	int morte;

	int tempo;
	int fade;

	SDL_Rect boxFade;
};

#endif //__RGAMEOVER_H__