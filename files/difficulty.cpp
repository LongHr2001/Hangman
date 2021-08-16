#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include"SDL_init.h"
#include"difficulty.h"

bool diffScene::getQuit(){
    return quit;
}

int diffScene::getDifficulty(){
    return difficulty;
}

diffScene::diffScene(SDL_Renderer* _renderer, int _windowWidth, int _windowHeight){
    renderer = _renderer;
    windowWidth = _windowWidth;
    windowHeight = _windowHeight;

    SDL_Color color = {255, 255, 255, 255};

    bg = loadTexture("bg.png", renderer);
    chooseDifficulty = textToTexture("Choose Difficulty:", "HangmanFont.ttf", color, 40, renderer);
    easy = textToTexture("Easy", "HangmanFont.ttf", color, 35, renderer);
    hard = textToTexture("Hard", "HangmanFont.ttf", color, 35, renderer);
    pointer = loadTexture("pointer.png", renderer);

    Update();
}

diffScene::~diffScene(){
    SDL_RenderClear(renderer);
    renderer = nullptr;

    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(chooseDifficulty);
    SDL_DestroyTexture(easy);
    SDL_DestroyTexture(hard);
    SDL_DestroyTexture(pointer);
}

void diffScene::Input(){
    SDL_Delay(100);
    SDL_PollEvent(&input);

    if(input.type == SDL_QUIT){
        quit = true;
    }
    else if(input.type == SDL_KEYDOWN){
        switch(input.key.keysym.sym){
            case SDLK_RETURN:
                difficulty = option;

                break;

            case SDLK_DOWN:
                option++;
                if(option > 2){
                    option = 1;
                }

                break;

            case SDLK_UP:
                option--;
                if(option < 1){
                    option = 2;
                }

                break;
        }
    }

    pointerY = 270 + (option-1)*70;
}

void diffScene::Render(){
    renderTexture(bg, renderer, 0, 0);

    int chooseDifficultyWidth;
    SDL_QueryTexture(chooseDifficulty, NULL, NULL, &chooseDifficultyWidth, NULL);
    renderTexture(chooseDifficulty, renderer, (windowWidth - chooseDifficultyWidth)/2, 160);

    int easyWidth;
    SDL_QueryTexture(easy, NULL, NULL, &easyWidth, NULL);
    renderTexture(easy, renderer, (windowWidth - easyWidth)/2, 250);

    int hardWidth;
    SDL_QueryTexture(hard, NULL, NULL, &hardWidth, NULL);
    renderTexture(hard, renderer, (windowWidth - hardWidth)/2, 320);

    int pointerWidth;
    SDL_QueryTexture(pointer, NULL, NULL, &pointerWidth, NULL);
    renderTexture(pointer, renderer, (windowWidth - pointerWidth)/2, pointerY);
}

void diffScene::Update(){
    while(difficulty == 0 && !quit){
        Input();

        Render();

        SDL_RenderPresent(renderer);
    }
}


