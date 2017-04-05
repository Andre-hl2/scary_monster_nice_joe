#ifndef __CINIMIGOH_H__
#define __CINIMIGOH_H__

#include "../core/Ator.h"
#include "../core/GerenteAtor.h"
#include "../core/FW_Resource.h"

class CInimigoH : public Ator
{
public:
	CInimigoH(GerenteAtor& _gerente,int _posX,int _posY);

	float pegaX();
	float pegaY();
	bool estaNoJogo();
	void inicializar();		
	void atualizar();	
	void desenhar();
	void finalizar();

	~CInimigoH();
private:
	FW_Image* image;
	int posX;
	int posY;
	int dir;
	int indice;
	int tempo;
	bool vivo;
};



#endif // __CINIMIGO_H__
