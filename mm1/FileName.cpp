#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void Substitution(int* a, int* b, int* s)
{
    for (int i = 0; i < 4; i++)
    {
        // ����4λ�����Ƶ�ʮ���Ʊ�ʾ
        int T = (a[i * 4] << 3) | (a[i * 4 + 1] << 2) | (a[i * 4 + 2] << 1) | a[i * 4 + 3];
        int temp = s[T];
        // ��������ת����4λ�����Ʋ�����b
        for (int j = 3; j >= 0; j--)
        {
            b[i * 4 + j] = temp % 2;
            temp >>= 1; // ����1λ��������һ��������λ
        }
    }
}

void Permutation(int* a, int* b, int* p)
{
    for (int i = 0; i < 16; i++) b[p[i]] = a[i];
}

void SPN(int* x, int* s, int* p, int* K)
{
    int w[16], u[16], v[16], k[16], y[16];

    // ��ʼ��w����
    for (int i = 0; i < 16; i++) {
        w[i] = x[i];
    }

    for (int i = 0; i < 4; i++) {
        // ��ȡ��ǰ�ֵ���Կ
        for (int j = 0; j < 16; j++) {
            k[j] = K[4 * i + j];
        }

        for (int j = 0; j < 16; j++) {
            u[j] = w[j] ^ k[j];
        }

        // ������û�
        Substitution(u, v, s);
        if (i < 3) {
            Permutation(v, w, p);
        }
        else {
            // ���һ�ֲ������û���ֱ��������
            for (int j = 0; j < 16; j++) {
                y[j] = v[j] ^ K[4 * 4 + j]; // ʹ�����һ�ֵ���Կ
            }
        }
    }
    // ������ս��
    for (int i = 0; i < 16; i++) {
        cout << y[i];
    }
}
int main()
{
    int x[16], K[32];
    int pais[16] = { 0xE,4,0xD,1,2,0xF,0xB,8,3,0xA,6,0xC,5,9,0,7 };
    int paip[16] = { 0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15 };
    string X, Key;//���ģ���Կ
    cin >> X >> Key;

    for (int i = 0; i < 16; i++)
    {
        x[i] = X[i] - '0';
    }

    for (int i = 0; i < 32; i++)
    {
        K[i] = Key[i] - '0';
    }

    SPN(x, pais, paip, K);
    return 0;
}