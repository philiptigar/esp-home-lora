#include "esphome.h"
#include <SPI.h>
#include <LoRa.h>

class LoRaReceiver : public PollingComponent {
public:
  Sensor *sensor = nullptr;

  LoRaReceiver() : PollingComponent(2000) {}  // 2 sec interval

  void setup() override {
    ESP_LOGI("LoRa", "Initializing...");
    LoRa.setPins(D8, D0, D2);
    if (!LoRa.begin(433E6)) {
      ESP_LOGE("LoRa", "LoRa init failed");
    }
  }

  void update() override {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
      String incoming = "";
      while (LoRa.available()) {
        incoming += (char)LoRa.read();
      }
      ESP_LOGI("LoRa", "Received: %s", incoming.c_str());
      try {
        float temp = std::stof(incoming.c_str());
        if (sensor) sensor->publish_state(temp);
      } catch (...) {
        ESP_LOGE("LoRa", "Invalid data");
      }
    }
  }

  void set_sensor(Sensor *s) { sensor = s; }
};
