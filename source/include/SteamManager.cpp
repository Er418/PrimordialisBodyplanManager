#include "SteamManager.hpp"
#include <windows.h>
#include "../../third_party/vdf_parser.hpp"

std::optional<std::string> SteamManager::GetSteamLocation() {
    HKEY hKey;
    const char* regPath = "Software\\Valve\\Steam";
    const char* valueName = "SteamPath";
    char steamPath[MAX_PATH];
    DWORD bufferSize = sizeof(steamPath);

    // Attempt to open the registry key
    if (RegOpenKeyExA(HKEY_CURRENT_USER, regPath, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        // Attempt to read the SteamPath value
        if (RegQueryValueExA(hKey, valueName, NULL, NULL, (LPBYTE)steamPath, &bufferSize) == ERROR_SUCCESS) {
            RegCloseKey(hKey);
            if (log_level >= 2) {
                std::cout << "Located Steam installation at " << std::string(steamPath) << std::endl;
            }
            return std::string(steamPath);  // Successfully retrieved the path
        }
        RegCloseKey(hKey);
    }

    if (log_level >= 1) {
        std::cout << "Failed to locate Steam installation" << std::endl;
    }
    return std::nullopt;
}

std::optional<fs::path> SteamManager::GetGameLocationFromSteam() {
    std::optional<std::string> result = GetSteamLocation();
    if (!result.has_value()) {
        return std::nullopt;
    }
    std::string steam_dir = result.value();

    if (log_level >= 1) {
        std::cout << "Starting search in Steam files" << std::endl;
    }

    fs::path folder_file = fs::path(steam_dir) / "config" / "libraryfolders.vdf";

    if (fs::exists(folder_file)) {
        if (log_level >= 2) {
            std::cout << "Found /config/libraryfolders.vdf file" << std::endl;
        }
    } else {
        if (log_level >= 1) {
            std::cout << "Couldn't find /config/libraryfolders.vdf file, terminating Steam search" << std::endl;
        }
        return std::nullopt;
    }

    std::ifstream file(folder_file);
    auto root = tyti::vdf::read(file);
    std::string steam_folder;

    for (auto &folder: root.childs) {
        if (log_level >= 2) {
            std::cout << "Checking folder " << folder.second->name << std::endl;
        }
        bool success = false;

        // Going through list of apps in folder
        for (auto &app: folder.second->childs["apps"]->attribs) {
            if (app.first == "3267910") {
                success = true;
            }
        }

        if (success) {
            steam_folder = folder.second->attribs["path"];
            if (log_level >= 2) {
                std::cout << "Found Primordialis Demo in Steam folder " << steam_folder << std::endl;
            }
            break;
        }
    }

    if (steam_folder.empty()) {
        if (log_level >= 1) {
            std::cout << "Game directory not found" << std::endl;
        }
        return std::nullopt;
    }

    fs::path game_path = fs::path(steam_folder) / "steamapps" / "common" / "Primordialis Demo";

    if (CheckGameDirectory(game_path)) {
        return game_path;
    } else {
        if (log_level >= 1) {
            std::cout << "Game directory found, but not valid" << std::endl;
        }
        return std::nullopt;
    }
}

std::optional<fs::path> SteamManager::GetGameLocationFromConfig() {
    std::optional<std::string> game_dir_result = local_config.GetGameDir();
    if (!game_dir_result.has_value()) {
        return std::nullopt;
    }
    if (CheckGameDirectory(game_dir_result.value())) {
        return game_dir_result;
    } else {
        return std::nullopt;
    }
}


fs::path SteamManager::GetGameLocationManual() {
    std::string manual_dir;
    std::cout << "Failed to find valid game directory using Steam, please enter valid game directory:" << std::endl;
    std::getline(std::cin, manual_dir);
    while (!CheckGameDirectory(manual_dir)) {
        std::cout << "Game directory invalid, please enter valid game directory:" << std::endl;
        std::getline(std::cin, manual_dir);
    }
    return manual_dir;
}

fs::path SteamManager::FindGameDir() {
    auto game_location_result = GetGameLocationFromSteam();
    if (game_location_result.has_value()) {
        game_dir = game_location_result.value();

        global_config.Read(game_dir.value() / "unskill3d_bodyplan_manager" / "global_config.json");
        local_config.SetGameDir(game_dir.value().generic_string());

        return game_location_result.value();  // Steam search successful
    }

    game_location_result = GetGameLocationFromConfig();
    if (game_location_result.has_value()) {
        game_dir = game_location_result.value();

        global_config.Read(game_dir.value() / "unskill3d_bodyplan_manager" / "global_config.json");
        local_config.SetGameDir(game_dir.value().generic_string());

        return game_location_result.value();  // Config search successful
    }

    game_location_result = GetGameLocationManual();
    game_dir = game_location_result.value();

    CreateManagerFolder();

    global_config.Read(game_dir.value() / "unskill3d_bodyplan_manager" / "global_config.json");
    local_config.SetGameDir(game_dir.value().generic_string());

    return game_location_result.value();
}

bool SteamManager::CreateManagerFolder() const {
    if (!game_dir.has_value()) {
        std::cout << "Game directory not found, can't create manager folder" << std::endl;
        return false;
    }
    fs::path game_directory = game_dir.value();
    if (!fs::exists(game_directory / "unskill3d_bodyplan_manager")) {
        fs::create_directories(game_directory / "unskill3d_bodyplan_manager");
    }
    return true;
}

bool SteamManager::CreateBackupFolder() const {
    if (!game_dir.has_value()) {
        std::cout << "Game directory not found, can't create manager folder" << std::endl;
        return false;
    }
    CreateManagerFolder();
    fs::path game_directory = game_dir.value();
    if (!fs::exists(game_directory / "unskill3d_bodyplan_manager" / "backup")) {
        fs::create_directories(game_directory / "unskill3d_bodyplan_manager" / "backup");
    }
    return true;
}

bool SteamManager::CheckGameDirectory(const fs::path& directory) {
    return fs::exists(directory / "body plans");
}

bool SteamManager::CreateBackup(const std::vector<std::string>& files) {
    if (!game_dir.has_value()) {
        std::cout << "Game directory not found, can't create manager folder" << std::endl;
        return false;
    }
    fs::path game_directory = game_dir.value();

    if (global_config.GetCurrentBodypack() != "vanilla") {
        if (log_level >= 1) {
            std::cout << "Current bodypack is not vanilla, terminating backup process" << std::endl;
        }
        return false;
    }

    CreateBackupFolder();

    bool all_success = true;

    fs::path backup_folder = game_directory / "unskill3d_bodyplan_manager" / "backup";
    fs::path bodyplan_folder = game_directory / "body plans";

    for (const auto& file : files) {
        fs::path src_path = bodyplan_folder / file;
        fs::path dest_path = backup_folder / file;

        if (fs::exists(src_path)) {
            fm.FileCopy(src_path, dest_path);
        } else {
            if (log_level >= 1) {
                std::cout << "File not found: " << src_path << '\n';
            }
            all_success = false;
        }
    }

    return all_success;
}

bool SteamManager::RestoreBackup(const std::vector<std::string> &files) {
    if (!game_dir.has_value()) {
        std::cout << "Game directory not found, can't create manager folder" << std::endl;
        return false;
    }
    fs::path game_directory = game_dir.value();

    if (global_config.GetCurrentBodypack() == "vanilla") {
        std::cout << "It seems you are currently using vanilla bodypack. " <<
        "Are you sure you want to proceed with backup restoration? (Y/N)" << std::endl;
        char choice;
        std::cin >> choice;
        if (choice != 'Y' && choice != 'y') {
            std::cout << "Exiting without restoring backup.\n";
            return false;
        }
    }

    bool all_success = true;

    fs::path backup_folder = game_directory / "unskill3d_bodyplan_manager" / "backup";
    fs::path bodyplan_folder = game_directory / "body plans";

    if(!fs::exists(backup_folder)) {
        std::cout << "Backup folder not found, terminating backup restoration" << std::endl;
        return false;
    }

    for (const auto& file : files) {
        fs::path src_path = backup_folder / file;
        fs::path dest_path = bodyplan_folder / file;

        if (fs::exists(src_path)) {
            fm.FileCopy(src_path, dest_path);
        } else {
            if (log_level >= 1) {
                std::cout << "File not found: " << src_path << '\n';
            }
            all_success = false;
        }
    }

    global_config.SetCurrentBodypack("vanilla");

    return all_success;
}

bool SteamManager::MoveFilesToBodyplans(const fs::path& src, const std::vector<std::string> &files) {
    if (!game_dir.has_value()) {
        std::cout << "Game directory not found, can't create manager folder" << std::endl;
        return false;
    }
    fs::path game_directory = game_dir.value();

    bool all_success = true;

    fs::path bodyplanFolder = game_directory / "body plans";

    for (const auto& file : files) {
        fs::path srcPath = src / file;
        fs::path destPath = bodyplanFolder / file;

        if (fs::exists(srcPath)) {
            fm.FileCopy(srcPath, destPath);
        } else {
            if (log_level >= 1) {
                std::cout << "File not found: " << srcPath << '\n';
            }
            all_success = false;
        }
    }

    global_config.SetCurrentBodypack(local_config.GetBodypackName());

    return all_success;
}






