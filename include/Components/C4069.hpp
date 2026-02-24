/*
** EPITECH PROJECT, 2026
** COMPONENT4069
** File description:
** nanotekspice
*/

#ifndef COMPONENT4069
  #define COMPONENT4069
  #include "AComponent.hpp"
  #include "Gates.hpp"
  #include "IComponent.hpp"
  #include <memory>
  #include <vector>

namespace nts {
class C4069: public AComponent {
public :
  C4069() {
      for (int i = 0; i < 6; i++) {
          _subGates.push_back(std::make_unique<GateComponent>(Operators::ntsNot, SINGLE_OUTPUT));
      }
  }

  void simulate(std::size_t tick) override {
      for (std::unique_ptr<IComponent> &gate : _subGates) gate->simulate(tick);
  }

  void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) override {
      switch (pin) {
        case 1:
          _subGates[0]->setLink(1, other, otherPin);
          break;
        case 3:
          _subGates[0]->setLink(1, other, otherPin);
          break;
        case 5:
          _subGates[1]->setLink(1, other, otherPin);
          break;
        case 9:
          _subGates[1]->setLink(1, other, otherPin);
          break;
        case 11:
          _subGates[2]->setLink(1, other, otherPin);
          break;
        case 13:
          _subGates[3]->setLink(1, other, otherPin);
          break;
      }
  }

  Tristate compute(std::size_t pin) override {
    switch (pin) {
      case 2:
        return _subGates[0]->compute(2);
      case 4:
        return _subGates[1]->compute(2);
      case 6:
        return _subGates[2]->compute(2);
      case 8:
        return _subGates[3]->compute(2);
      case 10:
        return _subGates[4]->compute(2);
      case 12:
        return _subGates[5]->compute(2);
      default:
        return Undefined;
    }
  }

private:
  std::vector<std::unique_ptr<IComponent>> _subGates;
};
}

#endif

