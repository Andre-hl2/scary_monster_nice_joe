
#ifndef __RCREATE_H__
#define __RCREATE_H__

#include "../core/GerenteAtor.h"
#include "../core/Tela.h"
#include "../core/FW_Resource.h"
#include "../classes/CPlayer.h"

class RCreate : public Tela
{
public:
	RCreate (char* _caminho);

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
	FW_Image* inimigoBH,*inimigoBHA;
	FW_Image* inimigoBV,*inimigoBVA;
	FW_Image* inimigoBD,*inimigoBDA;
	FW_Image* peixe;
	FW_Image* fim;

	FW_Image* tileCoral, *tileNeve;

	FW_Image* tileA;

	FW_Save* fase;

	GameLoop* gameloop;

	FW_Image* background1;
	FW_Image* background2;
	FW_Image* background3;
	
	char* caminho;

	int valorMouse;
};

#endif //__RCREATE_H__