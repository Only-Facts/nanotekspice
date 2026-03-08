/*
** EPATECH PROJECT, 2026
** ACOMPONENT
** File description:
** nanotekspice
*/

#ifndef ACOMPONENT
  #define ACOMPONENT
  #include "IComponent.hpp"
  #include <cstddef>
  #include <map>
  #include <string>

namespace nts {
class AComponent: public IComponent {
protected:
  struct Link {
    IComponent *component;
    std::size_t pin;
  };
  std::map<std::size_t, Link> _links;

  std::map<std::size_t, std::pair<std::size_t, Tristate>> _cache;
  std::size_t _currentTick = 0;

  std::string _type;

  Tristate getPinValue(std::size_t pin) {
    if (!_links.contains(pin) || _links[pin].component == nullptr) return Undefined;
    return _links[pin].component->compute(_links[pin].pin);
  }

public:
  AComponent(const std::string &type) : _currentTick(0), _type(type) {};
  virtual ~AComponent() = default;

  AComponent(const AComponent&) = delete;
  AComponent& operator=(const AComponent&) = delete;
  AComponent(AComponent&&) noexcept = default;
  AComponent& operator=(AComponent&&) noexcept = default;

  std::string getType() const override { return _type; }

  void setLink(std::size_t pin, IComponent& other, std::size_t otherPin) override {
    _links[pin] = {&other, otherPin};
  }

  virtual void simulate(std::size_t tick) override {
    _currentTick = tick;
  }

  Tristate compute(std::size_t pin) override {
    if (_cache.count(pin) && _cache[pin].first == _currentTick) {
      return _cache[pin].second;
    }

    _cache[pin] = {_currentTick, Undefined};

    Tristate result = this->runLogic(pin);

    _cache[pin] = {_currentTick, result};
    return result;
  }
};
}

#endif /* ACOMPONENT */
