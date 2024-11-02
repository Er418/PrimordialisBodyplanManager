#include "../manager/source/SteamManager.hpp"

int main() {
    LocalConfigManager local_config;
    SteamManager steam(local_config);
    auto result = steam.FindGameDir();
    std::cout << result;
}