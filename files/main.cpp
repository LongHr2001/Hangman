#include <iostream>

#include"SDL_init.h"
#include"scenes.h"
#include"menu.h"

int main(int argc, char **argv){
    //Init SDL
    if(initSDL() == 1){
        return 1;
    }

    //Create Window
    const std::string WINDOW_TITLE = "Hangman";
    const int WINDOW_X = 100;
    const int WINDOW_Y = 20;
    const int WINDOW_WIDTH = 960;
    const int WINDOW_HEIGHT = 540;

    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE.c_str(), WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        SDLErrorLog("report.txt", "SDL_CreateWindow");
        quitSDL();
        return 1;
    }

    //Create Renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        SDL_DestroyWindow(window);
        SDLErrorLog("report.txt", "SDL_Renderer");
        quitSDL();
        return 1;
    }

    scenesHandler* scene = nullptr;

    while(true){
        //Scenes Handler
        if(scene == nullptr){
            scene = new scenesHandler(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
        }

        if(scene -> quit){
            delete scene;
            scene = nullptr;
            break;
        }

    }

    //Free stuff and end this application's misery life
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    quitSDL();

    return 0;
}
