#include "LocalConfigManager.hpp"
#include <fstream>

void  LocalConfigManager::Read(const fs::path& filepath) {
    if (fs::exists(filepath)) {
        std::ifstream fin(filepath);
        config = json::parse(fin);
        fin.close();
    }
}

void LocalConfigManager::Write(const fs::path& filepath) {
    std::ofstream fout(filepath);
    if (!config.contains("bodypack_name")) {
        config["bodypack_name"] = "unnamed_bodypack";
    }
    fout << config.dump();
    fout.close();
}

std::string LocalConfigManager::GetBodypackName() {
    if (config.contains("bodypack_name")) {
        return config["bodypack_name"];
    }
    return "unnamed_bodypack";
}

std::optional<std::string> LocalConfigManager::GetGameDir() {
    if (config.contains("game_dir")) {
        return config["game_dir"];
    }
    return std::nullopt;
}

void LocalConfigManager::SetGameDir(const std::string &path) {
    config["game_dir"] = path;
}
