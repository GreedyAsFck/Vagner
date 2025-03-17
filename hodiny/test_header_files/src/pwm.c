#include "pwm.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

// Configure LED pin for PWM output with appropriate frequency
void init_pwm(void)
{
    gpio_init(LED_PIN);
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);

    uint sliceNum = pwm_gpio_to_slice_num(LED_PIN);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 125);
    pwm_config_set_wrap(&config, 1000);
    pwm_init(sliceNum, &config, true);

    pwm_set_gpio_level(LED_PIN, 0);
}