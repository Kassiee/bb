#include "imports.h"

class input_parser {
public:
  input_parser(int &arc, char **argv);

  const std::string &get_cmd_option(const std::string &option) const;
  bool cmd_option_exists(const std::string &option) const;

private:
  std::vector<std::string> tokens;
};
