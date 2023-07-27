#include "./apps/games/wordle/wordle.h"
#include "./apps/games/wordle/dictionary.h"
#include <gfx_util.h>
#include <osw_app.h>
#include <osw_hal.h>
#include <string.h>
#include <vector>

bool debug = false;

void OswAppWordle::setup() {
    dictionary = new Dictionary();
    menu = new WordleMenu();
    initialize();
}

void OswAppWordle::initialize() {
    menu->initialize();
    wordToGuess = dictionary->getRandomWord();
    selectedRowIndex = 0;
    selectedColIndex = 0;
    gameState = IN_PROGRESS;

    guesses.clear();
    for (int i = 0; i < 6; i++) {
        guesses.push_back("     ");
    }
}

void OswAppWordle::loop() {
    // This section of the code is where you can write code that will loop.
    OswHal* hal = OswHal::getInstance();

    handleInput(hal);
    drawMenu(hal);
    drawGame(hal);
}

void OswAppWordle::handleInput(OswHal* hal) {
    if (gameState == IN_PROGRESS) {
        if(hal->btnIsLongPress(BUTTON_3)) {
            menu->setBtnLongPressState(true, BUTTON_3);
        }
        if (hal->btnHasGoneUp(BUTTON_3)) {
            if (menu->btnIsLongPressed(BUTTON_3)) {
                menu->toggleLetterMenu();
                menu->setBtnLongPressState(false, BUTTON_3);
            } else {
                menu->toggleNextLetter();
            }
        }
        if(hal->btnIsLongPress(BUTTON_2)) {
            menu->setBtnLongPressState(true, BUTTON_2);
        }
        if (hal->btnHasGoneUp(BUTTON_2)) {
            if (menu->btnIsLongPressed(BUTTON_2)) {
                submitGuess();
                menu->setBtnLongPressState(false, BUTTON_2);
            } else {
                toggleNextCol();
            }
        }
        if (hal->btnHasGoneUp(BUTTON_1)) {
            setLetter(selectedColIndex, menu->getCurrentLetter());
        }
    } else {
        if (hal->btnHasGoneUp(BUTTON_1) || hal->btnHasGoneUp(BUTTON_2) || hal->btnHasGoneUp(BUTTON_3)) {
            // restart game on button press
            initialize();
        }
    }
}

void OswAppWordle::drawMenu(OswHal* hal) {
    hal->gfx()->fill(0);
    hal->gfx()->setTextCursor(200, 60);
    hal->gfx()->print(menu->getCurrentLetter());
}

void OswAppWordle::drawGame(OswHal* hal) {
    if (debug) {
        hal->gfx()->setTextCursor(35, 40);
        hal->gfx()->setTextSize(1);
        hal->gfx()->print(wordToGuess);
    }
    if (gameState == IN_PROGRESS) {
        int y = 50;
        for (int i = 0; i < 6; i++) {
            std::vector<uint16_t> letterColors = getLetterColors(i);
            hal->gfx()->setTextSize(2);
            int x = 75;
            hal->gfx()->setTextCursor(x, y);
            for (int j = 0; j < 5; j++) {
                uint16_t lineColor = selectedColIndex == j && selectedRowIndex == i ? rgb565(0, 255, 0) : rgb565(255, 255, 255);
                hal->gfx()->setTextCursor(x, y);
                hal->gfx()->drawHLine(x, y + 4, 10, lineColor);
                hal->gfx()->setTextCursor(x, y);
                hal->gfx()->setTextColor(letterColors[j]);
                hal->gfx()->print(guesses[i][j]);
                x +=20;
            }
            y += 30;
        }
    } else {
        uint16_t textColor = gameState == WIN ? rgb565(0, 255, 0) : rgb565(255, 0, 0);
        hal->gfx()->setTextCursor(90, 130);
        hal->gfx()->setTextColor(textColor);
        hal->gfx()->setTextSize(2);
        hal->gfx()->print(wordToGuess);
    }
}

std::vector<uint16_t> OswAppWordle::getLetterColors(int row) {
    std::vector<uint16_t> colors;

    if (row == selectedRowIndex) {
        for (int i = 0; i < 5; i++) {
            colors.push_back(rgb565(255, 255, 255));
        }

        return colors;
    }

    for (int i = 0; i < 5; i++) {
        colors.push_back(0);
    }

    std::string word = guesses[row];
    std::vector<char> remainingLetters;

    // letters in correct location
    for (int i = 0; i < 5; i++) {
        char expectedChar = (wordToGuess[i] - 32);
        if (expectedChar == word[i]) {
            colors[i] = rgb565(0, 255, 0);
        } else {
            remainingLetters.push_back(expectedChar);
        }
    }



    // letters in wrong location
    for (int i = 0; i < 5; i++) {
        if (colors[i] == 0) {
            int indexToRemove = -1;
            for (int j = 0; j < remainingLetters.size(); j++) {
                // letter exists in word to guess
                if (remainingLetters[j] == word[i]) {
                    indexToRemove = j;
                    break;
                }
            }

            if (indexToRemove >= 0) {
                colors[i] = rgb565(255, 255, 0);
                remainingLetters.erase(remainingLetters.begin()+indexToRemove);
            }
        }
    }

    // letters not in word
    for (int i = 0; i < 5; i++) {
        if (colors[i] == 0) {
            colors[i] = rgb565(211, 211, 211);
        }
    }

    return colors;
}

void OswAppWordle::setLetter(int index, char letter) {
    guesses[selectedRowIndex][index] = letter;
    toggleNextCol();
}

void OswAppWordle::submitGuess() {
    for (int i = 0; i < 5; i++) {
        if (guesses[selectedRowIndex][i] == ' ') {
            return;
        }
    }

    if (wordMatchesWordToGuess(guesses[selectedRowIndex])) {
        gameState = WIN;
    } else if (selectedRowIndex < 5) {
        selectedRowIndex++;
        selectedColIndex = 0;
    } else {
        gameState = LOSE;
    }
}

bool OswAppWordle::wordMatchesWordToGuess(std::string guess) {
    for(int i = 0; i < 5; i++) {
        if ((wordToGuess[i] - 32) != guess[i]) {
            return false;
        }
    }
    return true;
}

void OswAppWordle::toggleNextCol() {
    if (selectedColIndex == 4) {
        selectedColIndex = 0;
    } else {
        selectedColIndex++;
    }
}

void OswAppWordle::stop() {
    delete menu;
    delete dictionary;
}