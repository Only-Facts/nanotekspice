/*
** EPITECH PROJECT, 2026
** COMPONENT4013
** File description:
** nanotekspice
*/

#ifndef COMPONENT4013
  #define COMPONENT4013
  #include "AComponent.hpp"
  #include "IComponent.hpp"

namespace nts {
class C4013: public AComponent {
public:
  C4013() : AComponent("C4013") {}
  ~C4013() override = default;

  void simulate(std::size_t tick) override {
    if (tick <= _currentTick)
      return;
    _currentTick = tick;
    simulateFF(0);
    simulateFF(1);
  }

  Tristate runLogic(std::size_t pin) override {
    switch (pin) {
      case 1:
        return _q[0];
      case 2:
        return inv(_q[0]);
      case 13:
        return _q[1];
      case 12:
        return inv(_q[1]);
      default:
        return Undefined;
    }
  }

private:
  Tristate _q[2] = {Undefined, Undefined};
  Tristate _lastClk[2] = {Undefined, Undefined};

  static Tristate inv(Tristate v) {
    if (v == Undefined)
      return Undefined;
    return static_cast<Tristate>(!v);
  }

  void simulateFF(int idx) {
    std::size_t clkPin = (idx == 0) ? 3  : 11;
    std::size_t rPin   = (idx == 0) ? 4  : 10;
    std::size_t dPin   = (idx == 0) ? 5  : 9;
    std::size_t sPin   = (idx == 0) ? 6  : 8;
    Tristate clk = getPinValue(clkPin);
    Tristate rst = getPinValue(rPin);
    Tristate set = getPinValue(sPin);
    Tristate d   = getPinValue(dPin);

    if (rst == True && set == True) {
      _q[idx] = Undefined;
    } else if (rst == True) {
      _q[idx] = False;
    } else if (set == True) {
      _q[idx] = True;
    } else if (rst == Undefined || set == Undefined) {
      _q[idx] = Undefined;
    } else {
      bool rising = (_lastClk[idx] == False && clk == True);
      if (rising)
        _q[idx] = d;
    }

    _lastClk[idx] = clk;
  }
};
}

#endif
