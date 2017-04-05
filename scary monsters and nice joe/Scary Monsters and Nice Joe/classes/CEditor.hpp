
#ifndef __CEDITOR_H__
#define __CEDITOR_H__

#include "../core/Ator.h"
#include "../core/GerenteAtor.h"
#include "CButton.hpp"
#include "../core/FW_Resource.h"

//defines de tipo
#define FUNDO	1
#define MUSICA	2
#define SPRITE	3
#define PAREDE	4
#define INIMIGOS 5
#define TEMPO	6

//defines de estado
#define SUBINDO 1
#define NADA	2
#define DESCENDO 3

class CEditor : public Ator
{
public:
	CEditor(GerenteAtor& _gerente,FW_Save* _save,int _posX,int _posY, int _tipo,int* _estado,int* _valorMouse = 0);

	float pegaX();
	float pegaY();
		
	bool estaNoJogo();
	void inicializar();		
	void atualizar();	
	void desenhar();
	void finalizar();

private:
	FW_Save* save;

	FW_Image* quadro;

	CButton** botoes;

	int estado;

	int tipo;
	int posX;
	int posY;
	int preY;

	int* gEstado;
	int* valorMouse;

	int numBotoes;

	bool vivo;
};

#endif //__CEDITOR_H__