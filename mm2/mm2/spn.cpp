//#include <iostream>
//#include <fstream>
//#include <string>
//#include <cmath>
//using namespace std;
//
//int S[16] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 };
//int P[16] = { 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15 };
//
//int x[16], y[16], key[32];
//
//void Substitution(int* a, int* b, int* s);
//void Permutation(int* a, int* b, int* p);
//void SPN(int* x, int* y, int* s, int* p, int* key);
//
//int main()
//{
//     文件输入输出
//    ifstream plaintextFile("random_ming.txt");  // 明文输入文件
//    ifstream keyFile("key.txt");                // 密钥输入文件
//    ofstream ciphertextFile("spn_pairs.txt");  // 密文输出文件
//
//    
//
//    string Key;
//    Key = "00111010100101001101011000111111";
//
//     读取并处理密钥
//    int keyLen = Key.length();
//    for (int i = 0; i < keyLen; i++)
//    {
//        key[i] = Key[i] - '0';
//    }
//
//    string X;
//     逐行读取明文并处理
//    while (plaintextFile >> X)
//    {
//       
//        
//         将明文转换为整数数组
//        for (int i = 0; i < 16; i++)
//        {
//            x[i] = X[i] - '0';
//            ciphertextFile << x[i];
//        }
//        ciphertextFile << endl;
//         SPN 加密
//        SPN(x, y, S, P, key);
//
//         将加密后的密文输出到文件
//        for (int i = 0; i < 16; i++)
//        {
//            ciphertextFile << y[i];
//        }
//        ciphertextFile << endl;  // 每个密文占一行
//
//    }
//
//     关闭文件
//    plaintextFile.close();
//    ciphertextFile.close();
//
//    return 0;
//}
//
//void Substitution(int* a, int* b, int* s)
//{
//    int T[4] = {};
//    for (int i = 0; i < 4; i++)
//    {
//        T[i] = a[i * 4] * pow(2, 3) + a[i * 4 + 1] * pow(2, 2) + a[i * 4 + 2] * pow(2, 1) + a[i * 4 + 3];
//        int temp = s[T[i]];
//
//        int j = (i * 4) + 3;
//        while (temp > 0)
//        {
//            b[j] = temp % 2;
//            temp = temp / 2;
//            j--;
//        }
//        while (j >= (i * 4))
//        {
//            b[j] = 0;
//            j--;
//        }
//    }
//}
//
//void Permutation(int* a, int* b, int* p)
//{
//    for (int i = 0; i < 16; i++)
//    {
//        b[p[i]] = a[i];
//    }
//}
//
//void SPN(int* x, int* y, int* s, int* p, int* key)
//{
//    int w[16], u[16], v[16], k[16];
//    for (int i = 0; i < 16; i++)
//    {
//        w[i] = x[i];
//    }
//    for (int i = 0; i < 3; i++)
//    {
//        for (int j = 0; j < 16; j++)
//        {
//            k[j] = key[4 * i + j];
//        }
//
//        for (int j = 0; j < 16; j++)
//        {
//            u[j] = w[j] ^ k[j];
//        }
//
//        Substitution(u, v, s);
//        Permutation(v, w, p);
//    }
//
//    for (int j = 0; j < 16; j++)
//    {
//        k[j] = key[4 * 3 + j];
//    }
//
//    for (int j = 0; j < 16; j++)
//    {
//        u[j] = w[j] ^ k[j];
//    }
//
//    Substitution(u, v, s);
//
//    for (int j = 0; j < 16; j++)
//    {
//        k[j] = key[4 * 4 + j];
//    }
//
//    for (int j = 0; j < 16; j++)
//    {
//        y[j] = v[j] ^ k[j];
//    }
//}
