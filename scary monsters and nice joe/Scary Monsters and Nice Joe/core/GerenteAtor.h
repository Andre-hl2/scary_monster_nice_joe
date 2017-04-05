#pragma once

#include <vector>
#include "GameLoop.h"
#include "FW_Resource.h"

//defines de direção para colisão por tile
#define CIMA	 0
#define DIREITA  1
#define BAIXO    2
#define ESQUERDA 3

class Ator;

class GerenteAtor
{
	private:
		std::vector<Ator*> adicionados;
		std::vector<Ator*> atores;
		std::vector<Ator*> mortos;
		std::vector<Ator*> excluidos;
	public:

		GameLoop& gameloop;

		GerenteAtor(GameLoop& _gameloop);
		void adicionar(Ator* ator);
		void atualizar();
		void desenhar();

		bool isFree(SDL_Rect a,int posX,int posY,int tipoAlvo);

		bool checkCollision(SDL_Rect a,SDL_Rect b);

		Ator* pegaProximo(Ator* origem, int raio,int tipoAtor);

		~GerenteAtor();
};

