#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include"scenes.h"

int scenesHandler::Input(){
    SDL_PollEvent(&input);

    if(input.type == SDL_QUIT){
        return -1;
    }
    return 0;
}

scenesHandler::scenesHandler(SDL_Renderer* _renderer, int _WindowWidth, int _WindowHeight){
    renderer = _renderer;
    WindowWidth = _WindowWidth;
    WindowHeight = _WindowHeight;

    Update();
}

scenesHandler::~scenesHandler(){
    delete credit;
    delete game;
    delete menu;

    credit = nullptr;
    game = nullptr;
    menu = nullptr;
    renderer = nullptr;
}

void scenesHandler::Update(){
    while(!quit){
        switch(currentScene){
            case MENU_SCENE:

                delete credit;
                delete game;
                credit = nullptr;
                game = nullptr;

                if(menu == nullptr){
                    menu = new menuScene(renderer, WindowWidth);

                    quit = menu -> getQuit();
                    currentScene = (Scenes)(menu -> getOption());
                }

                break;

            case CREDIT_SCENE:

                delete menu;
                delete game;
                menu = nullptr;
                game = nullptr;

                if(credit == nullptr){
                    credit = new creditScene(renderer, WindowWidth, WindowHeight);

                    quit = credit -> getQuit();

                    if(credit -> Back()){
                        currentScene = MENU_SCENE;
                    }
                }


                break;

            case GAME_SCENE:
                delete menu;
                delete credit;
                menu = nullptr;
                credit = nullptr;

                if(game == nullptr){
                    game = new gameScene(renderer, WindowWidth, WindowHeight);

                    quit = game -> getQuit();

                    if(game -> getDone()){
                        currentScene = MENU_SCENE;
                    }
                }

                break;
        }
    }
}


