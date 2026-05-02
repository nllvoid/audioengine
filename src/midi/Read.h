//
// Created by yevhenii on 01.05.2026.
//
#include <filesystem>

#ifndef READ_H
#define READ_H

namespace AudioEngine {
    std::vector<std::byte> read_file_data(const std::string &name);
}

#endif //READ_H
