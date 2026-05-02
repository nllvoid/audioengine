//
// Created by yevhenii on 02.05.2026.
//
#include <filesystem>
#include <fstream>
#include <vector>

namespace AudioEngine {
    std::vector<std::byte> read_file_data(const std::string &name) {
        const std::filesystem::path input_file_path{name};
        auto length = std::filesystem::file_size(input_file_path);
        if (length == 0) {
            return {};
        }
        std::vector<std::byte> buffer(length);
        std::ifstream input_file(name, std::ios_base::binary);
        input_file.read(reinterpret_cast<char *>(buffer.data()), length);
        input_file.close();
        return buffer;
    }
}
