#ifndef SDL_INIT_H_INCLUDED
#define SDL_INIT_H_INCLUDED

#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//Error log
void SDLErrorLog(const std::string& fileName, const std::string& errormsg);
void IMGErrorLog(const std::string& fileName, const std::string& errormsg);
void TTFErrorLog(const std::string& fileName, const std::string& errormsg);

//Basic stuffs
int initSDL();
int handlingInput(SDL_Event e);
void quitSDL();

SDL_Texture* loadTexture(const char* textureName, SDL_Renderer* renderer);
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y);
void renderPartofTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int clipX, int clipY, int width, int height);
SDL_Texture* textToTexture(const std::string& text, const char* fontFile, SDL_Color color, int fontSize, SDL_Renderer* renderer);



#endif // SDL_INIT_H_INCLUDED
