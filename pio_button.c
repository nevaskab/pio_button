#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

//arquivo .pio
#include "pio_button.pio.h"

#define DEBOUNCE_DELAY 200
#define NUM_ROWS 5
#define NUM_COLS 5
#define NUM_BUTTONS 2

#define MATRIX_PIN 7
#define RED_LED 13

const uint A_BUTTON = 5;
const uint B_BUTTON = 6;

volatile int numero_atual = 0;


void init_pins() {
    gpio_init(MATRIX_PIN);
    gpio_set_dir(MATRIX_PIN, GPIO_OUT);
    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);
    gpio_init(A_BUTTON);
    gpio_set_dir(A_BUTTON, GPIO_IN);
    gpio_init(B_BUTTON);
    gpio_set_dir(B_BUTTON, GPIO_IN);

    gpio_pull_up(A_BUTTON);
    gpio_pull_up(B_BUTTON);
}

void leds_off(){
    gpio_put(RED_LED, 0);
}

void leds_on(uint led) {
    leds_off();
    gpio_put(led, 1);
}

const uint32_t gpio_button[NUM_BUTTONS] = {A_BUTTON, B_BUTTON};
uint32_t last_time[NUM_BUTTONS] = {0};

bool debounce(uint gpio) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    int index_button;

    for (index_button = 0; index_button < NUM_BUTTONS; index_button++) {
        if (gpio_button[index_button] == gpio) {
            break;
        }
    }

    if (current_time - last_time[index_button] < DEBOUNCE_DELAY) {
        return false;
    }

    last_time[index_button] = current_time;
    return true;
}

void irq_button(uint gpio, uint32_t events) {
    if(debounce(gpio)){
        if(gpio == A_BUTTON){
            numero_atual = (numero_atual + 1) % 10;
        }
        else if(gpio == B_BUTTON){
            numero_atual = (numero_atual - 1 +10) % 10;
        }
    }
}

uint32_t matrix_rgb(double r, double g, double b) {
 unsigned char R, G, B;
 R = r * 255;
 G = g * 255;
 B = b * 255;
 return (G << 24) | (R << 16) | (B << 8);
}

const double matrix_numeros[10][NUM_ROWS][NUM_COLS] = {
    //número 0
    {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
    },
    //número 1
    {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0
    },
    //número 2
    {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
    },
    //número 3
    {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
    },
    //número 4
    {
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0
    },
    //número 5
    {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
    },
    //número 6
    {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
    },
    //número 7
    {
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 0.0
    },
    //número 8
    {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
    },
    //número 9
    {
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
    },

};

void desenho_pio(const double matrix_numeros[NUM_ROWS][NUM_COLS], PIO pio, uint sm, double r, double g, double b) {
    uint32_t valor_led;
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            valor_led = matrix_rgb(r * matrix_numeros[i][j], g * matrix_numeros[i][j], b * matrix_numeros[i][j]);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
    }
}

int main()
{
    PIO pio = pio0; 
    bool ok;

    ok = set_sys_clock_khz(128000, false);

    stdio_init_all();
    init_pins();

    uint offset = pio_add_program(pio, &pio_button_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_button_program_init(pio, sm, offset, MATRIX_PIN);

    gpio_set_irq_enabled_with_callback(A_BUTTON, GPIO_IRQ_EDGE_FALL, true, &irq_button);
    gpio_set_irq_enabled_with_callback(B_BUTTON, GPIO_IRQ_EDGE_FALL, true, &irq_button);

    while(1){
        leds_on(RED_LED);
        sleep_ms(100);
        leds_off();
        sleep_ms(100);

        desenho_pio(matrix_numeros[numero_atual], pio, sm, 0.0, 0.5, 0.5);

        sleep_ms(100);
    }
    return 0;
}
