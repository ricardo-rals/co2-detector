#include "../includes/co2-controle.h"
#include "../includes/botoes.h"
#include <math.h>

static float volume_ambiente = 0.0; // Valor padrão, será calculado
static float nivel_co2 = 600.0; // Inicia com 600 ppm
static float area_ambiente = 0.0; // Área do ambiente (m²)

// Função para definir as dimensões do ambiente (em metros cúbicos)
void definir_dimensoes(float largura, float comprimento, float altura) {
    area_ambiente = largura * comprimento;  // Área (m²)
    volume_ambiente = area_ambiente * altura; // Volume em m³
}

// Função para calcular o nível de CO2 com base no valor do sensor
float calcular_nivel_co2(uint16_t valor_y, bool exaustor_ligado, float *vazao, float *reducao) {
    // Convertendo valor_y (valor do sensor) para nível de CO2 (ppm)
    float novo_nivel = (valor_y / 4095.0) * 10000; // Converte para ppm
    float incremento = 200.0;
    float co2_externo = 400.0; // ppm do CO2 no ambiente externo

    // Ajuste do nível de CO2 baseado no sensor
    if (valor_y > 3000) {
        if (novo_nivel > nivel_co2) {
            nivel_co2 += incremento;
            if (nivel_co2 > novo_nivel) nivel_co2 = novo_nivel;
        }
    } else if (valor_y < 1000) {
        if (novo_nivel < nivel_co2) {
            nivel_co2 -= incremento;
            if (nivel_co2 < novo_nivel) nivel_co2 = novo_nivel;
        }
    }

    // Lógica do exaustor
    float vs = 0.0, reducao_co2 = 0.0;
    if (exaustor_ligado) {
        // Definir dimensões do ambiente quando o exaustor estiver ligado
        definir_dimensoes(15.0, 5.0, 2.0); // Exemplo de dimensões do ambiente
        int pessoas = 10; // Número de pessoas no ambiente
        float fp = 2.5; // Fator de geração de CO2 por pessoa (L/h)
        float fa = 0.3; // Fator de ventilação (m²)
        float ez = eficiencia_exaustor; // Eficiência do exaustor (valor entre 0 e 1)

        // Cálculo do volume de ar necessário para o exaustor
        float vef1 = pessoas * fp; // Volume de CO2 gerado pelas pessoas (L/h)
        float vef2 = area_ambiente * fa; // Volume de ventilação pela área (L/h)
        float vef = (vef1 > vef2) ? vef1 : vef2; // Escolher o maior valor entre os dois
        vs = vef * ez; // Ajuste: multiplicando pela eficiência do exaustor

        // Cálculo da redução de CO2
        reducao_co2 = (vs * (nivel_co2 - co2_externo)) / volume_ambiente;
        nivel_co2 -= reducao_co2; // Atualiza o nível de CO2 no ambiente

        // Garantir que o nível de CO2 não seja menor que o CO2 externo
       
        if (nivel_co2 < 600.0) {
            nivel_co2 = 600.0; // Limite superior de CO2
        }
    }

    // Retorna os valores calculados (vazão e redução de CO2)
    if (vazao) *vazao = vs;
    if (reducao) *reducao = reducao_co2;

    // Retorna o nível de CO2 atual
    return nivel_co2;
}
