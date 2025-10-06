#include "lora_receiver.h"

extern Sensor &received_temperature;

static auto my_lora = new LoRaReceiver();

void setup() {
  my_lora->set_sensor(&received_temperature);
  my_lora->setup();
}

void loop() {
  my_lora->update();
}
