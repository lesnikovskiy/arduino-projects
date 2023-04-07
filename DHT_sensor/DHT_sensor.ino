#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHT_PIN A0
#define DHT_TYPE DHT11

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 4  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT dht(DHT_PIN, DHT_TYPE);

unsigned long lastTimeDataRead = millis();
unsigned long sensorReadingDelay = 1000;

unsigned long lastTimeSerialPrint = millis();
unsigned long serialPrintDelay = 1000;

float prevTemperature = 0.0;
float prevHumidity = 0.0;

void setup() {
  Serial.begin(9600);

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  display.display();
  delay(2000);
}

void loop() {
  unsigned long timeNow = millis();

  float temperature;
  float humidity;

  if (timeNow - lastTimeDataRead >= sensorReadingDelay) {
    lastTimeDataRead += sensorReadingDelay;

    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
  }

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Data are corrupted");
  } else {
    handleSensorData(temperature, humidity);
  }
}

void handleSensorData(float temperature, float humidity) {
  drawSensorData(temperature, humidity);
  logSensorData(temperature, humidity);
}

void drawSensorData(float temperature, float humidity) {
  if (prevTemperature != temperature || prevHumidity != humidity) {
    prevTemperature = temperature;
    prevHumidity = humidity;

    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(WHITE);

    display.setCursor(5, 20);
    display.print("T: ");
    display.print(temperature);

    display.setCursor(5, 50);
    display.print("H: ");
    display.print(humidity);

    display.display();
  }
}

void logSensorData(float temperature, float humidity) {
  unsigned long timeNow = millis();

  if (timeNow - lastTimeSerialPrint >= serialPrintDelay) {
    lastTimeSerialPrint += serialPrintDelay;

    Serial.print("Humidity: ");
    Serial.println(humidity);

    Serial.print("Temperate: ");
    Serial.println(temperature);

    Serial.println("---------------");
  }
}
