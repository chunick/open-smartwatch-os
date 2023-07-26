#ifndef OSW_APP_WORDLE_MENU_H
#define OSW_APP_WORDLE_MENU_H

#include <vector>
#include <osw_hal.h>
#include <vector>
#include <stdio.h>

class WordleMenu {
    private:
    std::vector<char> consonants;
    std::vector<char> vowels;
    int lettersMenuIndex;
    int currentConsonantIndex;
    int currentVowelIndex;
    bool btn3LongPressActive;
    bool btn2LongPressActive;

    bool isVowel(char c);
    bool isVowel(int c);
    bool consonantsSelected();
    bool vowelsSelected();

    public:
    void initialize();
    char getCurrentLetter();
    void removeCurrentLetter();
    int getConsonantCount();
    int getVowelCount();
    void toggleNextLetter();
    void toggleLetterMenu();
    void setBtnLongPressState(bool active, Button btn);
    bool btnIsLongPressed(Button btn);
};

#endif