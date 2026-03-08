/*
** EPITECH PROJECT, 2026
** COMPONENT4512
** File description:
** nanotekspice
*/

#ifndef COMPONENT4512
  #define COMPONENT4512
  #include "AComponent.hpp"
  #include "IComponent.hpp"

namespace nts {
class C4512 : public AComponent {
public:
  C4512() : AComponent("C4512") {}
  ~C4512() override = default;

  void simulate(std::size_t tick) override
  {
    _currentTick = tick;
  }

  Tristate runLogic(std::size_t pin) override {
    if (pin != 14)
      return Undefined;
    const Tristate disable = getPinValue(15);
    const Tristate inhibit = getPinValue(10);
    if (disable != False)
      return Undefined;
    if (inhibit == True)
      return False;
    if (inhibit == Undefined)
      return Undefined;
    const Tristate a = getPinValue(11);
    const Tristate b = getPinValue(12);
    const Tristate c = getPinValue(13);
    if (a == Undefined || b == Undefined || c == Undefined)
      return Undefined;
    const int idx =
      ((c == True) ? 4 : 0) |
      ((b == True) ? 2 : 0) |
      ((a == True) ? 1 : 0);
    return getPinValue(dataPinFromIndex(idx));
  }

  void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) override {
    AComponent::setLink(pin, other, otherPin);
  }

private:
  static std::size_t dataPinFromIndex(int idx) {
    if (idx >= 0 && idx <= 6)
      return static_cast<std::size_t>(1 + idx);
    return 9;
  }
};
}

#endif
