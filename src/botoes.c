#include "../includes/botoes.h"
#include "../includes/controle-leds.h"
#include "../includes/display.h"
#include <stdio.h>

volatile bool botao_joystick_pressionado = false;
volatile bool exaustor_ligado = false;
volatile float eficiencia_exaustor = 0.8; // Valor inicial da eficiência do exaustor (entre 0 e 1)
uint8_t estilo_borda = 0;

bool debounce(uint gpio) {
    static uint32_t ultimo_tempo = 0;
    uint32_t agora = to_ms_since_boot(get_absolute_time());

    if (agora - ultimo_tempo < 200) { // 200ms de debounce
        printf("Botão ignorado (debounce ativo)\n");
        return false;
    }
    if (!gpio_get(gpio)) { // Verifica se o botão ainda está pressionado
        ultimo_tempo = agora;
        return true;
    }
    
    return false;
}

void interrupcao_botao(uint gpio, uint32_t eventos) {
    if (eventos & GPIO_IRQ_EDGE_FALL) {
        printf("Interrupção acionada no pino %d\n", gpio);
        if (debounce(gpio)) {
            if (gpio == PINO_BOTAO_JOYSTICK) {
                botao_joystick_pressionado = true;
                printf("Botão do joystick pressionado\n");
            } 
            // Controle de eficiência do exaustor com os botões A e B
            else if (gpio == PINO_BOTAO_A) {
                eficiencia_exaustor -= 0.05; // Diminui a eficiência
                if (eficiencia_exaustor < 0.1) {
                    eficiencia_exaustor = 0.1; // Limita o valor mínimo
                }
                printf("Eficiência do exaustor diminuída para: %.2f\n", eficiencia_exaustor);
            } 
            else if (gpio == PINO_BOTAO_B) {
                eficiencia_exaustor += 0.05; // Aumenta a eficiência
                if (eficiencia_exaustor > 1.0) {
                    eficiencia_exaustor = 1.0; // Limita o valor máximo
                }
                printf("Eficiência do exaustor aumentada para: %.2f\n", eficiencia_exaustor);
            }
        }
    }
}

void botoes_init() {
    // Inicializa o botão do joystick
    gpio_init(PINO_BOTAO_JOYSTICK);
    gpio_set_dir(PINO_BOTAO_JOYSTICK, GPIO_IN);
    gpio_pull_up(PINO_BOTAO_JOYSTICK);
    gpio_set_irq_enabled_with_callback(PINO_BOTAO_JOYSTICK, GPIO_IRQ_EDGE_FALL, true, &interrupcao_botao);
    printf("Botão do joystick inicializado no pino %d\n", PINO_BOTAO_JOYSTICK);

    // Inicializa o botão A
    gpio_init(PINO_BOTAO_A);
    gpio_set_dir(PINO_BOTAO_A, GPIO_IN);
    gpio_pull_up(PINO_BOTAO_A);
    gpio_set_irq_enabled_with_callback(PINO_BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &interrupcao_botao);
    printf("Botão A inicializado no pino %d\n", PINO_BOTAO_A);

    // Inicializa o botão B
    gpio_init(PINO_BOTAO_B);
    gpio_set_dir(PINO_BOTAO_B, GPIO_IN);
    gpio_pull_up(PINO_BOTAO_B);
    gpio_set_irq_enabled_with_callback(PINO_BOTAO_B, GPIO_IRQ_EDGE_FALL, true, &interrupcao_botao);
    printf("Botão B inicializado no pino %d\n", PINO_BOTAO_B);
}

bool botao_joystick() {
    if (botao_joystick_pressionado) {
        botao_joystick_pressionado = false;
        // Alterna o estado do exaustor
        exaustor_ligado = !exaustor_ligado;
        printf("Exaustor %s\n", exaustor_ligado ? "Ligado" : "Desligado");

        return exaustor_ligado; // Retorna o estado do exaustor
    }
    return exaustor_ligado; // Retorna o estado atual caso não tenha sido pressionado
}
