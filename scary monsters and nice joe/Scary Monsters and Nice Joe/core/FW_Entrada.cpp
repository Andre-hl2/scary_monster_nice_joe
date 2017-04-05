
#include "FW_Entrada.h"

//função de chamada do Singleton
FW_Entrada& FW_Entrada::getInstance()
{
	static FW_Entrada Instance;

	return Instance;
}

//funções de retorno de entrada, mouse e teclado
FW_Botao* FW_Entrada::pegaTecla()
{
	return tecla;
}

FW_Mouse* FW_Entrada::pegaMouse()
{
	return &mouse;
}

FW_Controle* FW_Entrada::pegaControle()
{
	return &controle;
}

//funções para atualizar os estados do input

void FW_Entrada::processaTecla(FW_Botao* tecla,SDL_Event event)
{
	switch(event.type)
    {
    case SDL_KEYDOWN:
        tecla->pressionado=true;
        tecla->liberado=false;
        tecla->ativo=true;
        break;
    case SDL_KEYUP:
        tecla->ativo=false;
        tecla->liberado=true;
        tecla->pressionado=false;
        break;
    }

}

void FW_Entrada::atualiza()
{

	// Remove o pressionamento das teclas do passo anterior
    for(int i=0;i<FW_MAX_TECLAS;i++)
            tecla[i].pressionado = false;
    // Remove o liberamento das teclas do passo anterior
    for(int i=0;i<FW_MAX_TECLAS;i++)
            tecla[i].liberado=false;
    // Remove o pressionamento do mouse do passo anterior
    for(int i=0;i<3;i++)
            mouse.botoes[i].pressionado = false;
    // Remove o liberamento do mpouse do passo anterior
    for(int i=0;i<3;i++)
            mouse.botoes[i].liberado=false;

	for(int i=0;i<14;i++)
	{
		controle.botoes[i].liberado = false;
		controle.botoes[i].pressionado = false;
	}


	// A estrutura que recebe os eventos
	SDL_Event event;
	// Enquanto houverem eventos a processar ...
	while(SDL_PollEvent( &event ))
	{
	// Trata de acordo com o tipo de evento
	switch( event.type )
	{
	case SDL_QUIT:
		tecla[FW_ENCERRA].pressionado = true;
		break;

	case SDL_KEYDOWN:
	case SDL_KEYUP:
			switch(event.key.keysym.sym)
			{
			case SDLK_UP:
				processaTecla(&tecla[FW_CIMA],event);
				break;
			case SDLK_RIGHT:
				processaTecla(&tecla[FW_DIREITA],event);
				break;
			case SDLK_DOWN:
				processaTecla(&tecla[FW_BAIXO],event);
				break;
			case SDLK_LEFT:
				processaTecla(&tecla[FW_ESQUERDA],event);
				break;
			case SDLK_z:
				processaTecla(&tecla[FW_Z],event);
				break;
			case SDLK_x:
				processaTecla(&tecla[FW_X],event);
				break;
			case SDLK_c:
				processaTecla(&tecla[FW_C],event);
				break;
			case SDLK_a:
				processaTecla(&tecla[FW_A],event);
				break;
			case SDLK_s:
				processaTecla(&tecla[FW_S],event);
				break;
			case SDLK_d:
				processaTecla(&tecla[FW_D],event);
				break;
			case SDLK_w:
				processaTecla(&tecla[FW_W],event);
				break;
			case SDLK_SPACE:
				processaTecla(&tecla[FW_ESPACO],event);
				break;
			case SDLK_LCTRL:
				processaTecla(&tecla[FW_CONTROL],event);
				break;

			case SDLK_1:
				processaTecla(&tecla[FW_1],event);
				break;
			case SDLK_2:
				processaTecla(&tecla[FW_2],event);
				break;
			case SDLK_3:
				processaTecla(&tecla[FW_3],event);
				break;
			case SDLK_4:
				processaTecla(&tecla[FW_4],event);
				break;
			case SDLK_5:
				processaTecla(&tecla[FW_5],event);
				break;
			case SDLK_6:
				processaTecla(&tecla[FW_6],event);
				break;
			case SDLK_7:
				processaTecla(&tecla[FW_7],event);
				break;
			case SDLK_8:
				processaTecla(&tecla[FW_8],event);
				break;
			case SDLK_9:
				processaTecla(&tecla[FW_9],event);
				break;
			case SDLK_0:
				processaTecla(&tecla[FW_0],event);
				break;

			case SDLK_RETURN:
				processaTecla(&tecla[FW_ENTER],event);
				break;
			case SDLK_ESCAPE:
				processaTecla(&tecla[FW_ESC],event);
				break;
			}
			break; //break dos eventos de tipo teclado

	case SDL_MOUSEMOTION:
			mouse.x=event.motion.x;
			mouse.y=event.motion.y;
			break;// break da posição do mouse

	case SDL_MOUSEBUTTONDOWN:
			mouse.x=event.button.x;
			mouse.y=event.button.y;
			switch(event.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouse.botoes[FW_MESQUERDO].pressionado=true;
				mouse.botoes[FW_MESQUERDO].liberado=false;
				mouse.botoes[FW_MESQUERDO].ativo=true;
				break;
			case SDL_BUTTON_RIGHT:
				mouse.botoes[FW_MDIREITO].pressionado=true;
				mouse.botoes[FW_MDIREITO].liberado=false;
				mouse.botoes[FW_MDIREITO].ativo=true;
				break;
			case SDL_BUTTON_MIDDLE:
				mouse.botoes[FW_MMEIO].pressionado=true;
				mouse.botoes[FW_MMEIO].liberado=false;
				mouse.botoes[FW_MMEIO].ativo=true;
				break;
			}
			break; //break dos eventos de mouse button down

	case SDL_MOUSEBUTTONUP:
			mouse.x=event.button.x;
			mouse.y=event.button.y;
			switch(event.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouse.botoes[FW_MESQUERDO].ativo=false;
				mouse.botoes[FW_MESQUERDO].liberado=true;
				mouse.botoes[FW_MESQUERDO].pressionado=false;
				break;
			case SDL_BUTTON_RIGHT:
				mouse.botoes[FW_MDIREITO].ativo=false;
				mouse.botoes[FW_MDIREITO].liberado=true;
				mouse.botoes[FW_MDIREITO].pressionado=false;
				break;
			case SDL_BUTTON_MIDDLE:
				mouse.botoes[FW_MMEIO].ativo=false;
				mouse.botoes[FW_MMEIO].liberado=true;
				mouse.botoes[FW_MMEIO].pressionado=false;
				break;
			}
			break; //break dos eventos de mouse button up
		}

	}

	//processos do controle
	
	controle.plugado = controle.controle.plugado();

	if(controle.plugado)
	{

		controle.controle.pegaEstado();

		controle.Lthumb_x = controle.controle.pegaLX();
		controle.Lthumb_y = controle.controle.pegaLY();
		controle.Rthumb_x = controle.controle.pegaRX();
		controle.Rthumb_y = controle.controle.pegaRY();


		processaControle( controle.controle.pressionado(CONTROLEX_A),FWX_A);
		processaControle( controle.controle.pressionado(CONTROLEX_B),FWX_B);
		processaControle( controle.controle.pressionado(CONTROLEX_X),FWX_X);
		processaControle( controle.controle.pressionado(CONTROLEX_Y),FWX_Y);

		processaControle( controle.controle.pressionado(CONTROLEX_DPAD_CIMA),FWX_DUP);
		processaControle( controle.controle.pressionado(CONTROLEX_DPAD_DIREITA),FWX_DRIGHT);
		processaControle( controle.controle.pressionado(CONTROLEX_DPAD_BAIXO),FWX_DDOWN);
		processaControle( controle.controle.pressionado(CONTROLEX_DPAD_ESQUERDA),FWX_DLEFT);

		processaControle( controle.controle.pressionado(CONTROLEX_ANALOGICO_DIREITO),FWX_R3);
		processaControle( controle.controle.pressionado(CONTROLEX_ANALOGICO_ESQUERDO),FWX_L3);
		processaControle( controle.controle.pressionado(CONTROLEX_OMBRO_DIREITO),FWX_RB);
		processaControle( controle.controle.pressionado(CONTROLEX_OMBRO_ESQUERDO),FWX_LB);

		processaControle( controle.controle.pressionado(CONTROLEX_BACK),FWX_SELECT);
		processaControle( controle.controle.pressionado(CONTROLEX_START),FWX_START);
	}
}

void FW_Entrada::processaControle( bool pressionado, int indice)
{
	if(pressionado)
	{
		if(controle.botoes[indice].ativo)
			controle.botoes[indice].pressionado = false;
		else
			controle.botoes[indice].pressionado = true;
	}
	else
	{
		if(controle.botoes[indice].ativo)
			controle.botoes[indice].liberado = true;
		else
			controle.botoes[indice].liberado = false;
	}


	controle.botoes[indice].ativo = pressionado;
}
