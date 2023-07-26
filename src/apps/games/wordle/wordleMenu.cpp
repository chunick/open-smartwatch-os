#include "./apps/games/wordle/wordleMenu.h"

bool WordleMenu::isVowel(char c) {
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

bool WordleMenu::isVowel(int c) {
    return c == 65 || c == 69 || c == 73 || c == 79 || c == 85;
}

bool WordleMenu::consonantsSelected() {
    return lettersMenuIndex == 0;
}

bool WordleMenu::vowelsSelected() {
    return lettersMenuIndex == 1;
}

void WordleMenu::initialize() {
    lettersMenuIndex = 0;
    currentConsonantIndex = 0;
    currentVowelIndex = 0;
    btn3LongPressActive = false;
    btn2LongPressActive = false;
    consonants.clear();
    vowels.clear();
    for (int c = 65; c <= 90; c++) {
        if (isVowel(c)) {
            vowels.push_back(c);
        } else {
            consonants.push_back(c);
        }
    }
}

char WordleMenu::getCurrentLetter() {
    if (consonantsSelected()) {
        return consonants[currentConsonantIndex];
    }
    return vowels[currentVowelIndex];
}

void WordleMenu::removeCurrentLetter() {
    if (consonantsSelected()) {
        consonants.erase(consonants.begin() + currentConsonantIndex);
    } else {
        vowels.erase(vowels.begin() + currentVowelIndex);
    }

    toggleNextLetter();
}

void WordleMenu::toggleNextLetter() {
    if (consonantsSelected()) {
        if ((consonants.size() - 1) > currentConsonantIndex) {
            currentConsonantIndex++;
        } else {
            currentConsonantIndex = 0;
        }
    } else {
        if (vowels.size() - 1 > currentVowelIndex) {
            currentVowelIndex++;
        } else {
            currentVowelIndex = 0;
        }
    }
}

void WordleMenu::toggleLetterMenu() {
    if (consonantsSelected()) {
        lettersMenuIndex = 1;
    } else {
        lettersMenuIndex = 0;
    }
}

int WordleMenu::getConsonantCount() {
    return consonants.size();
}

int WordleMenu::getVowelCount() {
    return vowels.size();
}

void WordleMenu::setBtnLongPressState(bool active, Button btn) {
    if (btn == BUTTON_3) {
        btn3LongPressActive = active;
    }
    if (btn == BUTTON_2) {
        btn2LongPressActive = active;
    }
}

bool WordleMenu::btnIsLongPressed(Button btn) {
    if (btn == BUTTON_3) {
        return btn3LongPressActive;
    }
    if (btn == BUTTON_2) {
        return btn2LongPressActive;
    }
}