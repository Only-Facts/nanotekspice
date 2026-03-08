/*
** EPITECH PROJECT, 2026
** COMPONENT4040
** File description:
** nanotekspice
*/

#ifndef COMPONENT4040
  #define COMPONENT4040
  #include "AComponent.hpp"
  #include "IComponent.hpp"

namespace nts {
class C4040 : public AComponent {
public:
  C4040() : AComponent("C4040") {}
  ~C4040() override = default;

  void simulate(std::size_t tick) override {
    if (tick <= _currentTick) return;
    _currentTick = tick;
    Tristate reset = getPinValue(11);
    Tristate clk   = getPinValue(10);
    if (reset == True) {
      _value = 0;
    } else if (reset == Undefined) {
      _value = -1;
    } else {
      bool rising = (_lastClk == False && clk == True);
      if (rising) {
        if (_value >= 0) _value = (_value + 1) & 0xFFF;
        else _value = -1;
      }
    }
    _lastClk = clk;
  }

  Tristate runLogic(std::size_t pin) override {
    int bit = bitFromPin(pin);
    if (bit == -1) return Undefined;
    if (_value < 0) return Undefined;
    return ((_value >> bit) & 1) ? True : False;
  }

private:
  int _value{-1};
  Tristate _lastClk{Undefined};

  static int bitFromPin(std::size_t pin) {
    switch (pin) {
      case 9:  return 0;
      case 7:  return 1;
      case 6:  return 2;
      case 5:  return 3;
      case 3:  return 4;
      case 2:  return 5;
      case 4:  return 6;
      case 13: return 7;
      case 12: return 8;
      case 14: return 9;
      case 15: return 10;
      case 1:  return 11;
      default: return -1;
    }
  }
};
}

#endif
