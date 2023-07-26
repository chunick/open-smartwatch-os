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
    void drawMenu(OswHal* hal);
    void handleInput(OswHal* hal);
    void setLetter(int index, char letter);
    void submitGuess();
    void drawGame(OswHal* hal);
    void toggleNextCol();
    std::vector<uint16_t> getLetterColors(int row);

  private:
    Dictionary* dictionary;
    WordleMenu* menu;
    std::vector<std::string> guesses;
    std::string wordToGuess;
    int selectedRowIndex;
    int selectedColIndex;
};
#endif
