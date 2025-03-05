#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <bitset>
using namespace std;

#define abs_val(a) {if(a >= 4000) a -= 4000; else a = 4000 - a;}
typedef unsigned short ushort;
typedef unsigned int uint;

const int MAX = 8005;
ushort plaintext[MAX], ciphertext[MAX];
int key51, key53, key52, key54;
ushort tail_key;
uint key;

// SPN S-Box and P-Box
const unsigned short sBox_4[16] = { 0xe, 0x4, 0xd, 0x1, 0x2, 0xf, 0xb, 0x8, 0x3, 0xa, 0x6, 0xc, 0x5, 0x9, 0x0, 0x7 };
const unsigned short inverse_sBox[16] = { 0xe, 0x3, 0x4, 0x8, 0x1, 0xc, 0xa, 0xf, 0x7, 0xd, 0x9, 0x6, 0xb, 0x2, 0x0, 0x5 };
const unsigned short pos[17] = {
    0x0,
    0x8000, 0x4000, 0x2000, 0x1000,
    0x0800, 0x0400, 0x0200, 0x0100,
    0x0080, 0x0040, 0x0020, 0x0010,
    0x0008, 0x0004, 0x0002, 0x0001
};
const unsigned short pBox[17] = {
    0x0,
    0x8000, 0x0800, 0x0080, 0x0008,
    0x4000, 0x0400, 0x0040, 0x0004,
    0x2000, 0x0200, 0x0020, 0x0002,
    0x1000, 0x0100, 0x0010, 0x0001
};
unsigned short sBox_16[65536], spBox[65536];

// Ԥ���� S-Box �� P-Box
void precompute_spBox() {
    for (int i = 0; i < 65536; ++i) {
        sBox_16[i] = (sBox_4[i >> 12] << 12) |
            (sBox_4[(i >> 8) & 0xf] << 8) |
            (sBox_4[(i >> 4) & 0xf] << 4) |
            sBox_4[i & 0xf];

        spBox[i] = 0;
        for (int j = 1; j <= 16; ++j) {
            if (sBox_16[i] & pos[j]) {
                spBox[i] |= pBox[j];
            }
        }
    }
}

// ���������ַ���ת��Ϊ ushort
ushort binaryStringToUInt(const string& binary) {
    ushort result = 0;
    for (char bit : binary) {
        result = (result << 1) | (bit - '0');
    }
    return result;
}

// ���ļ��ж�ȡ���ĺ�����
void read_input(const string& filename) {
    ifstream file(filename);
    string binary;
    for (int i = 1; i <= 8000; ++i) {
        getline(file, binary);
        plaintext[i] = binaryStringToUInt(binary);
        getline(file, binary);
        ciphertext[i] = binaryStringToUInt(binary);
    }
    file.close();
}

// ��� key51 �� key53 ��ֵ
void output_keys() {
    cout << "Key51: " << bitset<4>(key51) << endl
        << "Key53: " << bitset<4>(key53) << endl;
}

// ������Կ L1 �� L2 �����¼���
void analyze_keys(int count13[2][16][16], ushort x[], ushort y[]) {
    ushort u1, u2, u3, u4;
    for (int L1 = 0; L1 < 16; ++L1) {
        for (int L2 = 0; L2 < 16; ++L2) {
            u1 = inverse_sBox[y[0] ^ L1];
            u2 = inverse_sBox[y[1] ^ key52];
            u3 = inverse_sBox[y[2] ^ L2];
            u4 = inverse_sBox[y[3] ^ key54];

            // ���� z �����¼���
            if (!((x[0] ^ x[1] ^ x[3] ^ (u1 >> 3) ^ (u2 >> 3) ^ (u3 >> 3) ^ (u4 >> 3)) & 0x1)) {
                count13[0][L1][L2]++;
            }

            if (!((x[8] ^ x[9] ^ x[11] ^ (u1 >> 1) ^ (u2 >> 1) ^ (u3 >> 1) ^ (u4 >> 1)) & 0x1)) {
                count13[1][L1][L2]++;
            }
        }
    }
}

// ���㲢�������ŵ���Կ L1 �� L2
void find_best_keys(int count13[2][16][16], int& bestL1, int& bestL2) {
    int cnt13[16][16];
    int max_val = -1;

    for (int L1 = 0; L1 < 16; ++L1) {
        for (int L2 = 0; L2 < 16; ++L2) {
            abs_val(count13[0][L1][L2]);
            abs_val(count13[1][L1][L2]);
            cnt13[L1][L2] = count13[0][L1][L2] + count13[1][L1][L2];

            if (cnt13[L1][L2] > max_val) {
                max_val = cnt13[L1][L2];
                bestL1 = L1;
                bestL2 = L2;
            }
        }
    }
}

int main() {
    precompute_spBox();

    // �Ѿ���õ� key52 �� key54
    key52 = 0x6;
    key54 = 0xf;

    read_input("spn_pairs.txt");

    int count13[2][16][16] = { 0 };
    ushort x[13], y[5];

    // �������е����ĺ����Ķ�
    for (int group = 0; group < 8000; ++group) {
        ushort x_init = plaintext[group];
        ushort y_init = ciphertext[group];

        // ��ȡ x �� y ��λ
        for (int pos = 0; pos < 12; ++pos) {
            x[pos] = (x_init >> (15 - pos)) & 0x1;
        }
        for (int pos = 0; pos < 4; ++pos) {
            y[pos] = (y_init >> (12 - 4 * pos)) & 0xf;
        }

        // ���� L1 �� L2 ��Կ
        analyze_keys(count13, x, y);
    }

    // �������ŵ� key51 �� key53
    find_best_keys(count13, key51, key53);

    output_keys();
    return 0;
}
