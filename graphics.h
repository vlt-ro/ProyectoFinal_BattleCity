#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

namespace graphics
{
    //Screen dimension constants
    const int UN = 16; //Número mínimo de pixeles
    const int SCREEN_WIDTH = 29*UN;
    const int SCREEN_HEIGHT = 26*UN;

    //Starts up SDL and creates window
    bool init();

    //Loads media
    bool loadMedia();

    //Frees media and shuts down SDL
    void close();

    //Loads individual image as texture
    SDL_Texture* loadTexture( std::string path );

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    vector<SDL_Texture*> gTextures;

	bool init()
	{
		//Initialization flag
		bool success = true;

		//Initialize SDL
		if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Set texture filtering to linear
			if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
			{
				printf( "Warning: Linear texture filtering not enabled!" );
			}

			//Create window
			gWindow = SDL_CreateWindow( "BATTLE_CITY", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
			if( gWindow == NULL )
			{
				printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Create renderer for window
				gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

				if( gRenderer == NULL )
				{
					printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
					success = false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if( !( IMG_Init( imgFlags ) & imgFlags ) )
					{
						printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
						success = false;
					}
					else
					{
						if( TTF_Init()==-1 )
						{
							printf("TTF_Init could not initialize! SDL_image Error: %s\n", TTF_GetError());
							success = false;
						}
					}
				}
			}
		}

		return success;
	}

	//Loads media
	bool loadMedia()
	{
		//Loading success flag
		bool success = true;
		 string path_textures = "resources/texturas.txt"; // Nombre del archivo

		// Se revisa si el archivo existe
		/*-------------------------------*/
		ifstream file(path_textures.c_str());

		if(file.fail())
		{
		  printf("El archivo no existe");
		  exit(1);
		}

		string str;
		vector<string> texturas;

		while (getline(file,str)){ texturas.push_back(str);} // Recorre cada fila del archivo obteniendo las palabras


		//Load PNG texture
		/*Tengo que hacer que pase por un arreglo de texturas y revise si todas están disponibles*/
		for (int i = 0; i < texturas.size(); ++i)
		{
			gTextures.push_back(loadTexture( texturas[i] ));
			if( gTextures[i]==NULL)
			{
				printf( "Failed to load texture image!\n" );
				success = false;
			}
		}

		return success;
	}

	  //Frees media and shuts down SDL
	void close()
	{
		//Free loaded image
		for (int i = 0; i < gTextures.size(); ++i)
		{
			SDL_DestroyTexture( gTextures[i] );
			gTextures[i] = NULL;
		}

		//Destroy window
		SDL_DestroyRenderer( gRenderer );
		SDL_DestroyWindow( gWindow );
		gWindow = NULL;
		gRenderer = NULL;

		//Quit SDL subsystems
		IMG_Quit();
		SDL_Quit();
	}

	SDL_Texture* loadTexture( std::string path )
	{
		//The final texture
		SDL_Texture* newTexture = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
		if( loadedSurface == NULL )
		{
			printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
		}
		else
		{
			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
			if( newTexture == NULL )
			{
				printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
			}

			//Get rid of old loaded surface
			SDL_FreeSurface( loadedSurface );
		}

		return newTexture;
	}

	void RenderRectangle(int RectangleXPosition, int RectangleYPosition, int RectangleWidth, int RectangleHeight, SDL_Color RectangleColor, bool Filled)
	{
		// Create the rectangle to render
		SDL_Rect Rectangle = {RectangleXPosition, RectangleYPosition, RectangleWidth, RectangleHeight};

		// Set the rectangle color
		SDL_SetRenderDrawColor(gRenderer, RectangleColor.r, RectangleColor.g, RectangleColor.b, RectangleColor.a);

		// Render a filled rectangle
		if(Filled)
			SDL_RenderFillRect(gRenderer, &Rectangle);

		// Render a unfilled rectangle
		else
			SDL_RenderDrawRect(gRenderer, &Rectangle);
	}


	void RenderText(string font_name, int font_size, string text,SDL_Color text_color, int w, int h, int y, int x )

	{
		SDL_Texture* text_texture = nullptr;
		SDL_Surface* text_surface = nullptr;
		TTF_Font* font = TTF_OpenFont(font_name.c_str(), font_size);

		if(font == nullptr)
		{
			printf( "SDL_ttf no pudo cargar las fuentes! SDL_ttf Error: %s\n", TTF_GetError() );
		}

		text_surface = TTF_RenderText_Solid(font, text.c_str(), text_color);

		text_texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);

		SDL_Rect drcrect1;

		drcrect1.x = x;
		drcrect1.y = y;
		drcrect1.w = w;
		drcrect1.h = h;

		SDL_RenderCopy(gRenderer, text_texture, NULL,&drcrect1);


	}

	void map()
	{
		//Clear screen
		SDL_RenderClear( gRenderer );

		SDL_Color RectangleColor1 = {0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE};
		RenderRectangle(0, 0, SCREEN_WIDTH-48, SCREEN_HEIGHT, RectangleColor1, true);

		SDL_Color RectangleColor2 = {0x60, 0x60, 0x60, SDL_ALPHA_OPAQUE};
		RenderRectangle(SCREEN_WIDTH-48, 0, 48, SCREEN_HEIGHT, RectangleColor2, true);

		string path_map = "resources/mapa.csv"; // Nombre del archivo

		// Se revisa si el archivo existe
		/*-------------------------------*/
		ifstream file(path_map.c_str());

		if(file.fail())
		{
			printf("El archivo no existe");
			exit(1);
		}

		string str;
		vector<string> mapa;

		while (getline(file,str)){ mapa.push_back(str);} // Recorre cada fila del archivo obteniendo las palabras


		SDL_Rect srcrect1;
		SDL_Rect dstrect1;

		srcrect1.x = 0;
		srcrect1.y = 0;
		srcrect1.w = UN;
		srcrect1.h = UN;

		dstrect1.w = UN;
		dstrect1.h = UN;

		for (int i = 0; i < mapa.size(); ++i)
		{
			for (int j = 0; j < mapa[0].size(); ++j)
			{
				dstrect1.y = UN*i;
				dstrect1.x = UN*j;

				switch(mapa[i][j])
				{
					case 'b':
						SDL_RenderCopy(gRenderer, gTextures[0], &srcrect1, &dstrect1);
						break;

					case 'c':
						SDL_RenderCopy(gRenderer, gTextures[1], &srcrect1, &dstrect1);
						break;

					case 'f':
						srcrect1.w = UN*2;
						srcrect1.h = UN*2;

						dstrect1.w = UN*2;
						dstrect1.h = UN*2;

						SDL_RenderCopy(gRenderer, gTextures[2], &srcrect1, &dstrect1);

						srcrect1.w = UN;
						srcrect1.h = UN;

						dstrect1.w = UN;
						dstrect1.h = UN;
						break;
					case '.':
					case ' ':
						break;
					default:
						//printf("Textura desconocida\n");
						//cout<<mapa[i][j]<<endl;
						break;
				}
			}
		}
		//Update screen
		SDL_RenderPresent( gRenderer );
	}

}

#endif // GRAPHICS_H
