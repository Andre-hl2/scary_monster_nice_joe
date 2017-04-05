
#ifndef __REDIT_H__
#define __REDIT_H__

#include "../core/GerenteAtor.h"
#include "../core/Tela.h"
#include "../core/FW_Resource.h"
#include "../classes/CPlayer.h"
#include "../classes/CButton.hpp"

class REdit : public Tela
{
public:
	REdit (char* _caminho);

	void inicializar(GameLoop* _gameloop);
	void atualizar();

	void desenhar();
	void finalizar();

	Tela* proximaTela();

private:
	GerenteAtor* gerente;
	FW_Image* inimigoV, *inimigoVA;
	FW_Image* inimigoH, *inimigoHA;
	FW_Image* inimigoDiag, *inimigoDiagA;
	FW_Image* inimigoE, *inimigoEA;
	FW_Image* inimigoBH,*inimigoBHA;
	FW_Image* inimigoBV,*inimigoBVA;
	FW_Image* inimigoBD,*inimigoBDA;
	FW_Image* peixe;
	FW_Image* fim;

	FW_Image* tileCoral, *tileNeve, *tileRocha, *tilePreto;
	FW_Image* tileCoralA,*tileNeveA,*tileRochaA,*tilePretoA;

	FW_Save* fase;

	GameLoop* gameloop;

	FW_Image* background1;
	FW_Image* background2;
	FW_Image* background3;
	FW_Image* background4;
	FW_Image* background5;
	FW_Image* background6;
	
	char* caminho;

	int valorMouse;

	int estado;

	FW_Image* HUD;

	CButton* sFundo;
	CButton* sMusica;
	CButton* sTile;
	CButton* sInimigo;
	CButton* sTempo;
	CButton* sSalvar;
};

#endif //__REDIT_H__