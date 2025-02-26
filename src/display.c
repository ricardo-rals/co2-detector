#include "../includes/display.h"
#include "../includes/controle-leds.h"
#include "../includes/co2-controle.h"
#include "../includes/botoes.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>
#include <math.h>

ssd1306_t display;

void display_init() {
    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(PINO_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PINO_I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PINO_I2C_SDA);
    gpio_pull_up(PINO_I2C_SCL);

    ssd1306_init(&display, LARGURA_DISPLAY, ALTURA_DISPLAY, false, 0x3C, i2c1);
    ssd1306_config(&display);
    ssd1306_fill(&display, false);
    ssd1306_send_data(&display);
}

void display_exibir_valores(uint16_t valor_y, bool exaustor_ligado) {
    float vazao, reducao;
    float nivel_co2 = calcular_nivel_co2(valor_y, exaustor_ligado, &vazao, &reducao);

    definir_cor_led(nivel_co2, exaustor_ligado);

    char *mensagem;
    if (nivel_co2 <= 1000) {
        mensagem = "ACEITAVEL";
    } else if (nivel_co2 > 1000 && nivel_co2 <= 2000) {
        mensagem = "ALERTA";
    } else {
        mensagem = "PERIGO";
    }

    char buffer[64];
    snprintf(buffer, sizeof(buffer), "CO2: %.1f ppm", nivel_co2);
    ssd1306_fill(&display, false);
    ssd1306_draw_string(&display, buffer, 0, 0);
    ssd1306_draw_string(&display, mensagem, 0, 10);

    snprintf(buffer, sizeof(buffer), "Vz: %.1f L/s", vazao);
    ssd1306_draw_string(&display, buffer, 0, 20);

    snprintf(buffer, sizeof(buffer), "Rd: %.1f ppm/s", reducao);
    ssd1306_draw_string(&display, buffer, 0, 30);

    snprintf(buffer, sizeof(buffer), "Ex: %s", exaustor_ligado ? "On" : "Off");
    ssd1306_draw_string(&display, buffer, 0, 40);

        // Exibe a eficiência do exaustor
    snprintf(buffer, sizeof(buffer), "Ez: %.2f", eficiencia_exaustor);
    ssd1306_draw_string(&display, buffer, 0, 50);
    ssd1306_send_data(&display);
}