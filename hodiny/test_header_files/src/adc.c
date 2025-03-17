#include "adc.h"
#include "hardware/adc.h"

// Configure ADC for potentiometer reading
void init_adc(void)
{
    adc_init();
    adc_gpio_init(POT_PIN);
    adc_select_input(ADC_CHAN);
}
