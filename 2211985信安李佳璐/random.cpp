#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

std::string generate_random_binary_string(int length) {
    std::string binary_string;
    for (int i = 0; i < length; ++i) {
        binary_string += (rand() % 2) ? '1' : '0'; // 随机生成 '0' 或 '1'
    }
    return binary_string;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // 设置随机种子

    const int num_strings = 8000;
    const int length = 16;
    std::vector<std::string> binary_strings;

    // 生成 8000 个 16 位的随机二进制明文
    for (int i = 0; i < num_strings; ++i) {
        binary_strings.push_back(generate_random_binary_string(length));
    }

    // 将所有结果保存到文件
    std::ofstream outFile("random_ming.txt");
    for (const auto& binary : binary_strings) {
        outFile << binary << std::endl;
    }

    outFile.close();
    return 0;
}
