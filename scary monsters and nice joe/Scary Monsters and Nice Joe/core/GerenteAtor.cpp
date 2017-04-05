
#include "GerenteAtor.h"
#include "Ator.h"

#include <algorithm>
#include <functional>
#include <string>
#include <fstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;

GerenteAtor::GerenteAtor(GameLoop& _gameloop)
	:gameloop(_gameloop)
{
}

void GerenteAtor::adicionar(Ator* ator)
{
	adicionados.push_back(ator);
	ator->inicializar();
}

void GerenteAtor::atualizar()
{
	//1. Excluir os atores na lista excluido
	//para libera-la. 
	for (Ator* ator : excluidos)
	{
		delete ator;
	}
	excluidos.clear();

	//2. Mover os mortos para a lista de excluídos
	//para liberar a lista de mortos.
	for (Ator* ator : mortos)
	{
		excluidos.push_back(ator);
	}
	mortos.clear();

	//Adiciona todos os atores que foram adicionados no loop anterior
	//e coloca-los na lista de atores.
	for (Ator* ator : adicionados)
	{
		atores.push_back(ator);
	}
	adicionados.clear();

	//3. Atualiza a lógica do ator e, caso queira sair do jogo
	//finaliza e move para a lista de mortos. Caso contrário,
	//mantém o ator numa lista de vivos.
	std::vector<Ator*> vivos;
	for (Ator* ator : atores) 
	{
		ator->atualizar();
		if (ator->estaNoJogo())
		{
			vivos.push_back(ator);
		}
		else
		{
			ator->finalizar();
			mortos.push_back(ator);
		}
	}

	//Substitui a lista de atores pela de vivos.
	swap(atores, vivos);

}


void GerenteAtor::desenhar()
{
	for (Ator* ator : atores) 
	{
		ator->desenhar();
	}
}

//retorna se esta livre 
bool GerenteAtor::isFree(SDL_Rect a,int posX,int posY,int tipoAlvo)
{
	bool existeColisão = false;
	a.x+=posX;
	a.y+=posY;

	for(Ator* ator : atores)
	{
		if(ator->especie == tipoAlvo)
		{
			if( sqrt( ((a.x - ator->pegaX()) * (a.x - ator->pegaX()) ) + ( (a.y - ator->pegaY())  * (a.y - ator->pegaY()))) < 64)
				if(/*existeColisão = */checkCollision(a,ator->box))
						return false;
		}
	}

	return true;

	if(existeColisão)
		return false;
	else
		return true;
}

//retorna se colidiu ou nao
bool GerenteAtor::checkCollision(SDL_Rect a,SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

Ator* GerenteAtor::pegaProximo(Ator* origem,int raio,int tipoAtor)
{
	Ator* temp = nullptr;
	int proximo = raio+10;


	for(Ator* ator : atores)
	{
		if(ator->especie == tipoAtor)
		{
			

			float quadr = sqrt( ((ator->pegaX() - origem->pegaX()) * (ator->pegaX() - origem->pegaX())) +  ( (ator->pegaY() - origem->pegaY())*(ator->pegaY() - origem->pegaY())));  


			if( quadr < raio )
			{
				if(quadr < proximo)
				{
					proximo = quadr;
					temp = ator;
				}
			}
		}
	}

	if(proximo == raio+10)
		return nullptr;

	return temp;
}

GerenteAtor::~GerenteAtor()
{
	for (Ator* ator : atores) 
	{
		delete ator;
	}
}
