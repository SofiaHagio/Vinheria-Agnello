#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Wi-Fi e servidor
const char* SSID     = "Wokwi-GUEST";
const char* SENHA    = "";
const char* BROKER   = "54.207.111.227";
const int   PORTA    = 1883;

// Topicos MQTT
const char* TOPICO_TEMP = "/TEF/vinheria001/attrs/t";
const char* TOPICO_UMID = "/TEF/vinheria001/attrs/h";
const char* TOPICO_LUZ  = "/TEF/vinheria001/attrs/l";
const char* TOPICO_CMD  = "/TEF/vinheria001/cmd";

// Pinos
#define DHTPIN 4
#define DHTTYPE DHT22
int ldr         = 34;
int ledVerde    = 25;
int ledAmarelo  = 26;
int ledVermelho = 27;
int buzzer      = 14;
int ledPlaca    = 2;

// Faixas ideais
const int TEMP_MIN = 10;
const int TEMP_MAX = 15;
const int UMID_MIN = 50;
const int UMID_MAX = 70;

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient mqtt(espClient);

unsigned long ultimoEnvio = 0;

// Comandos recebidos
void recebeComando(char* topico, byte* mensagem, unsigned int tamanho) {
  String msg = "";
  for (int i = 0; i < tamanho; i++) msg += (char)mensagem[i];
  Serial.println("Comando recebido: " + msg);

  if (msg == "vinheria001@on|")  digitalWrite(ledPlaca, HIGH);
  if (msg == "vinheria001@off|") digitalWrite(ledPlaca, LOW);
}

// Conexao Wi-Fi e MQTT
void conectar() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conectando ao Wi-Fi...");
    WiFi.begin(SSID, SENHA, 6);
    while (WiFi.status() != WL_CONNECTED) delay(500);
    Serial.println("Wi-Fi conectado!");
  }
  while (!mqtt.connected()) {
    Serial.println("Conectando ao broker MQTT...");
    if (mqtt.connect("vinheria_esp32")) {
      mqtt.subscribe(TOPICO_CMD);
      Serial.println("Conectado!");
    } else {
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPlaca, OUTPUT);

  mqtt.setServer(BROKER, PORTA);
  mqtt.setCallback(recebeComando);
  conectar();
}

void loop() {
  conectar();
  mqtt.loop();

  if (millis() - ultimoEnvio >= 5000) {
    ultimoEnvio = millis();

    // Sensores
    float temp = dht.readTemperature();
    float umid = dht.readHumidity();
    int luz = map(analogRead(ldr), 4095, 0, 0, 100);

    Serial.printf("Temp: %.1f C | Umid: %.0f %% | Luz: %d %%\n", temp, umid, luz);

    // Alertas
    bool tempOK = (temp >= TEMP_MIN && temp <= TEMP_MAX);
    bool umidOK = (umid >= UMID_MIN && umid <= UMID_MAX);

    digitalWrite(ledVerde,    luz <= 30 && tempOK && umidOK);
    digitalWrite(ledAmarelo,  (luz > 30 && luz < 60) || !tempOK);
    digitalWrite(ledVermelho, luz >= 60 || !umidOK);

    if (luz >= 60 || !tempOK || !umidOK) tone(buzzer, 1000);
    else noTone(buzzer);

    // Envio MQTT
    mqtt.publish(TOPICO_TEMP, String(temp, 1).c_str());
    mqtt.publish(TOPICO_UMID, String(umid / 100, 2).c_str());
    mqtt.publish(TOPICO_LUZ,  String(luz).c_str());
  }
}
