#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>   // ���� abs ����
using namespace std;

int S[16] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 };
int x[16] = {}; // ����
int y[16] = {}; // ����
int Count[16][16] = {}; // ������

// ʮ������ת��Ϊָ��λ���Ķ�������
void DecimalToBinary(int decimal, int* binary, int bits)
{
    for (int i = bits - 1; i >= 0; --i) {
        binary[i] = decimal % 2;
        decimal /= 2;
    }
}

int main()
{
    // S�е��������
    int S1[16] = {};
    for (int i = 0; i < 16; i++)
    {
        S1[S[i]] = i;
    }

    ifstream input("spn_pairs.txt");

    int L1[4] = {}; // ������Կ1
    int L2[4] = {}; // ������Կ2
    int v[16] = {};
    int u[16] = {};

    int n = 8000; // ����

    for (int i = 0; i < n; i++)
    {
        string X, Y;
        input >> X >> Y;

        // ��ȡ���ĺ�����
        for (int j = 0; j < 16; j++) {
            x[j] = X[j] - '0';
            y[j] = Y[j] - '0';
        }

        // �������п��ܵ� L1 �� L2
        for (int j = 0; j < 16; j++)
        {
            for (int k = 0; k < 16; k++)
            {
                // �� L1 �� L2 ת��Ϊ 4 λ������
                DecimalToBinary(j, L1, 4);
                DecimalToBinary(k, L2, 4);

                // ���� v ��ֵ��v4~v7 ��Ӧ L1��v12~v15 ��Ӧ L2
                for (int l = 0; l < 4; l++) {
                    v[4 + l] = L1[l] ^ y[4 + l];  // L1 ��Ӧ�� v
                    v[12 + l] = L2[l] ^ y[12 + l]; // L2 ��Ӧ�� v
                }

                // S��������
                int temp1 = (v[4] << 3) | (v[5] << 2) | (v[6] << 1) | v[7];
                int temp2 = S1[temp1]; // S��������õ� u
                DecimalToBinary(temp2, u + 4, 4); // u5~u7

                temp1 = (v[12] << 3) | (v[13] << 2) | (v[14] << 1) | v[15];
                temp2 = S1[temp1]; // S��������õ� u
                DecimalToBinary(temp2, u + 12, 4); // u13~u15

                // ���� z
                int z = x[4] ^ x[6] ^ x[7] ^ u[5] ^ u[7] ^ u[13] ^ u[15];

                // ���¼�����
                if (z == 0) Count[j][k]++;
            }
        }
    }
    input.close();

    // Ѱ�����ֵ���������ŵ� L1 �� L2
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

    // ��� key52 �� key54
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
