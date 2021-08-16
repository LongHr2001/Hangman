#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <chrono>

#include"game.h"

bool gameScene::getQuit(){
    return quit;
}

bool gameScene::getDone(){
    return done;
}

gameScene::gameScene(SDL_Renderer* _renderer, int _windowWidth, int _windowHeight){
    renderer = _renderer;
    windowWidth = _windowWidth;
    windowHeight = _windowHeight;

    Update();
}

gameScene::~gameScene(){
    renderer = nullptr;
}

void gameScene::Input(){
    if(input.type == SDL_QUIT){
        quit = true;
    }
}

void gameScene::Update(){
    while(!quit && !done){
        srand(time(0));

        Input();

        if(categoryScene == nullptr){
            categoryScene = new catScene(renderer, windowWidth, windowHeight);

            quit = categoryScene -> getQuit();

            if(quit == true){
                delete categoryScene;
                categoryScene = nullptr;

                break;
            }

            category = categoryScene -> getCategory();
        }

        delete categoryScene;
        categoryScene = nullptr;

        if(category == 8){
            category = (rand() % 7) + 1;
        }

        switch(category){
            case 1:
                fileName = "animals.txt";
                break;

            case 2:
                fileName = "bodyparts.txt";
                break;

            case 3:
                fileName = "foods.txt";
                break;

            case 4:
                fileName = "jobs.txt";
                break;

            case 5:
                fileName = "objects.txt";
                break;

            case 6:
                fileName = "places.txt";
                break;

            case 7:
                fileName = "plants.txt";
                break;
        }

        if(difficultyScene == nullptr){
            difficultyScene = new diffScene(renderer, windowWidth, windowHeight);

            quit = difficultyScene -> getQuit();

            if(quit == true){
                delete difficultyScene;
                difficultyScene = nullptr;

                break;
            }

            difficulty = difficultyScene -> getDifficulty();
        }

        delete difficultyScene;
        difficultyScene = nullptr;

        chooseWord();
        if (word.empty()) {
            std::cout << "No word available in " << fileName << std::endl;
            break;
        }


        if(currentGame == nullptr){
            currentGame = new game(renderer, windowWidth, windowHeight, difficulty, word);

            quit = currentGame -> getQuit();

            if(quit == true){
                delete currentGame;
                currentGame = nullptr;

                break;
            }

            win = currentGame -> getWin();
        }

        delete currentGame;
        currentGame = nullptr;

        if(over == nullptr){
            over = new gameOver(renderer, windowWidth, windowHeight, win, word);

            quit = over -> getQuit();

            if(quit == true){
                delete over;
                over = nullptr;

                break;
            }

            if(over -> getReplay() == 2){
                done = true;
            }
        }

        delete over;
        over = nullptr;
    }
}
