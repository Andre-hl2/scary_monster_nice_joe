#pragma once

class GameLoop;

class Tela
{
	public:
		virtual void inicializar(GameLoop* _gameloop) = 0;
		virtual void atualizar() = 0;
		virtual void desenhar() = 0;
		virtual void finalizar() = 0;

		virtual Tela* proximaTela() = 0;

		virtual ~Tela() {}
};