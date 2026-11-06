#include <Arduino.h>
#include <esp_task_wdt.h>
#include <esp_system.h>
#include <esp_err.h>

#include "config.h"
#include "Button.h"
#include "Ldr.h"
#include "Led.h"

Button button;
Ldr ldr;
Led led;

void setup()
{
    Serial.begin(115200);
    delay(2000);

    button.init();
    ldr.init();
    led.init();

        // Таймаут watchdog
        ESP_ERROR_CHECK(esp_task_wdt_init(5, true));

    if (esp_task_wdt_status(NULL) != ESP_OK)
    {
        ESP_ERROR_CHECK(esp_task_wdt_add(NULL));
    }

    Serial.printf("Watchdog initialized: 5 seconds\n");

    Serial.printf(
        "reset reason: %d\n",
        esp_reset_reason()
    );
}

void loop()
{
    esp_task_wdt_reset();

    ldr.poll();
    button.poll();

    led.handler(button.get_state() && ldr.get_state());

    static uint32_t lastLog = 0;

    if (millis() - lastLog >= 200)
    {
        lastLog = millis();

        Serial.printf(
            "Button State: %d LDR State: %d\n",
            button.get_state(),
            ldr.get_state()
        );
    }
    delay(1);
}
