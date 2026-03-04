/*
** EPITECH PROJECT, 2026
** COMPONENT4017
** File description:
** nanotekspice
*/

#ifndef COMPONENT4017
  #define COMPONENT4017
  #include "AComponent.hpp"
  #include "IComponent.hpp"

namespace nts {
class C4017 : public AComponent {
public:
  C4017() = default;
  ~C4017() override = default;

  void simulate(std::size_t tick) override {
    if (tick <= _currentTick) return;
    _currentTick = tick;

    Tristate reset = getPinValue(15);
    Tristate clk   = getPinValue(14);
    Tristate inhib = getPinValue(13);

    if (reset == True) {
      _state = 0;
    } else if (reset == Undefined) {
      _state = -1;
    } else {
      bool rising = (_lastClk == False && clk == True);
      bool enabled = (inhib == False);
      if (inhib == Undefined)
        enabled = false;
      if (rising && enabled) {
        if (_state >= 0)
          _state = (_state + 1) % 10;
        else
          _state = -1;
      }
    }
    _lastClk = clk;
  }

  Tristate compute(std::size_t pin) override {
    if (_state < 0) {
      if (isQPin(pin) || pin == 12)
        return Undefined;
      return Undefined;
    }

    if (pin == 12) {
      return (_state <= 4) ? True : False;
    }
    int q = qIndexFromPin(pin);
    if (q == -2)
      return Undefined;
    return (q == _state) ? True : False;
  }

private:
  int _state{-1};
  Tristate _lastClk{Undefined};

  static bool isQPin(std::size_t pin) {
    return pin == 1 || pin == 2 || pin == 3 || pin == 4 || pin == 5 || pin == 6 || pin == 7 || pin == 9 || pin == 10 || pin == 11;
  }

  static int qIndexFromPin(std::size_t pin) {
    switch (pin) {
      case 3: return 0;
      case 2: return 1;
      case 4: return 2;
      case 7: return 3;
      case 10:return 4;
      case 1: return 5;
      case 5: return 6;
      case 6: return 7;
      case 9: return 8;
      case 11:return 9;
      default:return -2;
    }
  }
};
}

#endif
