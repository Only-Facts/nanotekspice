#include "IComponent.hpp"
#include "ComponentFactory.hpp"
#include "Components/Constants.hpp"
#include "Components/ClockComponent.hpp"
#include "Components/InputComponent.hpp"
#include "Components/OutputComponent.hpp"
#include "Components/Gates.hpp"
#include "Components/C4001.hpp"
#include "Components/C4071.hpp"
#include "Components/C4081.hpp"
#include "Components/C4011.hpp"
#include "Components/C4030.hpp"
#include "Components/C4069.hpp"
#include "Errors.hpp"
#include <memory>

namespace nts {
ComponentFactory::ComponentFactory() {
  _builders["input"] = []() { return std::make_unique<InputComponent>(); };
  _builders["output"] = []() { return std::make_unique<OutputComponent>(); };
  _builders["clock"] = []() { return std::make_unique<ClockComponent>(); };
  _builders["true"] = []() { return std::make_unique<ConstantComponent>(Tristate::True); };
  _builders["false"] = []() { return std::make_unique<ConstantComponent>(Tristate::False); };

  _builders["and"] = []() { return std::make_unique<GateComponent>(Operators::ntsAnd); };
  _builders["or"] = []() { return std::make_unique<GateComponent>(Operators::ntsOr); };
  _builders["xor"] = []() { return std::make_unique<GateComponent>(Operators::ntsXor); };
  _builders["not"] = []() { return std::make_unique<GateComponent>(Operators::ntsNot, SINGLE_OUTPUT); };

  _builders["4001"] = []() { return std::make_unique<C4001>(); };
  _builders["4071"] = []() { return std::make_unique<C4071>(); };
  _builders["4081"] = []() { return std::make_unique<C4081>(); };
  _builders["4011"] = []() { return std::make_unique<C4011>(); };
  _builders["4030"] = []() { return std::make_unique<C4030>(); };
  _builders["4069"] = []() { return std::make_unique<C4069>(); };
}

std::unique_ptr<IComponent> ComponentFactory::createComponent(const std::string &type) {
  if (!_builders.contains(type))
    throw NTSError("Unknown component type: " + type);
  return _builders[type]();
}
}
