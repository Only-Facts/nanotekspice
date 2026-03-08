#include "IComponent.hpp"

nts::Tristate operator!(const nts::Tristate a) {
  if (a == nts::Undefined)
    return nts::Undefined;
  return a == nts::True ? nts::False : nts::True;
}

nts::Tristate operator&&(const nts::Tristate a, const nts::Tristate b) {
  if (a == nts::False || b == nts::False) return nts::False;
  if (a == nts::True && b == nts::True) return nts::True;
  return nts::Undefined;
}

nts::Tristate operator||(const nts::Tristate a, const nts::Tristate b) {
  if (a == nts::True || b == nts::True) return nts::True;
  if (a == nts::False && b == nts::False) return nts::False;
  return nts::Undefined;
}
