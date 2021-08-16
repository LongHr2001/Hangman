#include <iostream>
#include <string>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include"SDL_init.h"
#include"gameOver.h"
#include"word.h"

int gameOver::winCount = 0;
int gameOver::loseCount = 0;

bool gameOver::getQuit(){
    return quit;
}

int gameOver::getReplay(){
    return replay;
}

gameOver::gameOver(SDL_Renderer* _renderer, int _windowWidth, int _windowHeight, bool _win, std::string& _word){
    renderer = _renderer;
    windowWidth = _windowWidth;
    windowHeight = _windowHeight;
    win = _win;
    word = _word;

    SDL_Color color = {255, 255, 255, 255};

    bg = loadTexture("bg.png", renderer);

    if(win){
        winCount++;

        man = loadTexture("win.png", renderer);

        response = textToTexture("YOU ARE SAVED!", "HangmanFont.ttf", color, 50, renderer);
    }
    else{
        loseCount++;

        man = loadTexture("lose.png", renderer);

        response = textToTexture("YOU ARE HUNG...", "HangmanFont.ttf", color, 50, renderer);
    }

    roundCount = winCount + loseCount;

    answer = textToTexture("The correct word is: " + string_toUpper(word), "HangmanFont.ttf", color, 25, renderer);
    roundPlayed = textToTexture("Rounds played: " + std::to_string(roundCount), "HangmanFont.ttf", color, 30, renderer);
    roundWon = textToTexture("Rounds won: " + std::to_string(winCount), "HangmanFont.ttf", color, 30, renderer);
    roundLost = textToTexture("Rounds lost: " + std::to_string(loseCount), "HangmanFont.ttf", color, 30, renderer);
    replayPrompt = textToTexture("Play again?", "HangmanFont.ttf", color, 30, renderer);
    yes = textToTexture("Replay", "HangmanFont.ttf", color, 30, renderer);
    no = textToTexture("Back to Menu", "HangmanFont.ttf", color, 30, renderer);

    pointer = loadTexture("pointer.png", renderer);



    Update();
}

gameOver::~gameOver(){
    SDL_RenderClear(renderer);
    renderer = nullptr;

    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(man);
    SDL_DestroyTexture(answer);
    SDL_DestroyTexture(response);
    SDL_DestroyTexture(pointer);
    SDL_DestroyTexture(roundPlayed);
    SDL_DestroyTexture(roundWon);
    SDL_DestroyTexture(roundLost);
    SDL_DestroyTexture(replayPrompt);
    SDL_DestroyTexture(yes);
    SDL_DestroyTexture(no);
}

void gameOver::Input(){
    SDL_Delay(100);
    SDL_PollEvent(&input);

    if(input.type == SDL_QUIT){
        quit = true;
    }
    else if(input.type == SDL_KEYDOWN){
        switch(input.key.keysym.sym){
            case SDLK_RETURN:
                replay = option;

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

    pointerY = 423 + (option-1)*40;
}

void gameOver::Render(){
    renderTexture(bg, renderer, 0, 0);

    Uint32 ticks = SDL_GetTicks();
    Uint32 frameLength = (ticks / 100);

    if(win){
        Uint32 frameLength = (ticks / 100);
        renderPartofTexture(man, renderer, 410, 50, 128*(frameLength%6), 0, 128, 204);
    }
    else{
        Uint32 frameLength = (ticks / 500);
        renderPartofTexture(man, renderer, 370, 50, 300*(frameLength%4), 0, 300, 200);
    }

    int responseWidth;
    SDL_QueryTexture(response, NULL, NULL, &responseWidth, NULL);
    renderTexture(response, renderer, (windowWidth - responseWidth)/2,250);

    int answerWidth;
    SDL_QueryTexture(answer, NULL, NULL, &answerWidth, NULL);
    renderTexture(answer, renderer, (windowWidth - answerWidth)/2,310);


    int pointerWidth;
    SDL_QueryTexture(pointer, NULL, NULL, &pointerWidth, NULL);
    renderTexture(pointer, renderer, (windowWidth - pointerWidth)/2 +270, pointerY);

    renderTexture(roundPlayed, renderer, 100, 370);
    renderTexture(roundWon, renderer, 100, 410);
    renderTexture(roundLost, renderer, 100, 450);

    int replayPromptWidth;
    SDL_QueryTexture(replayPrompt, NULL, NULL, &replayPromptWidth, NULL);
    renderTexture(replayPrompt, renderer, (windowWidth - replayPromptWidth)/2 + 270, 370);

    int yesWidth;
    SDL_QueryTexture(yes, NULL, NULL, &yesWidth, NULL);
    renderTexture(yes, renderer, (windowWidth - yesWidth)/2 + 270, 410);

    int noWidth;
    SDL_QueryTexture(no, NULL, NULL, &noWidth, NULL);
    renderTexture(no, renderer, (windowWidth - noWidth)/2 + 270, 450);
}

void gameOver::Update(){
    while(!quit){
        Input();

        if(replay == 1){
            break;
        }
        else if(replay == 2){
            break;
        }

        Render();

        SDL_RenderPresent(renderer);
    }
}


