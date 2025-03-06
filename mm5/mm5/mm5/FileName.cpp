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

    // �Ȼ�ȡ��ʼ��bֵ��ͨ������a^m % n�������ｫ�����߼���ȡ����д��һ��С�Ķ����߼���
    
    long long temp_m = m;
    while (temp_m) {
        if (temp_m & 1) {
            b = mul(b, a, n);
        }
        a = mul(a, a, n);  // a = a^2 % n
        temp_m >>= 1;            // temp_m = temp_m / 2
    }
    

    // ����b�ĳ�ʼֵ���е�һ���жϣ����b == 1��n����������
    if (b == 1) return true;

    // ѭ���ж�b�Ƿ�����n - 1�����������n������
    for (long long i = 0; i < k; i++) {
        if (b == n - 1) return true;
        b = mul(b, b, n); // b = b^2 % n
    }

    return false;  // n�Ǻ���
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