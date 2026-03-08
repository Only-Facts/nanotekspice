#ifndef COMPONENT4514
  #define COMPONENT4514

  #include "AComponent.hpp"
  #include "IComponent.hpp"

namespace nts {

class C4514 : public AComponent {
public:
  C4514() : AComponent("C4514") {}
  ~C4514() override = default;

  void simulate(std::size_t tick) override {
    if (tick <= _currentTick)
      return;
    _currentTick = tick;
    Tristate strobe = getPinValue(1);
    if (_lastStrobe == True && strobe == False)
      _latched = currentIndex();
    if (strobe == Undefined)
      _latched = -1;
    _lastStrobe = strobe;
  }

  Tristate runLogic(std::size_t pin) override {
    const int out = outIndexFromPin(pin);
   if (out == -1)
      return Undefined;
    Tristate inhibit = getPinValue(23);
    if (inhibit == True)
      return False;
    if (inhibit == Undefined)
      return Undefined;
    Tristate strobe = getPinValue(1);
    int selected = -1;
    if (strobe == True)
      selected = currentIndex();
    else if (strobe == False)
      selected = _latched;
    else
      return Undefined;

    if (selected < 0)
      return Undefined;

    return (out == selected) ? True : False;
  }

  void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) override {
    AComponent::setLink(pin, other, otherPin);
  }

private:
  int _latched{-1};
  Tristate _lastStrobe{Undefined};

  int currentIndex() {
    Tristate a = getPinValue(2);
    Tristate b = getPinValue(3);
    Tristate c = getPinValue(21);
    Tristate d = getPinValue(22);

    if (a == Undefined || b == Undefined || c == Undefined || d == Undefined)
      return -1;

    return ((d == True) ? 8 : 0) |
           ((c == True) ? 4 : 0) |
           ((b == True) ? 2 : 0) |
           ((a == True) ? 1 : 0);
  }

  static int outIndexFromPin(std::size_t pin) {
    switch (pin) {
      case 11: return 0;
      case 9: return 1;
      case 10: return 2;
      case 8: return 3;
      case 7: return 4;
      case 6: return 5;
      case 5: return 6;
      case 4: return 7;
      case 18: return 8;
      case 17: return 9;
      case 20: return 10;
      case 19: return 11;
      case 14: return 12;
      case 13: return 13;
      case 16: return 14;
      case 15: return 15;
      default: return -1;
    }
  }
};

}

#endif
