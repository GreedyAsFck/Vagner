#include <stdio.h>
#include "pico/stdlib.h"
#include "adc.h"
#include "pwm.h"

// Timing definitions (in milliseconds)
#define DOT_DURATION 200
#define DASH_DURATION (DOT_DURATION * 3)
#define SYMBOL_SPACE (DOT_DURATION)
#define LETTER_SPACE (DOT_DURATION * 3)
#define WORD_SPACE (DOT_DURATION * 7)
#define MAX_INPUT 100

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

uint16_t read_brightness(void);
void set_led_brightness(uint16_t brightness);
void display_dot(void);
void display_dash(void);
void display_character(char c);
bool read_line(char *buffer, int max_length);
void clear_input_buffer(void);
uint16_t map_value(uint16_t value, uint16_t in_min, uint16_t in_max,
                   uint16_t out_min, uint16_t out_max);

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

// Read ADC value and scale it to PWM range
uint16_t read_brightness(void)
{
    return map_value(adc_read(), 0, 4095, 0, 1000);
}

// Set LED brightness using PWM
void set_led_brightness(uint16_t brightness)
{
    pwm_set_gpio_level(LED_PIN, brightness);
}

void display_dot(void)
{
    set_led_brightness(read_brightness());
    sleep_ms(DOT_DURATION);
    set_led_brightness(0);
    sleep_ms(SYMBOL_SPACE);
}

// TODO: Implement Morse code dash
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
    // Your implementation here:
    // 1. Handle spaces (use WORD_SPACE)
    if (c == ' ')
    {
        sleep_ms(WORD_SPACE);
        return;
    }
    // 2. Convert lowercase letters to uppercase
    if (c >= 'a' && c <= 'z')
    {
        c -= 'a' - 'A';
    }
    // 3. Verify character is a valid letter (A-Z)
    if (c >= 'A' && c <= 'Z')
    {
        const char *pattern = MORSE_CODE[c - 'A'];
        for (int i = 0; pattern[i] != '\0'; i++)
        {
            if (pattern[i] == '.')
                display_dot();
            else
                display_dash();
        }
    }
    sleep_ms(LETTER_SPACE);
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