/*
** EPITECH PROJECT, 2026
** LOGGER
** File description:
** nanotekspice
*/

#ifndef LOGGER
  #define LOGGER
  #include "AComponent.hpp"
#include "IComponent.hpp"
  #include <cstdint>
  #include <fstream>

namespace nts {
class Logger : public AComponent {
public:
  Logger() = default;
  ~Logger() override = default;

  void simulate(std::size_t tick) override {
    if (tick <= _currentTick) return;
    _currentTick = tick;

    Tristate clk = getPinValue(9);
    Tristate inhibit = getPinValue(10);

    bool rising = (_lastClk == False && clk == True);
    if (rising && inhibit == False)
      writeByte();

    _lastClk = clk;
  }

  Tristate compute(std::size_t) override {
    return Undefined;
  }

  void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) override {
    AComponent::setLink(pin, other, otherPin);
  }

private:
  Tristate _lastClk {Undefined};

  void writeByte() {
    std::uint8_t value = 0;

    for (int i = 0; i < 8; ++i) {
      Tristate b = getPinValue(static_cast<std::size_t>(i + 1));
      if (b == True)
        value |= static_cast<std::uint8_t>(1u << i);
    }

    std::ofstream out("./log.bin", std::ios::binary | std::ios::app);
    if (!out) return;
    out.write(reinterpret_cast<const char *>(&value), 1);
  }
};
}

#endif /* LOGGER */
