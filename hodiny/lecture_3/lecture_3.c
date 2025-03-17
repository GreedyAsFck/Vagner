/*
#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

void fade_();
uint16_t map_value(uint16_t value, uint16_t in_min, uint16_t in_max,
                   uint16_t out_min, uint16_t out_max);

int main()
{
    stdio_init_all();
    sleep_ms(2000);
    printf("Starting...\n");

    uint slice_num = pwm_gpio_to_slice_num(3);
    uint channel = pwm_gpio_to_channel(3);
    gpio_set_function(16, GPIO_FUNC_PWM);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 125);
    pwm_config_set_wrap(&config, 1000);

    pwm_init(slice_num, &config, true);

    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);

    while (1)
    {
        fade_();
    }

    return 0;
}

void fade_()
{

    uint16_t in_min = 0;
    uint16_t in_max = 4095;
    uint16_t out_min = 0;
    uint16_t out_max = 1000;

    static int fade = 0;

    uint16_t value = adc_read();

    uint16_t hodnota = map_value(value, in_min, in_max, out_min, out_max);

    pwm_set_gpio_level(16, hodnota);
}

uint16_t map_value(uint16_t value, uint16_t in_min, uint16_t in_max,
                   uint16_t out_min, uint16_t out_max)
{
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
*/
