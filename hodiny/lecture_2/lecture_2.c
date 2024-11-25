// Pico SDK libraries
#include "pico/stdlib.h"
#include "pico/time.h"

// Standard libraries
#include <stdio.h>
#include <stdbool.h>

#define LED_PIN 6
#define BUTTON_PIN 20

void handler(uint gpio, uint32_t events);

uint32_t millis();
int konst = 0;

uint32_t lastIrgTime = 0;

uint32_t lastIrgTime2 = 0;

int main()
{
    stdio_init_all();
    sleep_ms(2000);
    printf("Starting...\n");
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_init(BUTTON_PIN);
    gpio_pull_up(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_init(21);
    gpio_pull_up(21);
    gpio_set_dir(21, GPIO_IN);

    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_RISE, true, &handler);
    gpio_set_irq_enabled_with_callback(21, GPIO_IRQ_EDGE_RISE, true, &handler);

    while (1)
    {
        if (millis() - lastIrgTime2 >= 1000)
        {
            gpio_put(LED_PIN, !gpio_get(LED_PIN));
            lastIrgTime2 = millis();
        }

        printf("\r%d", konst);

        sleep_ms(100);
    }
    return 0;
}

void handler(uint gpio, uint32_t events)
{
    if ((millis() - lastIrgTime) >= 200)
    {
        if (gpio == 21)
        {
            konst += 1;
            lastIrgTime = millis();
        }
        else if (gpio == BUTTON_PIN)
        {
            konst -= 1;
            lastIrgTime = millis();
        }
    }
}

uint32_t millis()
{
    return to_ms_since_boot(get_absolute_time());
}