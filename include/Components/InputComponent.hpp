/*
** EPITECH PROJECT, 2026
** INPUTCOMPONENT
** File description:
** nanotekspice
*/

#ifndef INPUTCOMPONENT
  #define INPUTCOMPONENT
  #include "AComponent.hpp"

namespace nts {
class InputComponent: public AComponent {
public:
  InputComponent() : AComponent("input"), _nextValue(Undefined), _value(Undefined) {}
  virtual ~InputComponent() = default;

  void setValue(Tristate v) { _nextValue = v; }

  void simulate(std::size_t tick) override {
    AComponent::simulate(tick);
    _value = _nextValue;
  }

  Tristate runLogic(std::size_t pin) override { 
    if (pin != 1) return Undefined;
    return _value;
  }

protected:
  Tristate _nextValue;
  Tristate _value;
};
}

#endif /* INPUTCOMPONENT */
