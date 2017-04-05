

#include "Main.hpp"

#include "core\GameLoop.h"
#include "core/FW_Entrada.h"
#include "core\ControleX.hpp"
#include "rooms\CMenu.hpp"
#include "rooms\RLogo.h"

#include "core\FW_Resource.h"

void alteraSave();

int main(int argc, char* argv[])
{
	srand(time(NULL));

	ControleX player;

	int i=0;

	GameLoop gameloop(new RLogo);

	if(player.plugado())
	{
		printf("\n\n\n             Controle detectado...\n\n");

		printf(" Bem vindo ao jogo'Scary Monsters and Nice Joe'\n  Deseja jogar com\n[A] Tela Cheia\n[X] Janela");
		
		while(i == 0)
		{
			player.pegaEstado();

			if(player.pressionado(CONTROLEX_A))
				i=1;
			if(player.pressionado(CONTROLEX_X))
				i=2;

			if(player.pressionado(CONTROLEX_Y))
				i=3;
		}

		if(i == 1)
			gameloop.executar("Scary Monsters and Nice Joe - pre alpha beta do pre jogo", 1024, 768,true);
		else
		{
			if(i==2)
				gameloop.executar("Scary Monsters and Nice Joe - pre alpha beta do pre jogo", 1024, 768);
			else
			{
				alteraSave();
				gameloop.executar("Scary Monsters and Nice Joe - pre alpha beta do pre jogo", 1024, 768);
			}
		}
	}
	else
	{
		printf(" Bem vindo ao jogo'Scary Monsters and Nice Joe'\n  Deseja jogar com\n-1-Tela Cheia\n-2-Janela");
		scanf("%d",&i);

		if(i == 1)
			gameloop.executar("Scary Monsters and Nice Joe - pre alpha beta do pre jogo", 1024, 768,true);
		else
		{
			if(i == 2 )
				gameloop.executar("Scary Monsters and Nice Joe - pre alpha beta do pre jogo", 1024, 768);
			else
			{
				if(i == 3)
				{
					alteraSave();
					gameloop.executar("Scary Monsters and Nice Joe - pre alpha beta do pre jogo", 1024, 768);
				}
			}
		}
	}
	
	return 0;
}

void alteraSave()
{
	FW_Perfil perfil;

	int escolha;

	system("cls");
	printf("     \n\n\n     Digite o numero de fases que deseja liberar (1-16): ");
	scanf("%d",&escolha);

	if(escolha > 0 && escolha < 17)
		perfil.passou = escolha;
	else
		perfil.passou = 1;

	FW_SalvaPerfil("DATA/save.joe",perfil);
}