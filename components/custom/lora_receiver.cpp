#ifndef LORA_RECEIVER_H
#define LORA_RECEIVER_H

#include "esphome.h"
#include <SPI.h>
#include <LoRa.h>

class LoRaReceiver : public PollingComponent {
public:
  Sensor *sensor = nullptr;  // Pointer to the global sensor
  
  LoRaReceiver() : PollingComponent(2000) {} // 2 seconds interval

  void setup() override {
    ESP_LOGI("LoRa", "Initializing...");
    LoRa.setPins(D8, D0, D2);  // CS, RST, DIO0 (IRQ)
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
      
      // Parse the incoming string to float
      try {
        float temp = std::stof(incoming.c_str());
        publish_state(temp); // Call to publish the parsed temperature
      } catch (...) {
        ESP_LOGE("LoRa", "Invalid data");
      }
    }
  }

  void set_sensor(Sensor *s) { sensor = s; } // linking the global sensor

  void publish_state(float temp) {
    if (sensor != nullptr) {
      sensor->publish_state(temp);
    }
  }
};

#endif  // LORA_RECEIVER_H
