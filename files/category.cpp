#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include"SDL_init.h"
#include"category.h"

bool catScene::getQuit(){
    return quit;
}

int catScene::getCategory(){
    return category;
}

catScene::catScene(SDL_Renderer* _renderer, int _windowWidth, int _windowHeight){
    renderer = _renderer;
    windowWidth = _windowWidth;
    windowHeight = _windowHeight;

    SDL_Color color = {255, 255, 255, 255};

    bg = loadTexture("bg.png", renderer);
    chooseCategory = textToTexture("Choose Category:", "HangmanFont.ttf", color, 40, renderer);
    animals = textToTexture("Animals", "HangmanFont.ttf", color, 30, renderer);
    bodyparts = textToTexture("Body Parts", "HangmanFont.ttf", color, 30, renderer);
    foods = textToTexture("Foods & Drinks", "HangmanFont.ttf", color, 30, renderer);
    jobs = textToTexture("Jobs", "HangmanFont.ttf", color, 30, renderer);
    objects = textToTexture("Objects", "HangmanFont.ttf", color, 30, renderer);
    places = textToTexture("Places", "HangmanFont.ttf", color, 30, renderer);
    plants = textToTexture("Plants", "HangmanFont.ttf", color, 30, renderer);

    random = textToTexture("Random", "HangmanFont.ttf", color, 30, renderer);

    pointer = loadTexture("pointer.png", renderer);

    Update();
}

catScene::~catScene(){
    SDL_RenderClear(renderer);
    renderer = nullptr;

    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(chooseCategory);
    SDL_DestroyTexture(animals);
    SDL_DestroyTexture(bodyparts);
    SDL_DestroyTexture(foods);
    SDL_DestroyTexture(jobs);
    SDL_DestroyTexture(objects);
    SDL_DestroyTexture(places);
    SDL_DestroyTexture(plants);
    SDL_DestroyTexture(pointer);
    SDL_DestroyTexture(random);
}

void catScene::Input(){
    SDL_Delay(100);
    SDL_PollEvent(&input);

    if(input.type == SDL_QUIT){
        quit = true;
    }
    else if(input.type == SDL_KEYDOWN){
        switch(input.key.keysym.sym){
            case SDLK_RETURN:
                category = option;

                break;

            case SDLK_DOWN:
                option++;
                if(option > 8){
                    option = 1;
                }

                break;

            case SDLK_UP:
                option--;
                if(option < 1){
                    option = 8;
                }

                break;
        }
    }

    pointerY = 103 + (option-1)*50;
}

void catScene::Render(){
    renderTexture(bg, renderer, 0, 0);

    int chooseCategoryWidth;
    SDL_QueryTexture(chooseCategory, NULL, NULL, &chooseCategoryWidth, NULL);
    renderTexture(chooseCategory, renderer, (windowWidth - chooseCategoryWidth)/2, 10);

    int animalsWidth;
    SDL_QueryTexture(animals, NULL, NULL, &animalsWidth, NULL);
    renderTexture(animals, renderer, (windowWidth - animalsWidth)/2, 90);

    int bodypartsWidth;
    SDL_QueryTexture(bodyparts, NULL, NULL, &bodypartsWidth, NULL);
    renderTexture(bodyparts, renderer, (windowWidth - bodypartsWidth)/2, 140);

    int foodsWidth;
    SDL_QueryTexture(foods, NULL, NULL, &foodsWidth, NULL);
    renderTexture(foods, renderer, (windowWidth - foodsWidth)/2, 190);

    int jobsWidth;
    SDL_QueryTexture(jobs, NULL, NULL, &jobsWidth, NULL);
    renderTexture(jobs, renderer, (windowWidth - jobsWidth)/2, 240);

    int objectsWidth;
    SDL_QueryTexture(objects, NULL, NULL, &objectsWidth, NULL);
    renderTexture(objects, renderer, (windowWidth - objectsWidth)/2, 290);

    int placesWidth;
    SDL_QueryTexture(places, NULL, NULL, &placesWidth, NULL);
    renderTexture(places, renderer, (windowWidth - placesWidth)/2, 340);

    int plantsWidth;
    SDL_QueryTexture(plants, NULL, NULL, &plantsWidth, NULL);
    renderTexture(plants, renderer, (windowWidth - plantsWidth)/2, 390);

    int randomWidth;
    SDL_QueryTexture(random, NULL, NULL, &randomWidth, NULL);
    renderTexture(random, renderer, (windowWidth - randomWidth)/2, 440);

    int pointerWidth;
    SDL_QueryTexture(pointer, NULL, NULL, &pointerWidth, NULL);
    renderTexture(pointer, renderer, (windowWidth - pointerWidth)/2, pointerY);
}

void catScene::Update(){
    while(category == 0 && !quit){
        Input();

        Render();

        SDL_RenderPresent(renderer);
    }
}


