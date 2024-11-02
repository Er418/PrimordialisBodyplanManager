#ifndef LOCALCONFIGMANAGER_HPP
#define LOCALCONFIGMANAGER_HPP

#include <iostream>
#include <optional>

#include "common.hpp"


class LocalConfigManager {
public:
    void Read(const fs::path& filepath);
    void Write(const fs::path& filepath);

    std::string GetBodypackName();

    std::optional<std::string> GetGameDir();
    void SetGameDir(const std::string& path);
private:
    int log_level = 2;
    json config;
};


#endif //LOCALCONFIGMANAGER_HPP
