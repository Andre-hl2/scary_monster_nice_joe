

#ifndef __FW_RESOURCE_H__
#define __FW_RESOURCE_H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#define RESOURCE FW_Resouce::getInstance()

//parte da imagem
struct FW_Image
{
	SDL_Texture* texture; //a textura da imagem
	SDL_Rect dst;
	SDL_Rect src;
};

FW_Image* FW_carregaSprite(SDL_Renderer* renderer,char* caminhos, int largura, int altura);

void FW_desenhaSprite(SDL_Renderer* renderer,FW_Image* sprite, int indice,int x,int y);

void FW_DesenhaSpriteRot(SDL_Renderer* renderer,FW_Image* sprite, int indice, int x, int y, int angle, bool flip = false);

void FW_removeSprite( FW_Image* sprite );

FW_Image* FW_CarregaTextoFonte(SDL_Renderer* renderer,char* caminhoFonte,char* texto, SDL_Color cor);

//parte do som
class FW_Resouce
{
public:
	static FW_Resouce& getInstance();

	void tocaMusica(char* caminho);
	void trocaMusica(char* caminho);
	void pausaMusica();
	void retomaMusica();
	void paraMusica();
	void removeMusica();

private:
	static FW_Resouce* Instance;
	
	FW_Resouce() {}

	Mix_Music* musicaAtual;
};



//parte do save

struct FW_Save
{
	int mapa[32][24];
	int musica;
	int fundo;
	int tile;
	int tempo;
	int skin;	
};

FW_Save* FW_limpaSave();

void FW_SalvaJogo(char*caminho,FW_Save save);

FW_Save* FW_CarregaJogo(char* caminho);

struct FW_Perfil
{
	int passou;
	int estrelas[15];
};

FW_Perfil* FW_carregaPerfil(char* caminho);
void FW_SalvaPerfil(char* caminho,FW_Perfil perfil);
void FW_criaPerfil(char* caminho);
void FW_apagaPerfil(char* caminho);

#endif // __FW_RESOURCE_H__