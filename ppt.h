#ifndef PPT_H_
#define PPT_H_

#include <cxxabi.h>

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

void consume(std::string& remaining) {
  remaining = std::string(remaining.begin() + 1, remaining.end());
}

void PrettyPrintTypeImpl(std::string remaining, std::string prefix) {
  while (true) {
    char ch = remaining.front();
    if (ch == '\0') {
      std::cout << '\n';
      break;
    }

    switch (ch) {
      case ' ':
      case '\t':
        break;
      case '<':
        prefix += "  ";
        std::cout << '<' << '\n' << prefix;
        break;
      case ',':
        std::cout << ',' << '\n' << prefix;
        break;
      case '>':
        prefix = prefix.substr(0, prefix.size() - 2);
        std::cout << '\n' << prefix << '>';
        break;
      default:
        std::cout << ch;
        break;
    }
    consume(remaining);
  }
}

template <typename T>
void PrettyPrintType() {
  char buf[500] = {'\0'};
  char* result = buf;
  result = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
  std::string remaining(result);
  PrettyPrintTypeImpl(remaining, "");
}

#define PPT(x) PrettyPrintType<decltype(x)>();

#endif  // PPT_H_