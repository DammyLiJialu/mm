#include <iostream>
using namespace std;

// ��������
const long long a = 1;  // ���߲��� a
const long long b = 6;  // ���߲��� b
const long long p = 11; // ģ�� p
const long long q = 13; // ����ǩ�����ɵ�ģ��

// ģ�ˣ�a * b % n
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

// ��չŷ������㷨����Ԫ��a * x �� 1 (mod p)
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
    if (r0 != 1) return 0; // ��������Ԫ
    return (s0 + p) % p;
}

// �����ݣ�base^exp % mod
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

// ��ϣ���������� x^base % q
long long Hash(long long x, long long base, long long q) {
    return modExp(base, x, q);
}

// ��Բ�����ϵĵ�
class Point {
public:
    long long x, y;
    bool isInf; // �Ƿ�Ϊ����Զ��

    Point() : x(0), y(0), isInf(false) {}
    Point(long long x, long long y) : x(x), y(y), isInf(false) {}
    Point(long long x, long long y, bool isInf) : x(x), y(y), isInf(isInf) {}

    // �ж��������Ƿ�Ϊ����
    bool isInverse(const Point& p2) const {
        return (x == p2.x && (y + p2.y) % p == 0);
    }

    // ����������ĺ�
    Point add(const Point& p2) const {
        if (isInf) return p2;
        if (p2.isInf) return *this;
        if (isInverse(p2)) return Point(-1, -1, true); // ��������Զ��

        long long k, x3, y3, t1, t2;
        if (x == p2.x) {
            // �㱶�ӹ�ʽ
            t1 = mul(x, x, p);     // t1 = x^2 % p
            t1 = mul(3, t1, p);    // t1 = 3 * x^2 % p
            t1 = (t1 + a) % p;     // t1 = (3 * x^2 + a) % p

            t2 = mul(2, y, p);     // t2 = 2 * y % p
            t2 = modInverse(t2, p); // t2 = (2 * y)^-1 % p

            k = mul(t1, t2, p);    // k = (3 * x^2 + a) / (2 * y) % p
        }
        else {
            // ��ӹ�ʽ
            t1 = p2.y - y;         // t1 = y2 - y1
            if (t1 < 0) t1 += p;   // ȷ���Ǹ�

            t2 = p2.x - x;         // t2 = x2 - x1
            if (t2 < 0) t2 += p;   // ȷ���Ǹ�

            t2 = modInverse(t2, p); // t2 = (x2 - x1)^-1 % p
            k = mul(t1, t2, p);    // k = (y2 - y1) / (x2 - x1) % p
        }

        // ���� x3
        x3 = mul(k, k, p);         // x3 = k^2 % p
        x3 = (x3 - x - p2.x) % p;  // x3 = k^2 - x1 - x2 % p
        if (x3 < 0) x3 += p;       // ȷ���Ǹ�

        // ���� y3
        t1 = x - x3;               // t1 = x1 - x3
        if (t1 < 0) t1 += p;       // ȷ���Ǹ�

        y3 = mul(k, t1, p);        // y3 = k * (x1 - x3) % p
        y3 = (y3 - y) % p;         // y3 = k * (x1 - x3) - y1 % p
        if (y3 < 0) y3 += p;       // ȷ���Ǹ�

        return Point(x3, y3);
    }

    // ��ˣ�k���㣩
    Point multiply(long long k) const {
        Point result(-1, -1, true); // ����Զ��
        Point temp = *this;
        while (k) {
            if (k & 1) result = result.add(temp);
            temp = temp.add(temp); // �㱶��
            k >>= 1;
        }
        return result;
    }
};

int main() {
    long long x0, y0, m, x, k;
    cin >> x0 >> y0 >> m >> x >> k;

    Point basePoint(x0, y0);
    Point kP = basePoint.multiply(k); // ���� k * P

    // ���� r = (k * P).x % q
    long long r = kP.x % q;
    if (r < 0) r += q; // ȷ�� r ������
    // ���� s 
    long long kInverse = modInverse(k, q); // ���� k ����Ԫ

    long long tmp = (mul(r, m, q) + Hash(x, 2, q)) % q;
    if (tmp < 0) tmp += q; // ȷ�� tmp Ϊ����
    long long s = mul(kInverse, tmp, q);

    // ���ǩ�� (r, s)
    cout << r << " " << s;

    return 0;
}
