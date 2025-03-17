#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

void init_pwm(void);

#define IN1 2
#define IN2 3

#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "stdlib.h"

#endif

void init_pwm(void)
{
    gpio_init(IN1);
    gpio_init(IN2);
    gpio_set_function(IN1, GPIO_FUNC_PWM);
    gpio_set_function(IN2, GPIO_FUNC_PWM);

    uint sliceNum_IN1 = pwm_gpio_to_slice_num(IN1);
    uint sliceNum_IN2 = pwm_gpio_to_slice_num(IN2);
    pwm_config config_motor = pwm_get_default_config();
    pwm_config_set_clkdiv(&config_motor, 125);
    pwm_config_set_wrap(&config_motor, 1000);
    pwm_init(sliceNum_IN1, &config_motor, true);
    pwm_init(sliceNum_IN2, &config_motor, true);

    pwm_set_gpio_level(IN1, 0);
    pwm_set_gpio_level(IN2, 0);
}