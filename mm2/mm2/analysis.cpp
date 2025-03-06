#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>   // 引入 abs 函数
using namespace std;

int S[16] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 };
int x[16] = {}; // 明文
int y[16] = {}; // 密文
int Count[16][16] = {}; // 计数器

// 十进制数转换为指定位数的二进制数
void DecimalToBinary(int decimal, int* binary, int bits)
{
    for (int i = bits - 1; i >= 0; --i) {
        binary[i] = decimal % 2;
        decimal /= 2;
    }
}

int main()
{
    // S盒的逆运算表
    int S1[16] = {};
    for (int i = 0; i < 16; i++)
    {
        S1[S[i]] = i;
    }

    ifstream input("spn_pairs.txt");

    int L1[4] = {}; // 待求密钥1
    int L2[4] = {}; // 待求密钥2
    int v[16] = {};
    int u[16] = {};

    int n = 8000; // 组数

    for (int i = 0; i < n; i++)
    {
        string X, Y;
        input >> X >> Y;

        // 读取明文和密文
        for (int j = 0; j < 16; j++) {
            x[j] = X[j] - '0';
            y[j] = Y[j] - '0';
        }

        // 遍历所有可能的 L1 和 L2
        for (int j = 0; j < 16; j++)
        {
            for (int k = 0; k < 16; k++)
            {
                // 将 L1 和 L2 转换为 4 位二进制
                DecimalToBinary(j, L1, 4);
                DecimalToBinary(k, L2, 4);

                // 计算 v 的值，v4~v7 对应 L1，v12~v15 对应 L2
                for (int l = 0; l < 4; l++) {
                    v[4 + l] = L1[l] ^ y[4 + l];  // L1 对应的 v
                    v[12 + l] = L2[l] ^ y[12 + l]; // L2 对应的 v
                }

                // S盒逆运算
                int temp1 = (v[4] << 3) | (v[5] << 2) | (v[6] << 1) | v[7];
                int temp2 = S1[temp1]; // S盒逆运算得到 u
                DecimalToBinary(temp2, u + 4, 4); // u5~u7

                temp1 = (v[12] << 3) | (v[13] << 2) | (v[14] << 1) | v[15];
                temp2 = S1[temp1]; // S盒逆运算得到 u
                DecimalToBinary(temp2, u + 12, 4); // u13~u15

                // 计算 z
                int z = x[4] ^ x[6] ^ x[7] ^ u[5] ^ u[7] ^ u[13] ^ u[15];

                // 更新计数器
                if (z == 0) Count[j][k]++;
            }
        }
    }
    input.close();

    // 寻找最大值，计算最优的 L1 和 L2
    int max_val = -1;
    int LL1 = 0, LL2 = 0;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            Count[i][j] = abs(Count[i][j] - n / 2);
            if (Count[i][j] > max_val)
            {
                max_val = Count[i][j];
                LL1 = i;
                LL2 = j;
            }
        }
    }

    // 输出 key52 和 key54
    cout << "key52: ";
    DecimalToBinary(LL1, L1, 4);
    for (int i = 0; i < 4; i++)
    {
        cout << L1[i];
    }
    cout << endl << "key54: ";
    DecimalToBinary(LL2, L2, 4);
    for (int i = 0; i < 4; i++)
    {
        cout << L2[i];
    }

    return 0;
}
