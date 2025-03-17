#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
// TODO: Define your pin configuration
// Choose appropriate pins for:
// - LED output (must support PWM)
// - Potentiometer input (must support ADC - GPIO26-29)
// Define appropriate PWM wrap value for brightness control

uint16_t map_value(uint16_t value, uint16_t in_min, uint16_t in_max,
                   uint16_t out_min, uint16_t out_max);

// Timing definitions (in milliseconds)
#define DOT_DURATION 200
#define DASH_DURATION (DOT_DURATION * 3)
#define SYMBOL_SPACE (DOT_DURATION)
#define LETTER_SPACE (DOT_DURATION * 3)
#define WORD_SPACE (DOT_DURATION * 7)
#define MAX_INPUT 100
#define PIN_LED 9
#define POTENCIO_PIN 26

// Morse code lookup table (DO NOT MODIFY)
const char *MORSE_CODE[] = {
    ".-",   // A
    "-...", // B
    "-.-.", // C
    "-..",  // D
    ".",    // E
    "..-.", // F
    "--.",  // G
    "....", // H
    "..",   // I
    ".---", // J
    "-.-",  // K
    ".-..", // L
    "--",   // M
    "-.",   // N
    "---",  // O
    ".--.", // P
    "--.-", // Q
    ".-.",  // R
    "...",  // S
    "-",    // T
    "..-",  // U
    "...-", // V
    ".--",  // W
    "-..-", // X
    "-.--", // Y
    "--.."  // Z
};

// Function declarations
void init_pwm(void);
void init_adc(void);
uint16_t read_brightness(void);
void set_led_brightness(uint16_t brightness);
void display_dot(void);
void display_dash(void);
void display_character(char c);
bool read_line(char *buffer, int max_length);
void clear_input_buffer(void);

int main()
{
    stdio_init_all();
    sleep_ms(2000); // Wait for USB serial to initialize

    init_pwm();
    init_adc();

    printf("Morse Code LED Controller\n");
    printf("Use potentiometer to control LED brightness\n\n");

    char input[MAX_INPUT];

    while (true)
    {
        printf("Enter text to convert to Morse code (max %d chars): ", MAX_INPUT - 1);

        if (read_line(input, MAX_INPUT))
        {
            printf("Converting: %s\n", input);

            for (int i = 0; input[i] != '\0'; i++)
            {
                display_character(input[i]);
            }

            printf("\nConversion complete!\n\n");
        }

        clear_input_buffer(); // Clear any remaining input
        sleep_ms(100);
    }

    return 0;
}

// Configure LED pin for PWM output with appropriate frequency
void init_pwm(void)
{
    gpio_init(PIN_LED);
    gpio_set_function(PIN_LED, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(PIN_LED);
    uint channel = pwm_gpio_to_channel(PIN_LED);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 125);
    pwm_config_set_wrap(&config, 1000);

    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(PIN_LED, 0);
}

// Configure ADC for potentiometer reading
void init_adc(void)
{

    adc_init();
    adc_gpio_init(POTENCIO_PIN);
    adc_select_input(0);
}

// Read ADC value and scale it to PWM range
uint16_t read_brightness(void)
{

    uint16_t in_min = 0;
    uint16_t in_max = 4095;
    uint16_t out_min = 0;
    uint16_t out_max = 1000;

    uint16_t value = adc_read();

    uint16_t hodnota = map_value(value, in_min, in_max, out_min, out_max);

    return hodnota;
}

// Set LED brightness using PWM
void set_led_brightness(uint16_t brightness)
{
    pwm_set_gpio_level(PIN_LED, brightness);
}

void display_dot(void)
{
    set_led_brightness(read_brightness());

    sleep_ms(DOT_DURATION);
    set_led_brightness(0);
    sleep_ms(SYMBOL_SPACE);
}

void display_dash(void)
{

    set_led_brightness(read_brightness());

    sleep_ms(DASH_DURATION);
    set_led_brightness(0);
    sleep_ms(SYMBOL_SPACE);
}

// Handle uppercase letters, lowercase letters, and spaces
void display_character(char c)
{

    // 1. Handle spaces (use WORD_SPACE)
    if (c == ' ')
    {
        sleep_ms(WORD_SPACE);
        return;
    }
    // 2. Convert lowercase letters to uppercase
    if (c >= 'a' && c <= 'z')
    {
        c -= 32;
    }

    // 3. Verify character is a valid letter (A-Z)
    if (c >= 'A' && c <= 'Z')
    {
        const char *pattern = MORSE_CODE[c - 'A'];

        for (int i = 0; pattern[i] != '\0'; i++)
        {
            switch (pattern[i])
            {
            case '.':
                display_dot();
                break;
            case '-':
                display_dash();
                break;
            default:
                break;
            }
        }
        sleep_ms(LETTER_SPACE);
    }
}
// Function to clear input buffer (DO NOT MODIFY)
void clear_input_buffer(void)
{
    while (getchar_timeout_us(0) != PICO_ERROR_TIMEOUT)
    {
        // Clear any remaining characters
    }
}

// Function to read input (DO NOT MODIFY)
bool read_line(char *buffer, int max_length)
{
    int index = 0;
    int c;

    while (index < max_length - 1)
    {
        c = getchar_timeout_us(50000);

        if (c == PICO_ERROR_TIMEOUT)
        {
            if (index == 0)
                continue;
            break;
        }

        if (c == '\r' || c == '\n')
        {
            if (index > 0)
                break;
            continue;
        }

        putchar(c);
        buffer[index++] = (char)c;
    }

    buffer[index] = '\0';
    putchar('\n');
    return index > 0;
}

uint16_t map_value(uint16_t value, uint16_t in_min, uint16_t in_max,
                   uint16_t out_min, uint16_t out_max)
{
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}