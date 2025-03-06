#include <iostream>
using namespace std;

long long mul(long long a, long long b, long long n) {
    long long result = 0;
    while (b) {
        if (b % 2 == 1) {
            result = (result + a) % n;
        }
        a = (a * 2) % n;
        b /= 2;
    }
    return result;
}

bool Miller_Rabin(long long n)
{
    // Write n - 1 as 2^k * m
    long long m = n - 1;
    long long k = 0;
    while (m % 2 == 0) {
        m /= 2;
        k++;
    }

    // Perform the Miller-Rabin test
    long long a = (rand() % (n - 1)) + 1;
    long long b = 1;

    // 先获取初始的b值（通过计算a^m % n），这里将计算逻辑提取出来写成一个小的独立逻辑块
    
    long long temp_m = m;
    while (temp_m) {
        if (temp_m & 1) {
            b = mul(b, a, n);
        }
        a = mul(a, a, n);  // a = a^2 % n
        temp_m >>= 1;            // temp_m = temp_m / 2
    }
    

    // 根据b的初始值进行第一步判断，如果b == 1，n可能是质数
    if (b == 1) return true;

    // 循环判断b是否会等于n - 1，如果等于则n是质数
    for (long long i = 0; i < k; i++) {
        if (b == n - 1) return true;
        b = mul(b, b, n); // b = b^2 % n
    }

    return false;  // n是合数
}
int main()
{
    long long n;
    cin >> n;
    for (int i = 0; i < 10; i++)
    {
        if (!Miller_Rabin(n))
        {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes";
    return 0;
}