/*
** EPITECH PROJECT, 2026
** CLOCKCOMPONENT
** File description:
** nanotekspice
*/

#ifndef CLOCKCOMPONENT
  #define CLOCKCOMPONENT
  #include "IComponent.hpp"
#include "InputComponent.hpp"

namespace nts {
class ClockComponent: public InputComponent {
public:
  void simulate(std::size_t tick) override {
    if (tick <= _currentTick) return;
    _currentTick = tick;

    if (_nextValue != Undefined) {
      _value = _nextValue;
      _nextValue = Undefined;
    } else {
      if (_value == True) _value = False;
      else if (_value == False) _value = True;
    }
  }

  nts::Tristate compute(std::size_t pin) override {
    if (pin != 1) return Undefined;
    return _value;
  }
};
}

#endif /* CLOCKCOMPONENT */
