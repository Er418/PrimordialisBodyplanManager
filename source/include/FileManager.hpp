#ifndef TEST_FILEMANAGER_HPP
#define TEST_FILEMANAGER_HPP
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

#include "common.hpp"

class FileManager {
public:
    bool FileCopy(const fs::path& src, const fs::path& dest, bool overwrite=true) const;

    bool FileMove(const fs::path& src, const fs::path& dest, bool overwrite=true) const;

    bool FileDelete(const fs::path& path) const;

    void FileGroupCopy(const fs::path& src_dir, const fs::path& dest_dir,
                       const std::vector<std::string>& files, bool overwrite=true) const;

    void FileGroupMove(const fs::path& src_dir, const fs::path& dest_dir,
                       const std::vector<std::string>& files, bool overwrite=true) const;

    void SetLogLevel(int new_level) {
        log_level = new_level;
    }
private:
    int log_level = 2;
};


#endif //TEST_FILEMANAGER_HPP
