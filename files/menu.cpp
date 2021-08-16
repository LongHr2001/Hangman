#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include"menu.h"

bool menuScene::getQuit(){
    return quit;
}

int menuScene::getOption(){
    return option;
}

int menuScene::Input(){
    SDL_Delay(100);
    SDL_PollEvent(&input);

    if(input.type == SDL_QUIT){
        quit = true;
    }
    else if(input.type == SDL_KEYDOWN){
        switch(input.key.keysym.sym){
            case SDLK_RETURN:
                return option;

                break;

            case SDLK_DOWN:
                option++;
                if(option > 3){
                    option = 1;
                }

                break;

            case SDLK_UP:
                option--;
                if(option < 1){
                    option = 3;
                }

                break;
        }
    }

    menuPointerY = 353 + (option-1)*60;

    return 0;
}

void menuScene::setWindowWidth(int _windowWidth){
    windowWidth = _windowWidth;
}

void menuScene::setRenderer(SDL_Renderer* _renderer){
    renderer = _renderer;
}

menuScene::menuScene(SDL_Renderer* renderer, int windowWidth){
    setRenderer(renderer);
    setWindowWidth(windowWidth);

    SDL_Color color = {255, 255, 255, 255};

    bg = loadTexture("bg.png", renderer);
    logo = loadTexture("logo.png", renderer);
    playButton = textToTexture("Play", "HangmanFont.ttf", color, 30, renderer);
    creditButton = textToTexture("Credit", "HangmanFont.ttf", color, 30, renderer);
    quitButton = textToTexture("Quit", "HangmanFont.ttf", color, 30, renderer);
    menuPointer = loadTexture("pointer.png", renderer);

    Update();
}

menuScene::~menuScene(){
    SDL_RenderClear(renderer);

    renderer = nullptr;

    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(logo);
    SDL_DestroyTexture(playButton);
    SDL_DestroyTexture(creditButton);
    SDL_DestroyTexture(quitButton);
    SDL_DestroyTexture(menuPointer);
}

void menuScene::Render(){
    renderTexture(bg, renderer, 0, 0);

    int logoWidth;
    SDL_QueryTexture(logo, NULL, NULL, &logoWidth, NULL);
    renderTexture(logo, renderer, (windowWidth - logoWidth)/2 - 20,40);

    int playButtonWidth;
    SDL_QueryTexture(playButton, NULL, NULL, &playButtonWidth, NULL);
    renderTexture(playButton, renderer, (windowWidth - playButtonWidth)/2,340);

    int creditButtonWidth;
    SDL_QueryTexture(creditButton, NULL, NULL, &creditButtonWidth, NULL);
    renderTexture(creditButton, renderer, (windowWidth - creditButtonWidth)/2,400);

    int quitButtonWidth;
    SDL_QueryTexture(quitButton, NULL, NULL, &quitButtonWidth, NULL);
    renderTexture(quitButton, renderer, (windowWidth - quitButtonWidth)/2,460);

    int menuPointerWidth;
    SDL_QueryTexture(menuPointer, NULL, NULL, &menuPointerWidth, NULL);
    renderTexture(menuPointer, renderer, (windowWidth - menuPointerWidth)/2, menuPointerY);
}

void menuScene::Update(){
    while(!quit && !done){
        switch(Input()){
            case 1:
            case 2:
                done = true;
                break;
            case 3:
                quit = true;
                break;
        }

        Render();

        SDL_RenderPresent(renderer);
    }
}

