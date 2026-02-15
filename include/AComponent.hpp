/*
** EPATECH PROJECT, 2026
** ACOMPONENT
** File description:
** nanotekspice
*/

#ifndef ACOMPONENT
  #define ACOMPONENT
  #include "IComponent.hpp"
  #include <map>

namespace nts {
class AComponent: public IComponent {
protected:
  struct Link {
    IComponent *component;
    std::size_t pin;
  };
  std::map<std::size_t, Link> _links;

  std::map<std::size_t, std::pair<std::size_t, Tristate>> _cache;
  std::size_t _currentTick;

  Tristate getPinValue(std::size_t pin) {
    if (!_links.contains(pin) || _links[pin].component == nullptr) return Undefined;
    return _links[pin].component->compute(_links[pin].pin);
  }

public:
  AComponent() = default;
  virtual ~AComponent() = default;

  AComponent(const AComponent&) = delete;
  AComponent& operator=(const AComponent&) = delete;
  AComponent(AComponent&&) noexcept = default;
  AComponent& operator=(AComponent&&) noexcept = default;

  void setLink(std::size_t pin, IComponent& other, std::size_t otherPin) override {
    _links[pin] = {&other, otherPin};
  }
};
}

#endif /* ACOMPONENT */
