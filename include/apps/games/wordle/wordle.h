#ifndef OSW_APP_WORDLE_H
#define OSW_APP_WORDLE_H

#include <osw_hal.h>

#include "osw_app.h"

class OswAppWordle : public OswApp {
  public:
    OswAppWordle(void) {};
    virtual void setup() override;
    virtual void loop() override;
    virtual void stop() override;
    ~OswAppWordle() {};

  private:
};

#endif
