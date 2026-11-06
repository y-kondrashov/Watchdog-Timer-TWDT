#include "Button.h"
#include "config.h"
#include "Infinite_loop.h"

#include <Arduino.h>

void Button::init()
{
    pinMode(BTN, INPUT_PULLDOWN);
}

void Button::poll()
{
    if (millis() - lastTimeChangeBtn > BTN_PERIOD_MS)
    {
        lastTimeChangeBtn = millis();
        const uint16_t btn_value = digitalRead(BTN);

        if (btn_value == HIGH)
        {
            
            if (btnTimekeeper == 0)
            {
                btnTimekeeper = millis();
            }

            uint32_t countedTime = millis() - btnTimekeeper;

            // if btn PRESSED form 1-4sec
            if (countedTime >= BTN_LONG_PRESS_MS
                && countedTime <= BTN_LONG_LONG_PRESS_MS)
                {
                    buttonState = true;
                    Serial.printf(
                        "btn %lu\n",
                        static_cast<unsigned long>(millis()));
                }

                // if btn PRESSED form > 4sec --> infinit loop
                if (countedTime >= BTN_LONG_LONG_PRESS_MS)
            {
                infiniteLoop();
            }
        }
        else
        {
            buttonState = false;
            btnTimekeeper = 0;
        }
    }
}

bool Button::get_state()
{
    return buttonState;
}