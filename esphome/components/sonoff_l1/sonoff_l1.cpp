#include "sonoff_l1.h"
#include "esphome/core/log.h"
#include <HardwareSerial.h>

namespace esphome {
namespace sonoff_l1 {

static const char *const TAG = "components.l1";

void SonoffL1::write_state(light::LightState *state) {
  String print = "AT+UPDATE=\"sequence\":588226226,\"switch\":on,\"light_type\":1,\"colorR\":255\"colorG\":"
                 "20\"colorB\":100,\"bright\":100,\"mode\":1";

  Serial.printf("%s", print.c_str());
  Serial.write(0x1b);
  Serial.flush();
  ESP_LOGD(TAG, "Wrote %s", print);

  String recv = Serial.readStringUntil(0x1b);
  ESP_LOGD(TAG, "Recv: %s", recv);
}

void SonoffL1::setup() { Serial.begin(19200); }

void SonoffL1::loop() {}

void SonoffL1::dump_config() {}

light::LightTraits SonoffL1::get_traits() {
  auto traits = light::LightTraits();
  traits.set_supported_color_modes({light::ColorMode::RGB});

  return traits;
}

}  // namespace sonoff_l1
}  // namespace esphome
