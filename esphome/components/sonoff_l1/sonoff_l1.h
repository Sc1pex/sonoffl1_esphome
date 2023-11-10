#pragma once

#include <WString.h>
#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"
#include "esphome/components/light/light_state.h"
#include "esphome/components/light/light_traits.h"

namespace esphome {
namespace sonoff_l1 {

class SonoffL1 : public light::LightOutput, public Component {
 public:
  // LightOutput methods
  light::LightTraits get_traits() override;
  void setup_state(light::LightState *state) override { this->light_state = state; }
  void write_state(light::LightState *state) override;

  // Component methods
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return esphome::setup_priority::DATA; }

 protected:
  light::LightState *light_state{nullptr};
  char rbuff[1024];
  char wbuff[1024];
  int mode = 0;
};

}  // namespace sonoff_l1
}  // namespace esphome
