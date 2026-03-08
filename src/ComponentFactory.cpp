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
#include "Components/C4008.hpp"
#include "Components/C4069.hpp"
#include "Components/C4013.hpp"
#include "Components/C4017.hpp"
#include "Components/C4040.hpp"
#include "Components/C4094.hpp"
#include "Components/C4512.hpp"
#include "Components/C4514.hpp"
#include "Components/C4801.hpp"
#include "Components/C2716.hpp"
#include "Components/Logger.hpp"
#include "Errors.hpp"
#include <memory>

namespace nts {
ComponentFactory::ComponentFactory() {
  _builders["input"] = []() { return std::make_unique<InputComponent>(); };
  _builders["output"] = []() { return std::make_unique<OutputComponent>(); };
  _builders["clock"] = []() { return std::make_unique<ClockComponent>(); };
  _builders["true"] = []() { return std::make_unique<ConstantComponent>(Tristate::True); };
  _builders["false"] = []() { return std::make_unique<ConstantComponent>(Tristate::False); };

  _builders["and"] = []() { return std::make_unique<GateComponent>("and", Operators::ntsAnd); };
  _builders["or"] = []() { return std::make_unique<GateComponent>("or", Operators::ntsOr); };
  _builders["xor"] = []() { return std::make_unique<GateComponent>("xor", Operators::ntsXor); };
  _builders["not"] = []() { return std::make_unique<GateComponent>("not", Operators::ntsNot, SINGLE_OUTPUT); };
  _builders["nor"] = []() { return std::make_unique<GateComponent>("nor", Operators::ntsNor); };

  _builders["4001"] = []() { return std::make_unique<C4001>(); };
  _builders["4071"] = []() { return std::make_unique<C4071>(); };
  _builders["4081"] = []() { return std::make_unique<C4081>(); };
  _builders["4011"] = []() { return std::make_unique<C4011>(); };
  _builders["4030"] = []() { return std::make_unique<C4030>(); };
  _builders["4069"] = []() { return std::make_unique<C4069>(); };
  _builders["4008"] = []() { return std::make_unique<C4008>(); };
  _builders["4013"] = []() { return std::make_unique<C4013>(); };
  _builders["4017"] = []() { return std::make_unique<C4017>(); };
  _builders["4040"] = []() { return std::make_unique<C4040>(); };
  _builders["4094"] = []() { return std::make_unique<C4094>(); };
  _builders["4512"] = []() { return std::make_unique<C4512>(); };
  _builders["4801"] = []() { return std::make_unique<C4801>(); };
  _builders["4514"] = []() { return std::make_unique<C4514>(); };
  _builders["2716"] = []() { return std::make_unique<C2716>(); };

  _builders["logger"] = []() { return std::make_unique<Logger>(); };
}

std::unique_ptr<IComponent> ComponentFactory::createComponent(const std::string &type) {
  if (!_builders.contains(type))
    throw NTSError("Unknown component type: " + type);
  return _builders[type]();
}
}
