#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// 函数声明
int is_prime(long long num);
long long gcd(long long a, long long b);
void exgcd(long long a, long long b, long long* x, long long* y);
long long mod_pow(long long base, long long exponent, long long mod);

int main() {
    setlocale(LC_ALL, "chs"); // 设置中文输出

    long long p, q;

    printf("请输入两个素数p和q：");
    scanf_s("%lld %lld", &p, &q);

    if (!is_prime(p) || !is_prime(q)) {
        printf("错误：p或q不是素数。\n");
        return 1;
    }

    long long n = p * q;
    long long phi_n = (p - 1) * (q - 1);

    if (n < 256) {
        printf("错误：n=%lld 必须至少为256，请选择更大的素数。\n", n);
        return 1;
    }

    long long e;
    printf("请输入公钥e（需与φ(n)=%lld互质且1 < e < %lld）：", phi_n, phi_n);
    scanf_s("%lld", &e);

    if (e <= 1 || e >= phi_n || gcd(e, phi_n) != 1) {
        printf("错误：e不符合要求。\n");
        return 1;
    }

    long long d, y;
    exgcd(e, phi_n, &d, &y);
    d = (d % phi_n + phi_n) % phi_n;

    printf("\n公钥(e, n) = (%lld, %lld)\n", e, n);
    printf("私钥(d, n) = (%lld, %lld)\n\n", d, n);

    int choice;
    printf("请选择操作：1.加密  2.解密\n");
    scanf_s("%d", &choice);

    if (choice == 1) {
        char plaintext[256];
        printf("请输入明文（最多255字符）：");
        getchar(); // 清除输入缓冲区
        fgets(plaintext, sizeof(plaintext), stdin);
        plaintext[strcspn(plaintext, "\n")] = '\0';

        printf("\n加密结果：");
        for (int i = 0; plaintext[i] != '\0'; ++i) {
            long long m = (unsigned char)plaintext[i];
            long long c = mod_pow(m, e, n);
            printf("%lld ", c);
        }
        printf("\n");
    }
    else if (choice == 2) {
        printf("请输入密文（空格分隔数字，输入-1结束）：\n");
        long long c;
        while (1) {
            scanf_s("%lld", &c);
            if (c == -1) break;
            long long m = mod_pow(c, d, n);
            if (m < 0 || m >= 256) {
                printf("错误：解密值%lld无效\n", m);
                return 1;
            }
            printf("%c", (char)m);
        }
        printf("\n");
    }
    else {
        printf("无效选择。\n");
        return 1;
    }

    return 0;
}

// 判断素数（试除法）
int is_prime(long long num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (long long i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

// 计算最大公约数
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 扩展欧几里得算法（非递归实现）
void exgcd(long long a, long long b, long long* x, long long* y) {
    long long x0 = 1, x1 = 0;
    long long y0 = 0, y1 = 1;

    while (b != 0) {
        long long q = a / b;
        long long temp = b;
        b = a % b;
        a = temp;

        temp = x0 - q * x1;
        x0 = x1;
        x1 = temp;

        temp = y0 - q * y1;
        y0 = y1;
        y1 = temp;
    }

    *x = x0;
    *y = y0;
}

// 快速幂模运算
long long mod_pow(long long base, long long exponent, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        exponent = exponent >> 1;
        base = (base * base) % mod;
    }
    return result;
}
