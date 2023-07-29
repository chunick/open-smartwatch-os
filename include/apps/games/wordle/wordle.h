#ifndef OSW_APP_WORDLE_H
#define OSW_APP_WORDLE_H
#include "./apps/games/wordle/dictionary.h"
#include "./apps/games/wordle/wordleMenu.h"
#include <osw_hal.h>
#include <string>
#include <vector>
#include "osw_app.h"

class OswAppWordle : public OswApp {
  public:
    OswAppWordle(void) {};
    virtual void setup() override;
    virtual void loop() override;
    virtual void stop() override;

  private:
    enum GameState {
        IN_PROGRESS,
        WIN,
        LOSE
    };

    Dictionary* dictionary;
    WordleMenu* menu;
    std::vector<std::string> guesses;
    std::string wordToGuess;
    int selectedRowIndex;
    int selectedColIndex;
    GameState gameState;

    void drawMenu(OswHal* hal);
    void handleInput(OswHal* hal);
    void setLetter(int index, char letter);
    void submitGuess();
    void drawGame(OswHal* hal);
    void toggleNextCol();
    void initialize();
    std::vector<uint16_t> getLetterColors(int row);
    bool wordMatchesWordToGuess(std::string guess);
    void printCString(std::string string, OswHal* hal);
};
#endif
