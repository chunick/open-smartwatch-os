
#include "./apps/games/wordle/wordle.h"
#include "./apps/games/wordle/dictionary.h"

#include <gfx_util.h>
#include <osw_app.h>
#include <osw_hal.h>

// define global scope variables

void OswAppWordle::setup() {
    // this is where you initialise code, gets called when this app is shown
}

void OswAppWordle::loop() {
    // This section of the code is where you can write code that will loop.
    OswHal* hal = OswHal::getInstance();

    Dictionary dictionary;

    hal->gfx()->fill(0);
    hal->gfx()->setTextSize(2);
    hal->gfx()->setTextColor(rgb565(255, 0, 0), rgb565(0, 0, 0));  // colour changes: foreground, background
    hal->gfx()->setTextCursor(90, 120);                            // set (X,Y) coordinates for the 240x204px display
    hal->gfx()->print(dictionary.getRandomWord());
}

void OswAppWordle::stop() {
    // this is where you de-initialize stuff, gets called when another app is shown
}
