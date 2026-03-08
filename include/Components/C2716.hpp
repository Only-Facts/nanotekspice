/*
** EPITECH PROJECT, 2026
** COMPONENT2716
** File description:
** nanotekspice
*/

#ifndef COMPONENT2716
  #define COMPONENT2716
  #include "AComponent.hpp"
  #include "IComponent.hpp"
  #include <array>
  #include <cstdint>
  #include <fstream>
#include <string>

namespace nts {
class C2716 : public AComponent {
public:
  C2716() : AComponent("C2716") {
    for (auto &b : rom) b = 0;
    std::ifstream in("./rom.bin", std::ios::binary);
    if (!in) return;
    in.read(reinterpret_cast<char *>(rom.data()), static_cast<std::streamsize>(rom.size()));
  }

  ~C2716() override = default;

  void simulate(std::size_t tick) override {
    _currentTick = tick;
  }

  Tristate runLogic(std::size_t pin) override {
    int bit = dIndex(pin);
    if (bit < 0) return Undefined;
    if (getPinValue(19) != False) return Undefined;
    if (getPinValue(21) != False) return Undefined;
    int a = addr();
    if (a < 0) return Undefined;
    std::uint8_t v = rom[static_cast<std::size_t>(a)];
    return ((v >> bit) & 1) ? True : False;
  }

  void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) override {
    AComponent::setLink(pin, other, otherPin);
  }

private:
  std::array<std::uint8_t, 2048> rom{};

  int addr() {
    const std::size_t A[11] = {9,8,7,6,5,4,3,2,23,22,20};
    int v = 0;
    for (int i = 0; i < 11; ++i) {
      Tristate t = getPinValue(A[i]);
      if (t == Undefined) return -1;
      if (t == True) v |= (1 << i);
    }
    return v;
  }

  static int dIndex(std::size_t pin) {
    switch (pin) {
      case 10: return 0;
      case 11: return 1;
      case 12: return 2;
      case 14: return 3;
      case 15: return 4;
      case 16: return 5;
      case 17: return 6;
      case 18: return 7;
      default: return -1;
    }
  }
};
}

#endif
