#include "Parser.hpp"
#include "Errors.hpp"
#include "IComponent.hpp"
#include <fstream>
#include <regex>

namespace nts {
Parser::Parser() : _currentSection(Section::NONE) {}

std::map<std::string, std::unique_ptr<nts::IComponent>> Parser::parseFile(const std::string &filepath) {
  std::ifstream file(filepath);
  if (!file.is_open())
    throw NTSError("Could not open file: " + filepath);

  std::string line;
  _currentSection = Section::NONE;
  _components.clear();

  while (std::getline(file, line)) {
    line = line.substr(0, line.find('#'));
    line = trim(line);
    if (line.empty()) continue;

    if (line.find(".chipsets:") == 0) {
      _currentSection = Section::CHIPSETS;
      continue;
    } else if (line.find(".links:") == 0) {
      _currentSection = Section::LINKS;
      continue;
    }

    if (_currentSection == Section::CHIPSETS) processChipset(line);
    else if (_currentSection == Section::LINKS) processLink(line);
  }
  return std::move(_components);
}

void Parser::processChipset(const std::string &line) {
  std::stringstream ss(line);
  std::string type, name;

  if (!(ss >> type >> name))
    throw NTSError("Invalid chipset syntax: " + line);

  if (_components.contains(name))
    throw NTSError("Component name already exists: " + name);

  _components[name] = _factory.createComponent(type);
}

void Parser::processLink(const std::string &line) {
  std::regex pattern(R"(^([^:\s]+)\s*:\s*(\d+)\s+([^:\s]+)\s*:\s*(\d+)$)");
  std::smatch matches;

  if (std::regex_match(line, matches, pattern)) {
    std::string comp1 = matches[1];
    std::size_t pin1 = std::stoul(matches[2]);
    std::string comp2 = matches[3];
    std::size_t pin2 = std::stoul(matches[4]);

    if (!_components.contains(comp1))
      throw NTSError("Link error: Component '" + comp1 + "' does not exist.");
    if (!_components.contains(comp2))
      throw NTSError("Link error: Component '" + comp2 + "' does not exist.");

    _components[comp1]->setLink(pin1, *_components[comp2], pin2);
    _components[comp2]->setLink(pin2, *_components[comp1], pin1);
  } else {
    throw NTSError("Invalid syntax in .links: " + line);
  }
}

std::string Parser::trim(const std::string &str) const {
  const std::string whitespace = " \t\r\n";

  std::size_t first = str.find_first_not_of(whitespace);
  if (first == std::string::npos) return "";

  std::size_t last = str.find_last_not_of(whitespace);
  return str.substr(first, (last - first + 1));
}
}
