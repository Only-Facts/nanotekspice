/*
** EPITECH PROJECT, 2026
** OUTPUTCOMPONENT
** File description:
** nanotekspice
*/

#ifndef OUTPUTCOMPONENT
  #define OUTPUTCOMPONENT
  #include "AComponent.hpp"
#include "IComponent.hpp"
  #include <string>

namespace nts {
class OutputComponent: public AComponent {
public:
  OutputComponent() : AComponent("output") {}

  Tristate runLogic(std::size_t pin) override {
    if (pin != 1) return Undefined;
    return getPinValue(1);
  }
};
}

#endif /* OUTPUTCOMPONENT */
