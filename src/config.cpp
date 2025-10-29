#include <string>
#include <filesystem>
#include "config.h"

using namespace std;

string get_config_dir() {
    return filesystem::current_path().string() + "/config";
}
