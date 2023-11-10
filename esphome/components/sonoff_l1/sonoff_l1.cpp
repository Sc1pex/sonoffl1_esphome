#include "sonoff_l1.h"
#include "esphome/core/log.h"
#include <HardwareSerial.h>

namespace esphome {
namespace sonoff_l1 {

static const char *const TAG = "components.l1";

void SonoffL1::write_state(light::LightState *state) {
  // This will be called by the light to get a new state to be written.
  float red, green, blue;
  // use any of the provided current_values methods
  state->current_values_as_rgb(&red, &green, &blue);

  // Convert to 0-255
  int redValue, greenValue, blueValue;
  redValue = floor(red * 255);
  greenValue = floor(green * 255);
  blueValue = floor(blue * 255);

  bool ledState;
  state->current_values_as_binary(&ledState);

  float brightnessPercent;
  state->current_values_as_brightness(&brightnessPercent);

  // Convert to 0-100
  int brightness = floor(brightnessPercent * 100);

  char buffer[140];
  snprintf_P(buffer, sizeof(buffer),
             PSTR("AT+UPDATE=\"sequence\":\"123123\",\"switch\":\"%s\",\"light_type\":1,\"colorR\":%d,\"colorG\":%d,"
                  "\"colorB\":%d,\"bright\":%d,\"mode\":%d"),
             ledState ? "on" : "off", redValue, greenValue, blueValue, brightness, mode);

  if (!ledState) {
    mode += 1;
  }

  Serial.print(buffer);
  Serial.write(0x1B);
  Serial.flush();
  // ESP_LOGD(TAG, "Wrote: %s", buffer);
}

void SonoffL1::setup() { Serial.begin(19200); }

void SonoffL1::loop() {
  char buffer[128];
  int read = Serial.readBytes(buffer, 128);
  char r[128];
  strncpy(r, buffer, read);
  r[read] = 0;
  Serial.printf("Read %d bytes: %s\r\n", read, r);
  // ESP_LOGD(TAG, "Read %d bytes: %s", read, r);
}

void SonoffL1::dump_config() {}

light::LightTraits SonoffL1::get_traits() {
  auto traits = light::LightTraits();
  traits.set_supported_color_modes({light::ColorMode::RGB});

  return traits;
}

}  // namespace sonoff_l1
}  // namespace esphome
