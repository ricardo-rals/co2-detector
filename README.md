# Simulador de Detecção de Gás CO2 com Controle de Exaustor

Este projeto consiste em um sistema embarcado que simula a detecção de gás CO2 em um ambiente fechado. O sistema utiliza um joystick para simular a leitura dos níveis de CO2, um botão para controlar um exaustor que reduz os níveis de CO2, um LED RGB para indicar o estado do ambiente, um buzzer para alertas sonoros e um display OLED para exibir informações em tempo real.

O projeto foi desenvolvido como parte do curso de Sistemas Embarcados e utiliza conceitos de programação em C, controle de periféricos (ADC, PWM, I2C, GPIO) e integração de hardware e software.

## Funcionalidades Principais

### Simulação de Leitura de CO2
- O eixo Y do joystick simula a leitura dos níveis de CO2.
- O valor é convertido para ppm (partes por milhão) e exibido no display OLED.

### Controle do Exaustor
- O botão do joystick liga e desliga o exaustor.
- Quando ligado, o exaustor reduz os níveis de CO2 no ambiente.

### Indicação Visual com LED RGB
- **Verde**: Nível de CO2 seguro (≤ 1000 ppm).
- **Amarelo**: Nível de CO2 em alerta (1000 ppm < CO2 ≤ 2000 ppm).
- **Vermelho**: Nível de CO2 perigoso (> 2000 ppm).

### Alertas Sonoros com Buzzer
O buzzer é ativado quando:
- O nível de CO2 está perigoso (> 2000 ppm).
- O exaustor está desligado.

### Exibição de Informações no Display OLED
- **Linha 1**: Nível de CO2 em ppm.
- **Linha 2**: Estado do sistema (ACEITAVEL, ALERTA ou PERIGO).
- **Linha 3**: Vazão do exaustor (L/s).
- **Linha 4**: Redução de CO2 (ppm/s).
- **Linha 5**: Estado do exaustor (On/Off).
- **Linha 6**: Eficiência do exaustor (Ez).

## Componentes Utilizados
- **Microcontrolador**: Raspberry Pi Pico (ou similar).
- **Joystick**: Para simular a leitura de CO2 e controlar o exaustor.
- **LED RGB**: Para indicar os níveis de CO2.
- **Buzzer**: Para emitir alertas sonoros.
- **Display OLED**: Para exibir informações em tempo real.
- **Botões**: Para ajustar a eficiência do exaustor.

## Estrutura do Código
O projeto está organizado nos seguintes arquivos:
- `main.c`: Contém a função principal e inicializa os periféricos.
- `botoes.c`: Gerencia o botão do joystick e os botões de ajuste de eficiência.
- `buzzer.c`: Controla o buzzer para emitir alertas sonoros.
- `co2_controle.c`: Calcula os níveis de CO2 e controla o exaustor.
- `controle_leds.c`: Gerencia o LED RGB com base nos níveis de CO2.
- `display.c`: Exibe as informações no display OLED.
- `joystick.c`: Lê o valor do eixo Y do joystick.
- `ssd1306.c`: Biblioteca para controle do display OLED.

## Como Executar o Projeto

## **Instalação**
1. Clone o repositório:
   ```bash
   git clone https://github.com/ricardo-rals/co2-detector.git
   cd co2-detector
   ```

2. Abra o projeto no Visual Studio Code.

3. Configure o SDK do Raspberry Pi Pico W de acordo com a [documentação oficial](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf).

4. Siga as instruções no Visual Studio Code para compilar e carregar o projeto no seu Raspberry Pi Pico.

### Funcionamento
1. Movimente o joystick para simular a leitura de CO2.
2. Pressione o botão do joystick para ligar/desligar o exaustor.
3. Ajuste a eficiência do exaustor usando os botões A e B.
4. Observe as informações no display OLED e os alertas sonoros do buzzer.

## Vídeo de Demonstração
Assista ao vídeo de demonstração do projeto: [Simulador de Detecção de Gás CO2](https://youtu.be/nWVuBp3Eg_Y)

## Relatório completo
[Relatório do Projeto: Simulador de Detecção de Gás CO2](https://docs.google.com/document/d/1T2vYlnPl2az3kbAuUnCv0KYfSd7e1Vl2TWFm-3X83qc/edit?usp=sharing)
