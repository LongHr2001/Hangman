#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include"SDL_init.h"
#include"credit.h"

bool creditScene::getQuit(){
    return quit;
}

bool creditScene::Back(){
    return toMenu;
}

void creditScene::Input(){
    SDL_PollEvent(&input);

    if(input.type == SDL_QUIT){
        quit = true;
    }
    else if(input.type == SDL_KEYDOWN && input.key.keysym.sym == SDLK_ESCAPE){
        toMenu = true;
    }
}

creditScene::creditScene(SDL_Renderer* _renderer, int _windowWidth, int _windowHeight){
    renderer = _renderer;
    windowWidth = _windowWidth;
    windowHeight = _windowHeight;

    SDL_Color color = {255, 255, 255, 255};

    bg = loadTexture("bg.png", renderer);
    logo = loadTexture("logo.png", renderer);
    gameBy = textToTexture("Game by: Nguyen Vu Hai Long", "HangmanFont.ttf", color, 30, renderer);
    fontName = textToTexture("Font: SVN-Avo Bold", "HangmanFont.ttf", color, 30, renderer);
    escToExit = textToTexture("Press ESC to Exit", "HangmanFont.ttf", color, 30, renderer);

    Update();
}

creditScene::~creditScene(){
    SDL_RenderClear(renderer);
    renderer = nullptr;

    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(logo);
    SDL_DestroyTexture(gameBy);
    SDL_DestroyTexture(fontName);
    SDL_DestroyTexture(escToExit);
}

void creditScene::Render(){
    renderTexture(bg, renderer, 0, 0);

    int logoWidth;
    SDL_QueryTexture(logo, NULL, NULL, &logoWidth, NULL);
    renderTexture(logo, renderer, (windowWidth - logoWidth)/2 - 20,40);

    int gameByWidth;
    SDL_QueryTexture(gameBy, NULL, NULL, &gameByWidth, NULL);
    renderTexture(gameBy, renderer, (windowWidth - gameByWidth)/2, 280);

    int fontNameWidth;
    SDL_QueryTexture(fontName, NULL, NULL, &fontNameWidth, NULL);
    renderTexture(fontName, renderer, (windowWidth - fontNameWidth)/2, 340);

    int escToExitWidth;
    SDL_QueryTexture(escToExit, NULL, NULL, &escToExitWidth, NULL);
    renderTexture(escToExit, renderer, (windowWidth - escToExitWidth)/2, 480);
}

void creditScene::Update(){
    while(!quit && !toMenu){
        Input();

        Render();

        SDL_RenderPresent(renderer);
    }
}
