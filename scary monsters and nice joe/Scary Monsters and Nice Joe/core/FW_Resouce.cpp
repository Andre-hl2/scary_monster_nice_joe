
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "../Main.hpp"
#include "Ator.h"
#include "FW_Resource.h"

FW_Resouce& FW_Resouce::getInstance()
{
	static FW_Resouce Instance;

	return Instance;
}

FW_Image* FW_carregaSprite(SDL_Renderer* renderer, char* caminho, int largura, int altura)
{
	SDL_Surface* temp = IMG_Load(caminho);
	FW_Image *image = new FW_Image;

	image->texture = SDL_CreateTextureFromSurface( renderer,	temp );

	if(temp != NULL)  //se carregou a surface
	{
		if((largura == 0) && (altura == 0)) //se deseja pegar a imagem inteira
		{
			image->dst.h = image->src.h = temp->h;
			image->dst.w = image->src.w = temp->w;

			image->src.y = 0;
		}
		else // se é um sprite set
		{
			image->dst.h = image->src.h = altura;
			image->dst.w = image->src.w = largura;

			image->src.y = 0;
		}

		SDL_FreeSurface( temp );
		return image;

	}
	else // se não carregou a surface
	{
		image->dst.h = image->dst.w = 0;
		image->src.h = image->src.w = 0;

		SDL_FreeSurface( temp );

		return image;
	}
		
}

void FW_desenhaSprite(SDL_Renderer* renderer, FW_Image* sprite, int indice, int posX, int posY)
{
	if(sprite->texture != NULL)
	{
		sprite->src.x = sprite->src.w*indice;
		sprite->dst.x = posX;
		sprite->dst.y = posY;

		SDL_RenderCopy(renderer,sprite->texture,&sprite->src, &sprite->dst);
	}
}

void FW_DesenhaSpriteRot(SDL_Renderer* renderer,FW_Image* sprite, int indice, int x, int y, int angle,bool flip)
{
	if(sprite->texture != NULL)
	{
		sprite->src.x = sprite->src.w*indice;
		sprite->dst.x = x;
		sprite->dst.y = y;

		SDL_Point pont;

		pont.x = sprite->src.x + (sprite->src.w/2);
		pont.y = sprite->src.y + (sprite->src.h/2);

		if(flip)
			SDL_RenderCopyEx(renderer,sprite->texture,&sprite->src,&sprite->dst, angle,&pont,SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopyEx(renderer,sprite->texture,&sprite->src,&sprite->dst, angle,&pont,SDL_FLIP_NONE);
	}
}

void FW_removeSprite( FW_Image* sprite )
{
	if(sprite->texture != NULL)
	{
		SDL_DestroyTexture( sprite->texture );
		sprite->texture = NULL;
	}

	delete sprite;
}

FW_Image* FW_CarregaTextoFonte(SDL_Renderer* renderer,char* caminhoFonte,char* texto, SDL_Color cor)
{

	 TTF_Font *gFont = TTF_OpenFont( "DATA/arial.ttf", 40 );

	 FW_Image* image = new FW_Image;

	 if(gFont != NULL)
	 {

		 //Render text surface
		SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, texto, cor );
		if( textSurface == NULL )
		{
			printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
		}
		else
		{
			//Create texture from surface pixels
			image->texture = SDL_CreateTextureFromSurface( renderer, textSurface );
			if( image->texture== NULL )
			{
				printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{
				//Get image dimensions
				image->src.w = image->dst.w = textSurface->w;
				image->src.h = image->dst.h = textSurface->h;
				image->src.x = image->src.y = 0;
			}

			//Get rid of old surface
			SDL_FreeSurface( textSurface );
		}

		TTF_CloseFont(gFont);
	 }
	 else
	 {
		 printf("Nao carregou a fonte");
	 }

	return image;
}



void FW_Resouce::tocaMusica(char* caminho)
{
	musicaAtual = Mix_LoadMUS(caminho);

	Mix_PlayMusic(musicaAtual,-1);
}

void FW_Resouce::trocaMusica(char* caminho)
{
	Mix_HaltMusic();
	Mix_FreeMusic(musicaAtual);
	musicaAtual = NULL;

	musicaAtual = Mix_LoadMUS(caminho);
	Mix_PlayMusic(musicaAtual, -1);
}

void FW_Resouce::pausaMusica()
{
	Mix_PauseMusic();
}

void FW_Resouce::retomaMusica()
{
	Mix_ResumeMusic();
}

void FW_Resouce::paraMusica()
{
	Mix_HaltMusic();
}

void FW_Resouce::removeMusica()
{
	Mix_FreeMusic( musicaAtual );
	musicaAtual = NULL;
}

FW_Save* FW_limpaSave()
{
	FW_Save* limpo = new FW_Save;

	
	for(int i=0;i<32;i++)
	{
		for(int j=0;j<24;j++)
		{
			if(i==0 || i==31 || j==0 || j==23 || j == 22 || j == 1 || j == 2)
				limpo->mapa[i][j] = 1;
			else
				limpo->mapa[i][j] = 0;
		}
	}

	return limpo;
}

void FW_SalvaJogo(char*caminho,FW_Save save)
{
	FILE *file;

	FW_Save* ptr = &save;
	
	if ((file = fopen(caminho, "wb"))==NULL)
	{
		printf("\nImpossível criar o arquivo - '%s'.",caminho);
		return;
	}
	fwrite(ptr, sizeof(FW_Save), 1, file);

	fclose(file);
}

FW_Save* FW_CarregaJogo(char* caminho)
{
	FILE *file;

	FW_Save *temp = new FW_Save;

	if ((file = fopen(caminho, "rb"))==NULL)
	{
		printf("\nImpossível ler o arquivo - '%s'.",caminho);
		return NULL;
	}

	fread(temp, sizeof(FW_Save), 1, file);

	fclose(file);

	return temp;
}

FW_Perfil* FW_carregaPerfil(char* caminho)
{
	FILE *file;

	FW_Perfil *temp = new FW_Perfil;

	if ((file = fopen(caminho, "rb"))==NULL)
	{
		printf("\nImpossível ler o arquivo - '%s'.",caminho);
		return NULL;
	}

	fread(temp, sizeof(FW_Perfil), 1, file);

	fclose(file);

	return temp;
}

void FW_SalvaPerfil(char* caminho,FW_Perfil perfil)
{
	FILE *file;

	FW_Perfil* ptr = &perfil;
	
	if ((file = fopen(caminho, "wb"))==NULL)
	{
		printf("\nImpossível criar o arquivo - '%s'.",caminho);
		return;
	}
	fwrite(ptr, sizeof(FW_Perfil), 1, file);

	fclose(file);
}

void FW_criaPerfil(char* caminho)
{
	FILE *file;

	FW_Perfil* ptr = new FW_Perfil;

	ptr->passou = 1;

	for(int i=0;i<15;i++)
	{
		ptr->estrelas[i]= 0;
	}

	if ((file = fopen(caminho, "wb"))==NULL)
	{
		printf("\nImpossível criar o arquivo - '%s'.",caminho);
		return;
	}
	fwrite(ptr, sizeof(FW_Perfil), 1, file);

	fclose(file);
}

void FW_apagaPerfil(char* caminho)
{
	FILE *file;

	FW_Perfil* ptr = new FW_Perfil;

	ptr->passou = 1;

	for(int i=0;i<15;i++)
	{
		ptr->estrelas[i]= 0;
	}

	if ((file = fopen(caminho, "wb"))==NULL)
	{
		printf("\nImpossível criar o arquivo - '%s'.",caminho);
		return;
	}
	fwrite(ptr, sizeof(FW_Perfil), 1, file);

	fclose(file);
}
