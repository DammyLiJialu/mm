#include <iostream>
#include <cmath>
using namespace std;

// 模拟乘法，逐步累加并取模
long long mod_multiply(long long a, long long b, long long mod) {
    long long result = 0;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result + a) % mod; // 累加并取模
        }
        a = (a + a) % mod; // a 自身加倍并取模
        b = b / 2;         // b 右移一位
    }
    return result;
}

// 快速幂取模函数
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1; // 初始化结果
    base = base % mod;    // 对 base 取模以防止溢出

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = mod_multiply(result, base, mod); // 使用逐步累加的乘法
        }
        base = mod_multiply(base, base, mod); // base 平方并取模
        exp = exp / 2;                        // 指数右移
    }

    return result;
}

// 扩展欧几里得算法求模逆元
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

// 求解私钥 d
long long compute_d(long long e, long long phi) {
    long long x, y;
    long long g = gcd_extended(e, phi, x, y);
    if (g != 1) {
        return -1; // 无解
    }
    return (x % phi + phi) % phi;
}

int main() {
    // 输入 p, q
    long long p, q;
    cin >> p >> q;

    // 计算 n 和 φ(n)
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    // 输入公钥 e 和密文 c
    long long e, c;
    cin >> e >> c;

    // 计算私钥 d
    long long d = compute_d(e, phi);
    if (d == -1) {
        cout << "Error: Unable to compute modular inverse." << endl;
        return 1;
    }

    // 解密 m = c^d mod n
    long long m = mod_exp(c, d, n);

    // 输出明文
    cout << m << endl;

    return 0;
}
