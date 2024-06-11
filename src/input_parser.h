#include "imports.h"

using std::string;
using std::vector;

class input_parser {
public:
  input_parser(int &arc, char **argv);

  const string &get_cmd_option(const string &option) const;
  bool cmd_option_exists(const string &option) const;

private:
  vector<string> tokens;
};
