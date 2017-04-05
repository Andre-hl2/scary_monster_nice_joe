
#include "GameLoop.h"
#include "GerenciadorTelas.h"
#include "Tela.h"

GerenciadorTelas::GerenciadorTelas(Tela* _tela, GameLoop* _gameloop)
	:tela(_tela),gameloop(_gameloop)
{
	tela->inicializar(gameloop);
}

void GerenciadorTelas::atualizar()
{
	Tela* proximaTela = tela->proximaTela();

	//se mandar tela nula termina o programa
	if (proximaTela == nullptr) 
	{
		tela->finalizar();
		delete tela;
		tela = nullptr;
	} 
	else
	{
		//se nao enviar uma tela igual a atual, termina essa e inicia a outra
		if (proximaTela != tela) 
		{
			tela->finalizar();
			delete tela;
			tela = proximaTela;

			tela->inicializar(gameloop);
		}

		//caso seja a mesma apenas atualiza
		tela->atualizar();
	}
}

void GerenciadorTelas::desenhar()
{
	if (tela != nullptr)
		tela->desenhar();
}

bool GerenciadorTelas::acabou()
{
	return tela == nullptr;
}

GerenciadorTelas::~GerenciadorTelas()
{
}