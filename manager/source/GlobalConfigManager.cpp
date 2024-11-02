#include "GlobalConfigManager.hpp"
#include <fstream>

void  GlobalConfigManager::Read(const fs::path& filepath) {
    if (fs::exists(filepath)) {
        std::ifstream fin(filepath);
        config = json::parse(fin);
        fin.close();
    }
}

void GlobalConfigManager::Write(const fs::path& filepath) {
    std::ofstream fout(filepath);
    fout << config.dump();
    fout.close();
}

std::string GlobalConfigManager::GetCurrentBodypack() {
    if (config.contains("current_bodypack")) {
        return config["current_bodypack"];
    }
    return "vanilla";
}

void GlobalConfigManager::SetCurrentBodypack(const std::string &name) {
    config["current_bodypack"] = name;
}
