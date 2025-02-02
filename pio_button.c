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

//Declaração de pinos e variáveis a serem utilizadas no código
#define DEBOUNCE_DELAY 200
#define NUM_ROWS 5
#define NUM_COLS 5
#define NUM_BUTTONS 2

#define MATRIX_PIN 7
#define RED_LED 13

const uint A_BUTTON = 5;
const uint B_BUTTON = 6;

volatile int numero_atual = 0;

//Função para inicializar todos os pinos de leds e botões
void init_pins() {
    gpio_init(MATRIX_PIN);
    gpio_set_dir(MATRIX_PIN, GPIO_OUT);
    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, GPIO_OUT); //Os leds precisam ser definidos como GPIO de saída
    gpio_init(A_BUTTON);
    gpio_set_dir(A_BUTTON, GPIO_IN); //Os botões precisam ser definidos como GPIO de entrada
    gpio_init(B_BUTTON);
    gpio_set_dir(B_BUTTON, GPIO_IN);

    gpio_pull_up(A_BUTTON);
    gpio_pull_up(B_BUTTON);
}

//Função que desliga o LED vermelho
void leds_off(){
    gpio_put(RED_LED, 0);
}

//Função que liga o led desejado (na função principal coloquei o vermelho)
void leds_on(uint led) {
    leds_off();
    gpio_put(led, 1);
}

//Declarei os botões e uma variável com o último tempo para poder criar a função de debounce
const uint32_t gpio_button[NUM_BUTTONS] = {A_BUTTON, B_BUTTON};
uint32_t last_time[NUM_BUTTONS] = {0};

//A função de debounce vai analisar CADA UM dos botões e evitar que o botão tenha "trepidação" para não gerar erros de execução
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

//Função de interrupção implementada juntamente com a ação de cada botão, evitando que o botão pressionado continue incrementando ou decrementando os números da matriz
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
 
//função que configura a intensidade das cores da matriz de led
uint32_t matrix_rgb(double r, double g, double b) {
 unsigned char R, G, B;
 R = r * 255;
 G = g * 255;
 B = b * 255;
 return (G << 24) | (R << 16) | (B << 8);
}

//Desenhos para cada número (no código os desenhos estão invertidos para que possam ficar corretos na matriz)
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

//Configura os leds da matriz a serem ligados na placa
void desenho_pio(const double matrix_numeros[NUM_ROWS][NUM_COLS], PIO pio, uint sm, double r, double g, double b) {
    uint32_t valor_led;
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            valor_led = matrix_rgb(r * matrix_numeros[i][j], g * matrix_numeros[i][j], b * matrix_numeros[i][j]);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
    }
}

//Função principal que inicializa pinos e mantém rotinas de execução
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

    //Função de interrupção sendo chamada para cada botão
    gpio_set_irq_enabled_with_callback(A_BUTTON, GPIO_IRQ_EDGE_FALL, true, &irq_button);
    gpio_set_irq_enabled_with_callback(B_BUTTON, GPIO_IRQ_EDGE_FALL, true, &irq_button);

    //Laço de repetição que faz o led vermelho piscar continuamente 5x por segundo além de ligar os leds da matriz de leds com o desenho definido em matrix_numeros
    while(1){
        //Como o led precisa piscar 5x por segundo, são 200ms para fazer a ação de acender e apagar em conjunto, ou seja para acender são 100ms e para apagar são 100ms, totalizando 200ms
        //Assim dividindo 1000ms(1s) por 200ms são 5 vezes
        leds_on(RED_LED);
        sleep_ms(100);
        leds_off();
        sleep_ms(100);

        //Função chama continuamente os desenhos dos números baseados nos números atuais que são incrementados ou decrementados com os botões A ou B
        desenho_pio(matrix_numeros[numero_atual], pio, sm, 0.1, 0.0, 0.1);

        sleep_ms(100);
    }
    return 0;
}
