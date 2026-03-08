/*
** EPITECH PROJECT, 2026
** CLOCKCOMPONENT
** File description:
** nanotekspice
*/

#ifndef CLOCKCOMPONENT
  #define CLOCKCOMPONENT
  #include "Components/InputComponent.hpp"

namespace nts {
class ClockComponent: public InputComponent {
public:
  ClockComponent() : InputComponent() {
    _type = "clock";
  }

  void simulate(std::size_t tick) override {
    Tristate old = _value;

    InputComponent::simulate(tick);

    if (_value == old && tick > 0) {
      if (_value == True) _value = False;
      else if (_value == False) _value = True;
    }
  }
};
}

#endif /* CLOCKCOMPONENT */
