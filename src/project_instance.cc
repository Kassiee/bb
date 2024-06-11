#include "project_instance.hh"
#include "util/split.hh"

void project_instance::config(std::vector<part> parts_input) {
  for (part x : parts_input) {
    if (!x.is_valid()) {
      std::cout << "\"" << x.name << "\" is not a valid property name\n";
      continue;
    }
    if (x.name == "cflags" || "cxxflags") {
      std::string v;
      for (auto flag : split(x.value, ',')) {
        v.append(flag + " ");
        properties[x.name] = v;
      }
    } else {
      properties[x.name] = x.value;
    }
  }
}
