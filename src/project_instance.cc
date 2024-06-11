#include "project_instance.h"
#include "imports.h"
#include "util/remws.h"
#include "util/split.h"

using std::string;
using std::vector;

vector<string> project_instance::get_files(const string &dir) {
  // std::cout << dir << "\n";
  vector<string> files;

  for (const auto &entry :
       std::filesystem::recursive_directory_iterator(std::string(dir))) {
    if (entry.is_regular_file()) {
      string filename = entry.path();

      std::cout << filename << "\n";
    }
  }
  return files;
}

void project_instance::config(std::vector<part> &parts_input) {
  for (part x : parts_input) {
    if (!x.is_valid()) {
      std::cout << "\"" << x.name << "\" is not a valid property name\n";
      continue;
    }

    if (x.name == "cflags" || "cxxflags") {
      std::string v;
      for (auto flag : split(x.value, ',')) {
        v.append(flag);
        properties[x.name] = v;
      }
    } else {
      properties[x.name] = x.value;
    }
  }
}
