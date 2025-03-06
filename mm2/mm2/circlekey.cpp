//#include <iostream>
//#include <string>
//using namespace std;
//
//void KeySchedule(int* K, int roundKeys[4][16])
//{
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 16; j++) {
//            roundKeys[i][j] = K[i * 16 + j]; // 从主密钥提取每一轮密钥
//        }
//    }
//}
//
//int main()
//{
//    int K[32];
//    int roundKeys[4][16];
//
//    string Key = "01111111001000110101111100101110";
//    if (Key.length() != 32) {
//        cout << "密钥长度必须为32位！" << endl;
//        return 1; // 结束程序
//    }
//
//    for (int i = 0; i < 32; i++) {
//        K[i] = Key[i] - '0'; // 将字符转为整型
//    }
//
//    // 生成轮密钥
//    KeySchedule(K, roundKeys);
//
//    // 输出轮密钥
//    cout << "生成的轮密钥：" << endl;
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 16; j++) {
//            cout << roundKeys[i][j];
//        }
//        cout << endl;
//    }
//
//    return 0;
//}
