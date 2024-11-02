#ifndef GLOBALCONFIGMANAGER_HPP
#define GLOBALCONFIGMANAGER_HPP

#include "common.hpp"

class GlobalConfigManager {
public:
    void Read(const fs::path& filepath);
    void Write(const fs::path& filepath);

    std::string GetCurrentBodypack();
    void SetCurrentBodypack(const std::string& name);
private:
    int log_level = 2;
    json config;
};


#endif //GLOBALCONFIGMANAGER_HPP
