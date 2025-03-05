'''维吉尼亚破解'''
import numpy as np
import wordninja
import vigenerecipher
import string
import re

def alpha(cipher):  # 预处理,去掉空格以及回车
    c = ''
    for i in range(len(cipher)):
        if (cipher[i].isalpha()):
            c += cipher[i]
    return c


def trans(cipher,key_len):
    decrypted = ''
    for i in range(len(cipher)):
        mov = int(i / key_len)
        mov %= 26
        t = ord(cipher[i]) - mov

        if t <65:
            t += 26

        decrypted += chr(t)
    return decrypted
def count_IC(cipher):  # 给定字符串计算其重合指数
    count = [0 for i in range(26)]
    L = len(cipher)
    IC = 0.0
    for i in range(len(cipher)):
        if (cipher[i].isupper()):
            count[ord(cipher[i]) - ord('A')] += 1
        elif (cipher[i].islower()):
            count[ord(cipher[i]) - ord('a')] += 1
    for i in range(26):
        IC += (count[i] * (count[i] - 1)) / (L * (L - 1))
    return IC


def count_key_len(cipher, key_len):  # 对字符串按输入个数进行分组，计算每一组的IC值返回平均值
    str = trans(cipher, key_len)


    N = ['' for i in range(key_len)]
    IC = [0 for i in range(key_len)]
    for i in range(len(str)):
        m = i % key_len
        N[m] += str[i]
    for i in range(key_len):
        IC[i] = count_IC(N[i])



    print("长度为%d时,平均重合指数为%.5f" % (key_len, np.mean(IC)))
    return np.mean(IC)


def length(cipher):  # 遍历确定最有可能的密钥长度返回密钥长度
    key_len = 1
    mins = 100
    aver = 0.0
    for i in range(1, 10):


        k = count_key_len(cipher, i)

        if (abs(k - 0.065) < mins):
            mins = abs(k - 0.065)
            key_len = i

            aver = k
    print("密钥长度为%d,此时重合指数每组的平均值为%.5f" % (key_len, aver))
    return key_len


def count_MIC(c1, c2, n):  # n=k1-k2为偏移量,计算c1,c2互重合指数MIC
    count_1 = [0 for i in range(26)]
    count_2 = [0 for i in range(26)]
    L_1 = len(c1)
    L_2 = len(c2)
    MIC = 0
    for i in range(L_1):
        if (c1[i].isupper()):
            count_1[ord(c1[i]) - ord('A')] += 1
        elif (c1[i].islower()):
            count_1[ord(c1[i]) - ord('a')] += 1
    for i in range(L_2):
        if (c2[i].isupper()):
            count_2[(ord(c2[i]) - ord('A') + n + 26) % 26] += 1
        elif (c2[i].islower()):
            count_2[(ord(c2[i]) - ord('a') + n + 26) % 26] += 1
    for i in range(26):
        MIC += count_1[i] * count_2[i] / (L_1 * L_2)
    return MIC


def count_n(c1, c2):  # 确定两个子串最优的相对偏移量n=k1-k2
    n = 0
    mins = 100
    k = [0.0 for i in range(26)]
    for i in range(26):
        k[i] = count_MIC(c1, c2, i)
        # print(i,k[i])
        if (abs(k[i] - 0.065) < mins):
            mins = abs(k[i] - 0.065)
            n = i
    return n


def group_k(cipher, key_len):  # 完成分组操作并计算每一组与第一组的最优相对偏移量并返回
    N = ['' for i in range(key_len)]
    MIC = [0 for i in range(key_len)]
    s = [0 for i in range(key_len)]
    for i in range(len(cipher)):  # 对密文进行分组
        m = i % key_len
        N[m] += cipher[i]
    for i in range(1, key_len):  # 计算与第一组之间的相对偏移量
        s[i] = count_n(N[0], N[i])  # s[i] = k1-k(i+1)
        MIC[i] = count_MIC(N[0], N[i], s[i])  # MIC[i] = MIC(1,i+1)
        print("第1组和第%d组之间偏移为%d时，互重合指数为%.5f" % (i + 1, s[i], MIC[i]))
    return s


def miyao(key_len, s, k):  # k为第一个子串的移位，输出密钥并返回密钥所有字母的下标
    mi = ['' for i in range(key_len)]
    for i in range(key_len):
        s[i] = -s[i] + k  # k2=k1-n
        mi[i] = chr((s[i] + 26) % 26 + ord('a'))
    print("第一个偏移量为%d,密钥为%s时" % (k, mi))
    return s


def the_end(cipher, key_len, s):  # 输入密文密钥返回明文结果
    plain = ''
    i = 0
    while (i < len(cipher)):
        for j in range(key_len):
            if (cipher[i].isupper()):
                plain += chr((ord(cipher[i]) - ord('A') -s[j] + 26) % 26 + ord('A'))
            else:
                plain += chr((ord(cipher[i]) - ord('a') -s[j] + 26) % 26 + ord('a'))
            i += 1
            if (i == len(cipher)):
                break
                # print(plain)
    return plain
def keyword(Ciphertext, keylength):
    ListCiphertext = list(Ciphertext)
    # 标准数据来源于课本
    Standard = {'A': 0.082, 'B': 0.015, 'C': 0.028, 'D': 0.043, 'E': 0.127, 'F': 0.022, 'G': 0.020, 'H': 0.061,
                'I': 0.070, 'J': 0.002, 'K': 0.008, 'L': 0.040, 'M': 0.024, 'N': 0.067, 'O': 0.075, 'P': 0.019,
                'Q': 0.001, 'R': 0.060, 'S': 0.063, 'T': 0.091, 'U': 0.028, 'V': 0.010, 'W': 0.023, 'X': 0.001,
                'Y': 0.020, 'Z': 0.001}

    while True:
        KeyResult = []

        for i in range(keylength):
            # 使用切片分组
            PresentCipherList = ListCiphertext[i::keylength]

            # 初始化重合指数最大值为０，检验移动位数对应字符以＊代替
            QuCoincidenceMax = 0
            KeyLetter = "*"

            # 遍历移动的位数
            # m是密钥对应的英文字母
            for m in range(26):
                # 初始化当前移动位数的重合互指数为０
                QuCoincidencePresent = 0

                # 遍历计算重合指数：各个字符的频率＊对应英文字符出现的标准频率－－－的和
                for Letter in set(PresentCipherList):
                    # fi/n
                    LetterFrequency = PresentCipherList.count(Letter) / len(PresentCipherList)

                    # 标准频率
                    # ord(Letter) - 65是将letter对应的字母化为26内的数值，然后与m运算，得到的k是对应的明文字母
                    k = chr((ord(Letter) - 65 - m) % 26 + 65)
                    StandardFrequency = Standard[k]

                    # 计算重合互指数，累加遍历26个英文字母
                    QuCoincidencePresent = QuCoincidencePresent + LetterFrequency * StandardFrequency

                # 保存遍历过程中重合指数的最大值，同时保存对应应对的位数，即对应key的字符
                if QuCoincidencePresent > QuCoincidenceMax:
                    QuCoincidenceMax = QuCoincidencePresent
                    # m是26个英文对应的位置，从0开始，+65是因为A在ascii中是65
                    KeyLetter = chr(m + 65)
            print("第", i + 1, "个密钥字母为:", KeyLetter, "对应的重合互指数为:", QuCoincidenceMax)
            # 保存当前位置key的值，退出循环，进行下一组子密文移动位数的尝试
            KeyResult.append(KeyLetter)
        # 列表转为字符串
        Key = "".join(KeyResult)
        break
    return Key

if __name__ == "__main__":
    fp = open("密文.txt", "r")
    cipher = ''
    for i in fp.readlines():
        cipher = cipher + i
    fp.close()
    cipher = alpha(cipher)

    key_len = length(cipher)
    str = trans(cipher, key_len)

    KeyResult = keyword(str, 5)

    print("密钥最可能为：", KeyResult, "\n")

    '''对英文文本进行分词'''

    ClearText = vigenerecipher.decode(str, KeyResult)
    print("解密结果为：", ClearText)
