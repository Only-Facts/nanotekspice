#ifndef COMPONENT4801
  #define COMPONENT4801
  #include "AComponent.hpp"
  #include "IComponent.hpp"
  #include <array>

namespace nts {

class C4801 : public AComponent {
public:
  C4801() : AComponent("C4801") {}
  ~C4801() override = default;

  void simulate(std::size_t tick) override {
    if (tick <= _currentTick)
      return;
    _currentTick = tick;

    if (getPinValue(18) == False && getPinValue(21) == False) {
      int a = addr();
      if (a < 0)
        return;
      for (int i = 0; i < 8; ++i) {
        Tristate v = readDataInput(i);
        if (v == Undefined)
          v = False;
        mem[a][i] = v;
      }
    }
  }

  Tristate runLogic(std::size_t pin) override {
    int i = dIndex(pin);
    if (i < 0)
      return Undefined;
    if (getPinValue(18) != False)
      return Undefined;
    if (getPinValue(21) != True)
      return Undefined;
    if (getPinValue(20) != False)
      return Undefined;

    int a = addr();
    if (a < 0)
      return Undefined;
    return mem[a][i];
  }

private:
  std::array<std::array<Tristate, 8>, 1024> mem = [] {
    std::array<std::array<Tristate, 8>, 1024> m{};
    for (auto &row : m)
      for (auto &b : row)
        b = False;
    return m;
  }();

  int addr() {
    const std::size_t A[10] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22};
    int v = 0;
    for (int i = 0; i < 10; ++i) {
      Tristate t = getPinValue(A[i]);
      if (t == Undefined)
        return -1;
      if (t == True)
        v |= (1 << i);
    }
    return v;
  }

  Tristate readDataInput(int i) {
    switch (i) {
      case 0: return getPinValue(9);
      case 1: return getPinValue(10);
      case 2: return getPinValue(11);
      case 3: return getPinValue(13);
      case 4: return getPinValue(14);
      case 5: return getPinValue(15);
      case 6: return getPinValue(16);
      case 7: return getPinValue(17);
      default: return Undefined;
    }
  }

  static int dIndex(std::size_t pin) {
    switch (pin) {
      case 9:  return 0;
      case 10: return 1;
      case 11: return 2;
      case 13: return 3;
      case 14: return 4;
      case 15: return 5;
      case 16: return 6;
      case 17: return 7;
      default: return -1;
    }
  }
};
}
#endif
