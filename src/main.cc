#include "imports.h"
#include "input_parser.h"
#include "project_instance.h"
#include "util/split.h"

using std::cout;
using std::string;
using std::vector;

namespace fs = std::filesystem;

// vector<string> get_files(const std::string &_dir) {
//   vector<string> files;
//   for (const auto &entry : fs::recursive_directory_iterator(_dir)) {
//     if (entry.is_regular_file()) {
//       string filename = entry.path().string();
//
//       if (std::any_of(extensions.begin(), extensions.end(),
//                       [&](const string &ext) {
//                         return filename.size() > ext.size() &&
//                                filename.compare(filename.size() - ext.size(),
//                                                 ext.size(), ext) == 0;
//                       })) {
//         files.push_back(filename);
//       }
//     }
//   }
//
//   return files;
// }

int main(int argc, char **argv) {
  input_parser input(argc, argv);
  if (input.cmd_option_exists("-h")) {
    cout << "No help here!\n";
  }
  string config_file = input.get_cmd_option("--config");
  if (config_file.empty()) {
    config_file = "default.bbuild";
  }

  if (!std::filesystem::exists(config_file)) {
    cout << config_file << " does not exist\n";
    if (!std::filesystem::exists("default.bbuild")) {
      cout
          << "Tried falling back to default.bbuild, but file does not exist.\n";
      return 1;
    }
  }

  std::ifstream c_file(config_file);
  vector<part> cfg;

  if (c_file.is_open()) {
    string line;

    while (getline(c_file, line)) {
      line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
      if (line.at(0) == '#' || line.empty())
        continue;

      auto delimites_pos = line.find("=");
      string name = line.substr(0, delimites_pos);
      string value = line.substr(delimites_pos + 1);
      cfg.push_back(part{.name = name, .value = value});
    }
  }

  project_instance project;
  project.config(cfg);
  project.get_files(project.properties["src_dir"]);
}
