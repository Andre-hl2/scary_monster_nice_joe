#ifndef __GERENCIADORTELAS_H__
#define __GERENCIADORTELAS_H__

class GameLoop;
class Tela;

class GerenciadorTelas
{
	private:
		Tela* tela;
		GameLoop* gameloop;
	public:
		GerenciadorTelas(Tela* tela, GameLoop* _gameloop);
		void atualizar();
		void desenhar();
		bool acabou();
		~GerenciadorTelas();
};

#endif // __GERENCIADORTELAS_H__