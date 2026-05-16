# 🍷 Vinheria Agnello — Sistema de Monitoramento de Luminosidade

> Projeto desenvolvido como parte da disciplina de Edge Computing & Computer Systems.  
> Utiliza Arduino Uno com sensor LDR, sensor DHT11 e display LCD 16x2 para monitorar luminosidade, temperatura e umidade do ambiente de armazenamento de vinhos, acionando alertas visuais e sonoros em tempo real.

---

## 📌 Descrição do projeto

O vinho é sensível a três fatores ambientais principais: **luminosidade**, **temperatura** e **umidade**. A exposição excessiva à luz degrada compostos orgânicos; variações de temperatura causam aromas indesejados; e umidade fora da faixa ideal compromete vedantes e rótulos.

Este sistema monitora continuamente esses três fatores e responde de forma automática, exibindo os valores em um display LCD e acionando LEDs e buzzer conforme os níveis detectados.

> Os valores exibidos no display são a **média de 5 leituras consecutivas**, atualizados a cada **5 segundos**.

---

## Faixas ideais de armazenamento

| Fator | Faixa Ideal | Fonte |
|---|---|---|
| Temperatura | 10°C a 15°C | Alexander Pandell, PhD — UC |
| Umidade | 50% a 70% | Recomendação geral |
| Luminosidade | Ambiente escuro/penumbra | — |

---

## 🔴 Lógica de alertas

### Luminosidade

| Estado | Condição | LED | Buzzer | Display |
|---|---|---|---|---|
| ✅ Adequado | Ambiente escuro | 🟢 Verde | Desligado | — |
| ⚠️ Alerta | Meia luz | 🟡 Amarelo | Desligado | `Ambiente a meia luz` |
| 🚨 Crítico | Muito claro | 🔴 Vermelho | Contínuo | `Ambiente muito claro` |

### Temperatura

| Estado | Condição | LED | Buzzer | Display |
|---|---|---|---|---|
| ✅ OK | Entre 10°C e 15°C | 🟢 Verde | Desligado | `Temperatura OK` + valor |
| ⚠️ Alta | Acima de 15°C | 🟡 Amarelo | Contínuo | `Temp. ALTA` + valor |
| ⚠️ Baixa | Abaixo de 10°C | 🟡 Amarelo | Contínuo | `Temp. BAIXA` + valor |

### Umidade

| Estado | Condição | LED | Buzzer | Display |
|---|---|---|---|---|
| ✅ OK | Entre 50% e 70% | 🟢 Verde | Desligado | `Umidade OK` + valor |
| ⚠️ Alta | Acima de 70% | 🔴 Vermelho | Contínuo | `Umidade ALTA` + valor |
| ⚠️ Baixa | Abaixo de 50% | 🔴 Vermelho | Contínuo | `Umidade BAIXA` + valor |

---

## Primeiro circuito (luminosidade)

![Circuito do projeto no Tinkercad](./circuito-01.png)

> Simulação montada no **Tinkercad**. O LDR lê a luminosidade e envia o sinal analógico à porta `A0` do Arduino, que processa e aciona os componentes conforme os limiares definidos no código.

🔗 [Acessar simulação no Tinkercad](https://www.tinkercad.com/things/iGE2alnjSsO-cp-vinheria-agnello)

[![Assista no YouTube](https://img.shields.io/badge/YouTube-Assistir%20Apresenta%C3%A7%C3%A3o-red?style=for-the-badge&logo=youtube)](https://youtu.be/E_VeabWIuwE?si=LpvlSQirIN8TYRqz)

---

## Segundo circuito (ambiental)

![Circuito do projeto](circuito-02.jpg)

> Simulação montada no **Wokwi** (sensor DHT22 como substituto do DHT11). O LDR lê a luminosidade via porta `A0`; o DHT22 lê temperatura e umidade via pino digital; o LCD 16x2 exibe os valores via comunicação I2C ou paralela.

🔗 [Acessar simulação no Wokwi](https://wokwi.com/projects/463841959926858753)

[![Assista no YouTube](https://img.shields.io/badge/YouTube-Assistir%20Apresenta%C3%A7%C3%A3o-red?style=for-the-badge&logo=youtube)](https://youtu.be/M6Er3k_67Ww?si=wdpfwa03QXsFueZl)

---

## 🛠️ Componentes utilizados

### Hardware

| Componente | Quantidade | Pino no Arduino |
|---|---|---|
| Arduino Uno | 1 | — |
| Sensor LDR (fotoresistor) | 1 | A0 |
| Resistor 10 kΩ | 1 | Divisor de tensão com LDR |
| Sensor DHT11 (ou DHT22) | 1 | D2 |
| Display LCD 16x2 (I2C) | 1 | SDA/SCL (A4/A5) |
| LED Verde (5 mm) | 1 | D5 |
| LED Amarelo (5 mm) | 1 | D6 |
| LED Vermelho (5 mm) | 1 | D7 |
| Resistores 220 Ω | 3 | Um por LED |
| Buzzer Passivo 5V | 1 | D3 |
| Jumpers | ~20 | — |
| Protoboard | 1 | 400 ou 830 pontos |

### Software

- **Arduino IDE** 2.x — [download](https://www.arduino.cc/en/software)
- **Biblioteca DHT sensor library** (Adafruit) — instalável via Library Manager
- **Biblioteca LiquidCrystal_I2C** (se usar LCD com I2C) — instalável via Library Manager

---

## ▶️ Como executar

### **Opção A - Tinkercad**

> Primeiro circuito (luminosidade)
 
1. Acesse [tinkercad.com](https://www.tinkercad.com) e faça login ou crie uma conta gratuita.
2. Clique em "Criar" e selecione "Circuito".
3. Adicione os componentes: Arduino Uno, LDR, resistor 10kΩ, LEDs (verde, amarelo e vermelho), resistores 220Ω e Buzzer.
4. Monte as conexões conforme o esquema em `circuito-01.png`.
5. Clique em "Código" e selecione o modo "Texto".
6. Apague o código padrão e cole o conteúdo do arquivo `circuito-01.ino`.
7. Clique em "Iniciar Simulação".
8. Clique no LDR e arraste o controle de luminosidade para testar os diferentes estados.
   
> Segundo circuito (ambiental)
 
1. Acesse [tinkercad.com](https://www.tinkercad.com) e faça login ou crie uma conta gratuita.
2. Clique em "Criar" e selecione "Circuito".
3. Adicione os componentes: Arduino Uno, LDR, resistor 10kΩ, sensor TMP36 (substituto do DHT11 no Tinkercad), LCD 16x2, LEDs (verde, amarelo e vermelho), resistores 220Ω e Buzzer.
4. Monte as conexões conforme o esquema em `circuito-02.jpg`.
5. Clique em "Código" e selecione o modo "Texto".
6. Apague o código padrão e cole o conteúdo do arquivo `circuito-02.ino`.
7. Clique em "Iniciar Simulação".
8. Interaja com o LDR e com o sensor de temperatura para testar os diferentes estados.

 ---
 
### **Opção B - Wokwi**
 
> Primeiro circuito (luminosidade)
 
1. Acesse [wokwi.com](https://wokwi.com) e faça login ou crie uma conta gratuita.
2. Clique em "New Project" e selecione "Arduino Uno".
3. No painel de componentes (botão "+" à esquerda), adicione: LDR, resistor 10kΩ, LEDs (verde, amarelo e vermelho), resistores 220Ω e Buzzer.
4. Monte as conexões conforme o esquema em `circuito-01.png`.
5. No editor de código, apague o conteúdo padrão e cole o conteúdo do arquivo `circuito-01.ino`.
6. Clique em Play.
7. Clique no LDR e ajuste o controle de luminosidade para testar os diferentes estados.
   
> Segundo circuito (ambiental)
 
1. Acesse [wokwi.com](https://wokwi.com) e faça login ou crie uma conta gratuita.
2. Clique em "New Project" e selecione "Arduino Uno".
3. No painel de componentes (botão "+" à esquerda), adicione: LDR, resistor 10kΩ, DHT22 (substituto do DHT11), LCD 16x2 I2C, LEDs (verde, amarelo e vermelho), resistores 220Ω e Buzzer.
4. Monte as conexões conforme o esquema em `circuito-02.jpg`.
5. No editor de código, apague o conteúdo padrão e cole o conteúdo do arquivo `circuito-02.ino`.
6. Clique em Play.
7. Clique no DHT22 e ajuste temperatura e umidade; clique no LDR para ajustar a luminosidade.

---

### **Opção C - Hardware físico**
 
1. Monte o circuito na protoboard conforme o esquema em `circuito-01.png` (primeiro circuito) ou `circuito-02.jpg` (segundo circuito).
2. Instale as bibliotecas **DHT sensor library** e **LiquidCrystal_I2C** no Arduino IDE via `Sketch > Include Library > Manage Libraries`.
3. Abra o arquivo `circuito-01.ino` (primeiro circuito) ou `circuito-02.ino` (segundo circuito).
4. Selecione a porta correta em `Ferramentas > Porta`.
5. Clique em Upload (Ctrl+U).
6. Abra o Monitor Serial (9600 baud) para acompanhar os valores em tempo real.

---

## ⚙️ Ajuste dos limiares

No arquivo `.ino`, as variáveis abaixo controlam os limites de cada estado. Ajuste conforme o ambiente real:

```cpp
// Luminosidade (valor analógico 0–1023)
int limiteOK     = 880;  // Abaixo → ambiente escuro (LED verde)
int limiteAlerta = 960;  // Entre os dois → meia luz (LED amarelo)
                         // Acima → muito claro (LED vermelho + buzzer)

// Temperatura (°C)
float tempMin = 10.0;
float tempMax = 15.0;

// Umidade (%)
float umidMin = 50.0;
float umidMax = 70.0;
```

Use o Monitor Serial para verificar os valores brutos dos sensores no seu ambiente e calibre conforme necessário.

---

## 🗂️ Estrutura do repositório

```
Vinheria-Agnello/
├── circuito-01       ← Código-fonte do sistema luminosidade (primiero circuito)
├── circuito-02       ← Código-fonte do sistema ambiental (segundo circuito)
├── circuito-01.png   ← Imagem do circuito luminosidade
├── circuito-02.jpg   ← Imagem do circuito ambiental
└── README.md         ← Este arquivo
```

---

## 👩‍💻 Equipe

| Integrante | RM |
|---|---|
| Guilherme Tome Nogueira | 570144 |
| Lucas de Andrade Astorini | 569119 |
| Sabrina Lopes da Silva | 571870 |
| Sofia Satomi Hagio | 569120 |
