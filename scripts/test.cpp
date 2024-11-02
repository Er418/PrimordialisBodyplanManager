#include "../source/includes/SteamManager.hpp"

int main() {
    SteamManager steam;
    auto result = steam.FindGameDir();
    if (!result.has_value()) {
        std::cout << "oops";
    } else {
        std::cout << result.value();
    }
}