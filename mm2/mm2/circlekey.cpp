//#include <iostream>
//#include <string>
//using namespace std;
//
//void KeySchedule(int* K, int roundKeys[4][16])
//{
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 16; j++) {
//            roundKeys[i][j] = K[i * 16 + j]; // ������Կ��ȡÿһ����Կ
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
//        cout << "��Կ���ȱ���Ϊ32λ��" << endl;
//        return 1; // ��������
//    }
//
//    for (int i = 0; i < 32; i++) {
//        K[i] = Key[i] - '0'; // ���ַ�תΪ����
//    }
//
//    // ��������Կ
//    KeySchedule(K, roundKeys);
//
//    // �������Կ
//    cout << "���ɵ�����Կ��" << endl;
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 16; j++) {
//            cout << roundKeys[i][j];
//        }
//        cout << endl;
//    }
//
//    return 0;
//}
