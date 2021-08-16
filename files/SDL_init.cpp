#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

void SDLErrorLog(const std::string& fileName, const std::string& errormsg){
    std::ofstream file(fileName);

    file << errormsg << " error: " << SDL_GetError() << std::endl;

    file.close();
}


void IMGErrorLog(const std::string& fileName, const std::string& errormsg){
    std::ofstream file(fileName);

    file << errormsg << " error: " << IMG_GetError() << std::endl;

    file.close();
}

void TTFErrorLog(const std::string& fileName, const std::string& errormsg){
    std::ofstream file(fileName);

    file << errormsg << " error: " << TTF_GetError() << std::endl;

    file.close();
}


int initSDL(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        SDLErrorLog("report.txt", "SDL_Init");
        return 1;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
        SDLErrorLog("report.txt", "IMG_Init");
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() != 0){
        SDLErrorLog("report.txt", "TTF_Init");
        SDL_Quit();
        return 1;
    }

    return 0;
}

void quitSDL(){
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int handlingInput(SDL_Event e){
    SDL_PollEvent(&e);
    switch(e.type){
    case SDL_QUIT:
        return -1;
    }

    return 0;
}

SDL_Texture* loadTexture(const char* textureName, SDL_Renderer* renderer){
    SDL_Texture* texture = IMG_LoadTexture(renderer, textureName);
    if(texture == nullptr){
        IMGErrorLog("report.txt", "loadTexture: IMG_LoadTexture");
    }

    return texture;
}

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y){
    SDL_Rect origin;

    origin.x = x;
    origin.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &origin.w, &origin.h);
	SDL_RenderCopy(renderer, texture, NULL, &origin);
}

void renderPartofTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int clipX, int clipY, int width, int height){
    SDL_Rect clip;
    SDL_Rect origin;

    clip.x = clipX;
    clip.y = clipY;
    clip.w = width;
    clip.h = height;

    origin.x = x;
    origin. y = y;
    origin.w = width;
    origin.h = height;

	SDL_RenderCopy(renderer, texture, &clip, &origin);
}

SDL_Texture* textToTexture(const std::string& text, const char* fontFile, SDL_Color color, int fontSize, SDL_Renderer* renderer){
    TTF_Font* font = TTF_OpenFont(fontFile, fontSize);
    if(font == nullptr){
        TTFErrorLog("report.txt", "textToTexture: TTF_OpenFont");
        return nullptr;
    }

	SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (surface == nullptr){
		TTF_CloseFont(font);
		TTFErrorLog("report.txt", "textToTexture: TTF_RenderText");
		return nullptr;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr){
		TTFErrorLog("report.txt", "textToTexture: CreateTexture");
	}

	SDL_FreeSurface(surface);


    return texture;
}


