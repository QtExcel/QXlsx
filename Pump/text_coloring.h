#pragma once
#include <cstdlib>
#include <sstream>

namespace coloring {

  enum class Color {
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    WHITE = 7,
    DEFAULT = 9
  };

  namespace {
    char textcolor[] = {0x1b, '[', '1', ';', '3'};
    std::string getColorCode(Color c) {
      std::stringstream ss;
      ss << textcolor << static_cast<int>(c) << "m";
      return ss.str();
    }
  }  // namespace


  std::string coloringText(std::string str, Color c) {
    std::stringstream ss;
    ss << getColorCode(c) << str << getColorCode(Color::DEFAULT);
    return ss.str();
  }

}
