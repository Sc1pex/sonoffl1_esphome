#pragma once

#include "esphome/components/number/number.h"
#include "../ld2410.h"

namespace esphome {
namespace ld2410 {

class MaxDistanceTimeoutNumber : public number::Number, public Parented<LD2410Component> {
 public:
  MaxDistanceTimeoutNumber() = default;

 protected:
  void control(float value) override;
};

}  // namespace ld2410
}  // namespace esphome
