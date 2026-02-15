/*
** EPITECH PROJECT, 2026
** CORE
** File description:
** nanotekspice
*/


#ifndef CORE
  #define CORE
  #define SUCCESS 0
  #define HELP 2026
  #define ERROR 84
  #define FAIL 1
  #include "IComponent.hpp"
  #include <map>
  #include <string>
  #include <memory>
  #include <atomic>

namespace nts {
class Core {
public:
  Core();
  ~Core() = default;

  Core(const Core&) = delete;
  Core& operator=(const Core&) = delete;
  Core(Core&&) noexcept = default;
  Core& operator=(Core&&) noexcept = default;

  void setup(const std::string &filepath);
  void run();

private:
  void simulate();
  void display() const;
  void loop();
  void setInputValue(const std::string &name, nts::Tristate value);

  std::size_t _tick;
  std::map<std::string, std::unique_ptr<nts::IComponent>> _components;

  std::map<std::string, nts::IComponent*> _inputs;
  std::map<std::string, nts::IComponent*> _outputs;

  static std::atomic<bool> _stopLoop;
  static void signalHandler(int signum);
};
}

#endif /* CORE */
