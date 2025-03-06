#include <iostream>
#include <cmath>
using namespace std;

// ģ��˷������ۼӲ�ȡģ
long long mod_multiply(long long a, long long b, long long mod) {
    long long result = 0;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result + a) % mod; // �ۼӲ�ȡģ
        }
        a = (a + a) % mod; // a ����ӱ���ȡģ
        b = b / 2;         // b ����һλ
    }
    return result;
}

// ������ȡģ����
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1; // ��ʼ�����
    base = base % mod;    // �� base ȡģ�Է�ֹ���

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = mod_multiply(result, base, mod); // ʹ�����ۼӵĳ˷�
        }
        base = mod_multiply(base, base, mod); // base ƽ����ȡģ
        exp = exp / 2;                        // ָ������
    }

    return result;
}

// ��չŷ������㷨��ģ��Ԫ
long long gcd_extended(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = gcd_extended(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

// ���˽Կ d
long long compute_d(long long e, long long phi) {
    long long x, y;
    long long g = gcd_extended(e, phi, x, y);
    if (g != 1) {
        return -1; // �޽�
    }
    return (x % phi + phi) % phi;
}

int main() {
    // ���� p, q
    long long p, q;
    cin >> p >> q;

    // ���� n �� ��(n)
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    // ���빫Կ e ������ c
    long long e, c;
    cin >> e >> c;

    // ����˽Կ d
    long long d = compute_d(e, phi);
    if (d == -1) {
        cout << "Error: Unable to compute modular inverse." << endl;
        return 1;
    }

    // ���� m = c^d mod n
    long long m = mod_exp(c, d, n);

    // �������
    cout << m << endl;

    return 0;
}
