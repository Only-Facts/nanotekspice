/*
** EPITECH PROJECT, 2026
** COMPONENT4094
** File description:
** nanotekspice
*/

#ifndef COMPONENT4094
  #define COMPONENT4094
  #include "AComponent.hpp"
  #include "IComponent.hpp"

namespace nts {
class C4094 : public AComponent {
public:
  C4094() : AComponent("C4094") {}
  ~C4094() override = default;

  void simulate(std::size_t tick) override {
    if (tick <= _currentTick) return;
    _currentTick = tick;
    Tristate data = getPinValue(2);
    Tristate clk  = getPinValue(3);
    Tristate stb  = getPinValue(1);

    if (_lastClk == False && clk == True) {
      for (int i = 7; i >= 1; --i) _shift[i] = _shift[i - 1];
      _shift[0] = data;
    }
    if (_lastStb == False && stb == True) {
      for (int i = 0; i < 8; ++i) _out[i] = _shift[i];
    }
    _lastClk = clk;
    _lastStb = stb;
  }

  Tristate runLogic(std::size_t pin) override {
    if (pin == 9)  return _shift[7];
    if (pin == 10) return invert(_shift[7]);
    Tristate oe = getPinValue(15);
    if (oe != True) return Undefined;
    switch (pin) {
      case 4:  return _out[0];
      case 5:  return _out[1];
      case 6:  return _out[2];
      case 7:  return _out[3];
      case 14: return _out[4];
      case 13: return _out[5];
      case 12: return _out[6];
      case 11: return _out[7];
      default: return Undefined;
    }
  }
private:
  Tristate _shift[8] = {Undefined,Undefined,Undefined,Undefined,Undefined,Undefined,Undefined,Undefined};
  Tristate _out[8]   = {Undefined,Undefined,Undefined,Undefined,Undefined,Undefined,Undefined,Undefined};
  Tristate _lastClk{Undefined};
  Tristate _lastStb{Undefined};

  static Tristate invert(Tristate v) {
    return (v == Undefined) ? Undefined : static_cast<Tristate>(!v);
  }
};
}

#endif
