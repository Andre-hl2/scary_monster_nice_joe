
#ifndef __RPASSOU_H__
#define __RPASSOU_H__

#include "../Main.hpp"
#include "../core/GerenciadorTelas.h"
#include "../core/FW_Resource.h"
#include "../core/GameLoop.h"
#include "../core/Tela.h"
#include "../classes/CButton.hpp"

class RPassou : public Tela
{
public:
	RPassou(int _fase);

	void inicializar(GameLoop* _gameloop);
	void atualizar();
	void desenhar();
	void finalizar();

	Tela* proximaTela();

private:
	GameLoop* gameloop;
	FW_Perfil* perfil;
	FW_Image* background;

	CButton* next;
	CButton* exit;
	int fase;

};

#endif // __RPASSOU_H__