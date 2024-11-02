#ifndef TEST_STEAMMANAGER_HPP
#define TEST_STEAMMANAGER_HPP

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <optional>

#include "common.hpp"
#include "FileManager.hpp"
#include "LocalConfigManager.hpp"
#include "GlobalConfigManager.hpp"


class SteamManager {
public:
    SteamManager(LocalConfigManager& local_config_) : local_config(local_config_) {};

    fs::path FindGameDir();
    bool CreateManagerFolder() const;

    bool CreateBackup(const std::vector<std::string>& files);
    bool RestoreBackup(const std::vector<std::string>& files);

    bool MoveFilesToBodyplans(const fs::path& src, const std::vector<std::string>& files);

    std::optional<fs::path> GetGameDir() const {
        return game_dir;
    }

    void SetLocalConfig(LocalConfigManager &local_config_) {
        local_config = local_config_;
    }

    GlobalConfigManager GetGlobalConfig() const {
        return global_config;
    }
    void SaveGlobalConfig() {
        global_config.Write(game_dir.value() / "unskill3d_bodyplan_manager" / "global_config.json");
    }
private:
    std::optional<std::string> GetSteamLocation();
    std::optional<fs::path> GetGameLocationFromSteam();
    std::optional<fs::path> GetGameLocationFromConfig();
    fs::path GetGameLocationManual();

    bool CreateBackupFolder() const;
    bool DeleteBackupFolder() const;

    bool CheckGameDirectory(const fs::path& directory);

    std::optional<fs::path> game_dir;
    int log_level = 2;
    FileManager fm;
    LocalConfigManager& local_config;
    GlobalConfigManager global_config;
};


#endif //TEST_STEAMMANAGER_HPP
