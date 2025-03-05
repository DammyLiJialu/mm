#include <iostream>
using namespace std;

// 常量定义
const long long a = 1;  // 曲线参数 a
const long long b = 6;  // 曲线参数 b
const long long p = 11; // 模数 p
const long long q = 13; // 用于签名生成的模数

// 模乘：a * b % n
long long mul(long long a, long long b, long long n) {
    long long result = 0;
    while (b) {
        if (b & 1) {
            result = (result + a) % n;
        }
        a = (a + a) % n;
        b >>= 1;
    }
    return result;
}

// 扩展欧几里得算法求逆元：a * x ≡ 1 (mod p)
long long modInverse(long long a, long long p) {
    long long s0 = 1, t0 = 0, s1 = 0, t1 = 1;
    long long r0 = a, r1 = p;
    while (r1) {
        long long q = r0 / r1;
        long long r = r0 - q * r1;
        long long s = s0 - q * s1;
        long long t = t0 - q * t1;
        r0 = r1; r1 = r;
        s0 = s1; s1 = s;
        t0 = t1; t1 = t;
    }
    if (r0 != 1) return 0; // 不存在逆元
    return (s0 + p) % p;
}

// 快速幂：base^exp % mod
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp) {
        if (exp & 1) {
            result = mul(result, base, mod);
        }
        base = mul(base, base, mod);
        exp >>= 1;
    }
    return result;
}

// 哈希函数：计算 x^base % q
long long Hash(long long x, long long base, long long q) {
    return modExp(base, x, q);
}

// 椭圆曲线上的点
class Point {
public:
    long long x, y;
    bool isInf; // 是否为无穷远点

    Point() : x(0), y(0), isInf(false) {}
    Point(long long x, long long y) : x(x), y(y), isInf(false) {}
    Point(long long x, long long y, bool isInf) : x(x), y(y), isInf(isInf) {}

    // 判断两个点是否互为反点
    bool isInverse(const Point& p2) const {
        return (x == p2.x && (y + p2.y) % p == 0);
    }

    // 计算两个点的和
    Point add(const Point& p2) const {
        if (isInf) return p2;
        if (p2.isInf) return *this;
        if (isInverse(p2)) return Point(-1, -1, true); // 返回无穷远点

        long long k, x3, y3, t1, t2;
        if (x == p2.x) {
            // 点倍加公式
            t1 = mul(x, x, p);     // t1 = x^2 % p
            t1 = mul(3, t1, p);    // t1 = 3 * x^2 % p
            t1 = (t1 + a) % p;     // t1 = (3 * x^2 + a) % p

            t2 = mul(2, y, p);     // t2 = 2 * y % p
            t2 = modInverse(t2, p); // t2 = (2 * y)^-1 % p

            k = mul(t1, t2, p);    // k = (3 * x^2 + a) / (2 * y) % p
        }
        else {
            // 点加公式
            t1 = p2.y - y;         // t1 = y2 - y1
            if (t1 < 0) t1 += p;   // 确保非负

            t2 = p2.x - x;         // t2 = x2 - x1
            if (t2 < 0) t2 += p;   // 确保非负

            t2 = modInverse(t2, p); // t2 = (x2 - x1)^-1 % p
            k = mul(t1, t2, p);    // k = (y2 - y1) / (x2 - x1) % p
        }

        // 计算 x3
        x3 = mul(k, k, p);         // x3 = k^2 % p
        x3 = (x3 - x - p2.x) % p;  // x3 = k^2 - x1 - x2 % p
        if (x3 < 0) x3 += p;       // 确保非负

        // 计算 y3
        t1 = x - x3;               // t1 = x1 - x3
        if (t1 < 0) t1 += p;       // 确保非负

        y3 = mul(k, t1, p);        // y3 = k * (x1 - x3) % p
        y3 = (y3 - y) % p;         // y3 = k * (x1 - x3) - y1 % p
        if (y3 < 0) y3 += p;       // 确保非负

        return Point(x3, y3);
    }

    // 点乘（k倍点）
    Point multiply(long long k) const {
        Point result(-1, -1, true); // 无穷远点
        Point temp = *this;
        while (k) {
            if (k & 1) result = result.add(temp);
            temp = temp.add(temp); // 点倍加
            k >>= 1;
        }
        return result;
    }
};

int main() {
    long long x0, y0, m, x, k;
    cin >> x0 >> y0 >> m >> x >> k;

    Point basePoint(x0, y0);
    Point kP = basePoint.multiply(k); // 计算 k * P

    // 计算 r = (k * P).x % q
    long long r = kP.x % q;
    if (r < 0) r += q; // 确保 r 是正数
    // 计算 s 
    long long kInverse = modInverse(k, q); // 计算 k 的逆元

    long long tmp = (mul(r, m, q) + Hash(x, 2, q)) % q;
    if (tmp < 0) tmp += q; // 确保 tmp 为正数
    long long s = mul(kInverse, tmp, q);

    // 输出签名 (r, s)
    cout << r << " " << s;

    return 0;
}
