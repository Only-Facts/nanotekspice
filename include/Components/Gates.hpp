/*
** EPITECH PROJECT, 2026
** GATES
** File description:
** nanotekspice
*/

#ifndef GATES
  #define GATES
  #include "IComponent.hpp"
#include <string>
  #define DEFAULT_OUTPUT 3
  #define SINGLE_OUTPUT 2
  #include "AComponent.hpp"
  #include <functional>

namespace nts {
class GateComponent: public AComponent {
public:
  using LogicOp = std::function<Tristate(Tristate, Tristate)>;

  GateComponent(const std::string &type, LogicOp op, std::size_t outputPin = DEFAULT_OUTPUT) : AComponent(type), _op(std::move(op)), _outputPin(outputPin) {}
  virtual ~GateComponent() = default;

  Tristate runLogic(std::size_t pin) override {
    if (pin != _outputPin) return getPinValue(pin);

    Tristate v1 = getPinValue(1);
    Tristate v2 = (_outputPin == SINGLE_OUTPUT) ? Undefined : getPinValue(2);

    return _op(v1, v2);
  }

private:
  LogicOp _op;
  std::size_t _outputPin;
};

struct Operators {
  static Tristate ntsAnd(Tristate a, Tristate b) {
    if (a == False || b == False) return False;
    if (a == True && b == True) return True;
    return Undefined;
  }
  static Tristate ntsOr(Tristate a, Tristate b) {
    if (a == True || b == True) return True;
    if (a == False && b == False) return False;
    return Undefined;
  }
  static Tristate ntsXor(Tristate a, Tristate b) {
    if (a == Undefined || b == Undefined) return Undefined;
    return (a == b) ? False : True;
  }
  static Tristate ntsNot(Tristate a, Tristate) {
    if (a == True) return False;
    if (a == False) return True;
    return Undefined;
  }
  static Tristate ntsNor(Tristate a, Tristate b) {
    Tristate res = ntsOr(a, b);
    return ntsNot(res, Undefined);
  }
  static Tristate ntsNand(Tristate a, Tristate b) {
    Tristate res = ntsAnd(a, b);
    return ntsNot(res, Undefined);
  }
};
}

#endif /* GATES */
