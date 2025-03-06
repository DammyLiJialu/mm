#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

std::string generate_random_binary_string(int length) {
    std::string binary_string;
    for (int i = 0; i < length; ++i) {
        binary_string += (rand() % 2) ? '1' : '0'; // ������� '0' �� '1'
    }
    return binary_string;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // �����������

    const int num_strings = 8000;
    const int length = 16;
    std::vector<std::string> binary_strings;

    // ���� 8000 �� 16 λ���������������
    for (int i = 0; i < num_strings; ++i) {
        binary_strings.push_back(generate_random_binary_string(length));
    }

    //// ��ӡǰ 10 �����ɵĶ������ַ���
    //for (int i = 0; i < 10; ++i) {
    //    std::cout << binary_strings[i] << std::endl;
    //}

    // �����н�����浽�ļ�
    std::ofstream outFile("random_binary_strings.txt");
    for (const auto& binary : binary_strings) {
        outFile << binary << std::endl;
    }

    outFile.close();
    return 0;
}
