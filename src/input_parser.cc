#include "input_parser.h"

input_parser::input_parser(int &argc, char **argv) {
  for (int i = 1; i < argc; ++i) {
    this->tokens.push_back(string(argv[i]));
  }
}

const string &input_parser::get_cmd_option(const string &option) const {
  vector<string>::const_iterator itr;
  itr = std::find(this->tokens.begin(), this->tokens.end(), option);

  if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
    return *itr;
  }

  static const string empty_string{""};
  return empty_string;
}

bool input_parser::cmd_option_exists(const string &option) const {
  return std::find(this->tokens.begin(), this->tokens.end(), option) !=
         this->tokens.end();
}
