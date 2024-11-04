#include <vector>

#include "../manager/source/SteamManager.hpp"

const std::vector<std::string> files = {
        "antenna_bug.bod",
        "assassin.bod",
        "boss_baby.bod",
        "boss_centipede.bod",
        "boss_donut.bod",
        "boss_missile.bod",
        "chariot.bod",
        "explosive_star.bod",
        "fire_chomper.bod",
        "fish.bod",
        "fish2.bod",
        "glow_bug.bod",
        "grub.bod",
        "jet_squid.bod",
        "lightning_star.bod",
        "menu_snek.bod",
        "mini_jelly.bod",
        "minion_worm.bod",
        "missile_claw.bod",
        "shield_crab.bod",
        "shockjelly.bod",
        "speedy.bod",
        "target_dummy.bod",
        "tentacle_exploder.bod",
};

int main() {
    LocalConfigManager local_config;
    fs::path current_path = fs::current_path();
    local_config.Read(current_path / "config.json");
    SteamManager gamedir_manager(local_config);
    gamedir_manager.FindGameDir();
    gamedir_manager.CreateBackup(files);
    gamedir_manager.MoveFilesToBodyplans(current_path / "body plans", files);

    local_config.Write(current_path / "config.json");
    gamedir_manager.SaveGlobalConfig();

    std::cout << "\n\nSuccessfully installed " << local_config.GetBodypackName() << std::endl;

    system("pause");
    return 0;
}