#include<iostream>
#include <iomanip>
#include <string>
#include <cstring>
using namespace std;

int S[16][16] = {
	0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
	0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
	0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
	0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
	0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
	0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
	0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
	0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
	0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
	0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
	0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
	0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
	0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
	0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
	0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
	0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

// AES�ĳ˷�����
int aesMult(int a, int b)
{
	int res = 0;

	for (int i = 0; i < 8; ++i) // ����b��ÿһλ
	{
		if (b & (1 << i)) // ���b�ĵ�iλ�Ƿ�Ϊ1
		{
			int temp = a;
			// ����iλ
			for (int j = 0; j < i; ++j)
			{
				temp = temp << 1;
				if (temp >= 256)
					temp ^= 0x11b; // ģGF(2^8)�Ķ���ʽ
			}
			res ^= temp; // ��򵽽����
		}
	}

	return res;
}

//��Կ��չ
void KeyExpansion(int key[4][4], int w[11][4][4]) {
	int rC[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

	// ����ʼ��Կ���Ƶ�w[0]
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			w[0][i][j] = key[j][i];
		}
	}

	// ��չ��Կ
	for (int i = 1; i < 11; ++i) {
		for (int j = 0; j < 4; ++j) {
			int temp[4];

			// �����һ��
			if (j == 0) {
				// ��ת
				temp[0] = w[i - 1][3][1];
				temp[1] = w[i - 1][3][2];
				temp[2] = w[i - 1][3][3];
				temp[3] = w[i - 1][3][0];

				// �ֽ��滻���ֳ������
				for (int k = 0; k < 4; ++k) {
					int m = temp[k];
					int row = m / 16;
					int col = m % 16;
					temp[k] = S[row][col];
					if (k == 0) {
						temp[k] ^= rC[i - 1]; // �Ե�һ�ֽڽ����ֳ������
					}
				}
			}
			else {
				// ����������
				for (int x = 0; x < 4; x++) {
					temp[x] = w[i][j - 1][x];
				}
			}

			// ������չ��Կ
			for (int x = 0; x < 4; ++x) {
				w[i][j][x] = w[i - 1][j][x] ^ temp[x];
			}
		}
	}
}


// �ֽڴ���������λ
void ByteSubAndShiftRow(int in[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int temp = in[i][j];
			int row = temp / 16;
			int col = temp % 16;

			// ֻ���������ֽڴ���
			in[i][j] = S[row][col];
		}

		// ִ����������λ
		for (int j = 0; j < i; j++) {
			int temp = in[i][0];
			in[i][0] = in[i][1];
			in[i][1] = in[i][2];
			in[i][2] = in[i][3];
			in[i][3] = temp;

		}
	}
}

void MixColumn(int in[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		int t0 = in[0][i];
		int t1 = in[1][i];
		int t2 = in[2][i];
		int t3 = in[3][i];

		in[0][i] = aesMult(t0, 2) ^ aesMult(t1, 3) ^ t2 ^ t3;
		in[1][i] = t0 ^ aesMult(t1, 2) ^ aesMult(t2, 3) ^ t3;
		in[2][i] = t0 ^ t1 ^ aesMult(t2, 2) ^ aesMult(t3, 3);
		in[3][i] = aesMult(t0, 3) ^ t1 ^ t2 ^ aesMult(t3, 2);
	}
}

//����Կ��
void AddRoundKey(int in[4][4], int key[4][4])
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; j++)
			in[i][j] = in[i][j] ^ key[j][i];
}

void Encrypt(int in[4][4], int key[4][4])
{
	int subKey[11][4][4];
	KeyExpansion(key, subKey);    // ��Կ��չ
	AddRoundKey(in, subKey[0]);     //�뵱ǰ�ִε�����Կ����������
	int i;
	for (i = 1; i < 10; i++)
	{
		ByteSubAndShiftRow(in);  //�ֽڴ���
		MixColumn(in);   //�л��
		AddRoundKey(in, subKey[i]);   //��Կ��
	}
	//���һ�μ��㲻��Ҫ�л��
	ByteSubAndShiftRow(in);  //�ֽڴ���
	AddRoundKey(in, subKey[i]);   //��Կ��
}

void inputHexArray(int array[4][4], const string& input) {
	if (input.length() != 32) {
		cout << "�����ʮ�������ַ������Ȳ���ȷ��������32���ַ���" << endl;
		exit(1); // �˳�����
	}

	for (int i = 0; i < 16; i++) {
		// ÿ�ζ�ȡ�����ַ�����ת����ʮ����������
		string byte = input.substr(i * 2, 2);
		int value = stoi(byte, nullptr, 16); // ���ַ���ת��Ϊʮ����������
		array[i % 4][i / 4] = value; // ����������˳�����4x4����
	}
}


int main() {
	int txt[4][4];
	int key[4][4];

	string keyInput;
	cin >> keyInput;
	inputHexArray(key, keyInput);
	string plaintext;
	cin >> plaintext;
	inputHexArray(txt, plaintext);


	Encrypt(txt, key);  //����

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (txt[j][i] < 16)
				cout << "0";
			cout << uppercase << hex << txt[j][i];
		}
	}
}