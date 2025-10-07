
#include "lora_receiver.h"

extern Sensor &received_temperature; // Link to the global sensor

static auto my_lora = new LoRaReceiver();

void setup() {
  // Link the sensor pointer
  my_lora->set_sensor(&received_temperature);
  my_lora->setup(); // Call the setup of LoRa
}

void loop() {
  my_lora->update(); // Call update periodically
}
