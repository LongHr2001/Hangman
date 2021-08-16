#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <algorithm>

#include"game.h"

std::string getLowerCaseString(const std::string& s){
    std::string res = s;
    transform(s.begin(), s.end(), res.begin(), ::tolower);
    return res;
}

std::string string_toUpper(std::string word){
    int length = word.length();

    for(int i=0; i< length; i++){
        word[i] = char(toupper(word[i]));
    }

    return word;
}

bool contain(const std::string& word, char c){
    return (word.find_first_of(c) != std::string::npos);
}

void gameScene::chooseWord(){
	std::vector<std::string> wordList;
	std::ifstream file(fileName);
  	if (file.is_open()) {
	    std::string temp;
		while (file >> temp) {
            wordList.push_back(temp);
        }
    	file.close();
  	}
  	if (wordList.size() > 0) {
        while(true){
            int randomIndex = rand() % wordList.size();

            if(difficulty == 1){
                if(wordList[randomIndex].length() <= 5){
                    word = getLowerCaseString(wordList[randomIndex]);
                    break;
                }
            }
            else if(difficulty == 2){
                if(wordList[randomIndex].length() > 5){
                    word = getLowerCaseString(wordList[randomIndex]);
                    break;
                }
            }
        }
	}
	else{
        word = "";
	}
}

void game::wordUpdate(){
    int length = word.length();

    for(int i = 0; i < length; i++){
        if(word[i] == guess){
            guessWord[i] = word[i];
        }
    }
}

void game::hintUpdate(){
    int length = word.length();
    int i = rand() % length;

    while(guessWord[i] != '-'){
        i = rand() % length;
    }
    guessWord[i] = word[i];
}

void game::wrongLetterUpdate(){
    int length = wrongLetter.length();

    if(length > 0){
        for(int i=0;i<length;i++){
            if(wrongLetter[i] == char(toupper(guess)) && guess != ' '){
                return;
            }
        }
    }

    wrongLetter.push_back(' ');
    wrongLetter.push_back(char(toupper(guess)));

    badGuessCount++;
}
