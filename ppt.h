#ifndef PPT_H_
#define PPT_H_

#include <cxxabi.h>

#include <iostream>
#include <string>

template <typename String = std::string>
void consume(String& remaining) {
  remaining = String(remaining.begin() + 1, remaining.end());
}

template <typename String = std::string>
void PrettyPrintTypeImpl(String remaining, String prefix) {
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
    consume<String>(remaining);
  }
}

template <typename T>
void PrettyPrintType() {
  char buf[1000] = {'\0'};
  char* result = buf;
  int status{0};
  result = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status);

  // 'status' explaination
  // https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.3/a01696.html
  if (status == 0) {
    std::string remaining(result);
    PrettyPrintTypeImpl<std::string>(remaining, "");
  } else {
    std::cerr << "[cxa_demangle error] ";
    if (status == -1) {
      std::cerr << "memory allocation failiure occurred.\n";
    } else if (status == -2) {
      std::cerr << "mangled_name is not a valid name under the C++ ABI "
                   "mangling rules.\n";
    } else if (status == -3) {
      std::cerr << "One of the arguments is invalid.\n";
    } else {
      std::cerr << "Unknown status.\n";
    }
  }
}

#define PPT(x) PrettyPrintType<decltype(x)>();

#endif  // PPT_H_