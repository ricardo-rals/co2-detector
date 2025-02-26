#ifndef CO2_CONTROLE_H
#define CO2_CONTROLE_H

#include <stdint.h>
#include <stdbool.h>

float calcular_nivel_co2(uint16_t valor_y, bool exaustor_ligado, float *vazao, float *reducao);
void definir_dimensoes(float largura, float comprimento, float altura);

#endif
