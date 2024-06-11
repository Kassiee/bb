#include "remws.h"

std::string remove_space(std::string input) {
  std::string newword;
  for (int i = 0; i < input.length(); ++i) {
    if (input[i] != ' ') {
      newword += input[i];
    }
  }

  return newword;
}
