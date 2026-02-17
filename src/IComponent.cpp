#include "IComponent.hpp"

nts::Tristate operator!(const nts::Tristate a) {
  if (a == nts::Undefined)
    return nts::Undefined;
  return a == nts::True ? nts::False : nts::True;
}

nts::Tristate operator&&(const nts::Tristate a, const nts::Tristate b) {
  if (a == nts::Undefined || b == nts::Undefined)
    return nts::Undefined;
  return a == nts::True && b == nts::True ? nts::True : nts::False;
}

nts::Tristate operator||(const nts::Tristate a, const nts::Tristate b) {
  if (a == nts::Undefined || b == nts::Undefined)
    return nts::Undefined;
  return a == nts::True || b == nts::True ? nts::True : nts::False;
}
