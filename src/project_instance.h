#include "imports.h"

const std::vector<std::string> valid_options = {
    "project_name", "language",     "src_dir", "bin_dir", "include_dirs",
    "c_compiler",   "cxx_compiler", "cflags",  "cxxflags"};

struct part {
  std::string name;
  std::string value;

  bool is_valid() {
    return std::find(valid_options.begin(), valid_options.end(), name) !=
           valid_options.end();
  }
};

class project_instance {

public:
  std::unordered_map<std::string, std::string> properties;

  std::string operator[](const std::string &name) { return properties[name]; }

  void config(std::vector<part> &parts_input);

  std::vector<std::string> get_files(const std::string &dir);

private:
  std::vector<std::string> file_extensions;
};
