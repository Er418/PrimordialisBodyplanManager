#include "FileManager.hpp"

bool FileManager::FileCopy(const fs::path &src, const fs::path &dest, bool overwrite) const {
    try {
        if (overwrite) {
            if (!FileDelete(dest)) {
                return false;
            }
        }
        fs::copy_file(src, dest, fs::copy_options::overwrite_existing);
        if (log_level >= 2) {
            std::cout << "Copied: " << src << " -> " << dest << '\n';
        }
        return true;
    } catch (const fs::filesystem_error &e) {
        if (log_level >= 1) {
            std::cerr << "Error copying file: " << e.what() << '\n';
        }
        return false;
    }
}

bool FileManager::FileDelete(const fs::path &path) const {
    try {
        if (fs::exists(path)) {
            fs::remove(path);
            if (log_level >= 2) {
                std::cout << "Existing file deleted: " << path << '\n';
            }
        }
        return true;
    } catch (const fs::filesystem_error &e) {
        if (log_level >= 1) {
            std::cerr << "Error deleting file: " << e.what() << '\n';
        }
        return false;
    }
}

bool FileManager::FileMove(const fs::path &src, const fs::path &dest, bool overwrite) const {
    try {
        if (overwrite) {
            if (!FileDelete(dest)) {
                return false;
            }
        }
        fs::rename(src, dest);
        if (log_level >= 2) {
            std::cout << "Moved: " << src << " -> " << dest << '\n';
        }
        return true;
    } catch (const fs::filesystem_error &e) {
        if (log_level >= 1) {
            std::cerr << "Error moving file: " << e.what() << '\n';
        }
        return false;
    }
}

void FileManager::FileGroupCopy(const fs::path &src_dir, const fs::path &dest_dir,
                                const std::vector<std::string> &files, bool overwrite) const {
    for (const auto& file : files) {
        fs::path src_file_path = fs::path(src_dir) / file;
        fs::path dest_file_path = dest_dir / file;

        if (fs::exists(src_file_path)) {
            FileCopy(src_file_path, dest_file_path, overwrite);
        } else {
            std::cout << "File not found: " << src_file_path << '\n';
        }
    }
}

void FileManager::FileGroupMove(const fs::path &src_dir, const fs::path &dest_dir,
                                const std::vector<std::string> &files, bool overwrite) const {
    for (const auto& file : files) {
        fs::path src_file_path = fs::path(src_dir) / file;
        fs::path dest_file_path = dest_dir / file;

        if (fs::exists(src_file_path)) {
            FileCopy(src_file_path, dest_file_path, overwrite);
        } else {
            std::cout << "File not found: " << src_file_path << '\n';
        }
    }
}
