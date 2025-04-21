#define _CRT_SECURE_NO_WARNINGS  // 禁用安全警告
#include <stdio.h>
#include <string.h>
#include <locale.h>
// 初始置换表IP
int IP[] = {
    58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7
};

// 逆初始置换表IP^-1
int IP_INV[] = {
    40,8,48,16,56,24,64,32,
    39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,
    37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,
    35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,
    33,1,41,9,49,17,57,25
};

// 扩展置换表E
int E[] = {
    32,1,2,3,4,5,4,5,
    6,7,8,9,8,9,10,11,
    12,13,12,13,14,15,16,17,
    16,17,18,19,20,21,20,21,
    22,23,24,25,24,25,26,27,
    28,29,28,29,30,31,32,1
};

// 置换表P
int P[] = {
    16,7,20,21,29,12,28,17,
    1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,
    19,13,30,6,22,11,4,25
};

// 置换选择表PC-1
int PC1[] = {
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
};

// 置换选择表PC-2
int PC2[] = {
    14,17,11,24,1,5,3,28,
    15,6,21,10,23,19,12,4,
    26,8,16,7,27,20,13,2,
    41,52,31,37,47,55,30,40,
    51,45,33,48,44,49,39,56,
    34,53,46,42,50,36,29,32
};

// S盒
int S[8][4][16] = {
    // S1
    {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
     {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
     {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
     {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
     // S2
     {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
      {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
      {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
      {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
      // S3
      {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
       {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
       {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
       {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
       // S4
       {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
        // S5
        {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
         {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
         {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
         {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
         // S6
         {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
          {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
          {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
          {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
          // S7
          {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
           {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
           {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
           {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
           // S8
           {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
            {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
            {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
            {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}
};

// 获取指定位的值
int get_bit(const unsigned char* data, int pos) {
    pos--;
    int byte_index = pos / 8;
    int bit_index = pos % 8;
    return (data[byte_index] >> (7 - bit_index)) & 1;
}

// 设置指定位的值
void set_bit(unsigned char* data, int pos, int val) {
    pos--;
    int byte_index = pos / 8;
    int bit_index = pos % 8;
    if (val)
        data[byte_index] |= (1 << (7 - bit_index));
    else
        data[byte_index] &= ~(1 << (7 - bit_index));
}

// 初始置换
void initial_permutation(unsigned char* data) {
    unsigned char temp[8] = { 0 };
    for (int i = 0; i < 64; i++) {
        int pos = IP[i];
        int val = get_bit(data, pos);
        set_bit(temp, i + 1, val);
    }
    memcpy(data, temp, 8);
}

// 逆初始置换
void inverse_initial_permutation(unsigned char* data) {
    unsigned char temp[8] = { 0 };
    for (int i = 0; i < 64; i++) {
        int pos = IP_INV[i];
        int val = get_bit(data, pos);
        set_bit(temp, i + 1, val);
    }
    memcpy(data, temp, 8);
}

// 生成子密钥
void generate_subkeys(unsigned char* key, unsigned char subkeys[16][6]) {
    unsigned char pc1_result[7] = { 0 };
    for (int i = 0; i < 56; i++) {
        int pos = PC1[i];
        set_bit(pc1_result, i + 1, get_bit(key, pos));
    }

    unsigned char C[28], D[28];
    for (int i = 0; i < 28; i++) {
        C[i] = get_bit(pc1_result, i + 1);
        D[i] = get_bit(pc1_result, i + 29);
    }

    int shift_schedule[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

    for (int round = 0; round < 16; round++) {
        // 循环左移
        int shift = shift_schedule[round];
        unsigned char temp;

        for (int s = 0; s < shift; s++) {
            temp = C[0];
            for (int i = 0; i < 27; i++) C[i] = C[i + 1];
            C[27] = temp;

            temp = D[0];
            for (int i = 0; i < 27; i++) D[i] = D[i + 1];
            D[27] = temp;
        }

        unsigned char CD[56];
        memcpy(CD, C, 28);
        memcpy(CD + 28, D, 28);

        unsigned char subkey[6] = { 0 };
        for (int i = 0; i < 48; i++) {
            int pos = PC2[i];
            set_bit(subkey, i + 1, CD[pos - 1]);
        }

        memcpy(subkeys[round], subkey, 6);
    }
}

// Feistel轮函数
void feistel(unsigned char* R, unsigned char* K, unsigned char* output) {
    unsigned char expanded[6] = { 0 };
    for (int i = 0; i < 48; i++) {
        int pos = E[i];
        set_bit(expanded, i + 1, get_bit(R, pos));
    }

    for (int i = 0; i < 6; i++) expanded[i] ^= K[i];

    unsigned char s_output[4] = { 0 };
    for (int i = 0; i < 8; i++) {
        int row = (get_bit(expanded, i * 6 + 1) << 1) | get_bit(expanded, i * 6 + 6);
        int col = (get_bit(expanded, i * 6 + 2) << 3) | (get_bit(expanded, i * 6 + 3) << 2) |
            (get_bit(expanded, i * 6 + 4) << 1) | get_bit(expanded, i * 6 + 5);
        int val = S[i][row][col];

        for (int j = 0; j < 4; j++) {
            set_bit(s_output, i * 4 + j + 1, (val >> (3 - j)) & 1);
        }
    }

    for (int i = 0; i < 32; i++) {
        int pos = P[i];
        set_bit(output, i + 1, get_bit(s_output, pos));
    }
}

// DES加密
void des_encrypt(unsigned char* data, unsigned char subkeys[16][6]) {
    initial_permutation(data);

    unsigned char L[4], R[4];
    memcpy(L, data, 4);
    memcpy(R, data + 4, 4);

    for (int round = 0; round < 16; round++) {
        unsigned char next_L[4];
        memcpy(next_L, R, 4);

        unsigned char F_result[4] = { 0 };
        feistel(R, subkeys[round], F_result);

        for (int i = 0; i < 4; i++) R[i] = L[i] ^ F_result[i];
        memcpy(L, next_L, 4);
    }

    unsigned char combined[8];
    memcpy(combined, R, 4);
    memcpy(combined + 4, L, 4);

    inverse_initial_permutation(combined);
    memcpy(data, combined, 8);
}

// DES解密
void des_decrypt(unsigned char* data, unsigned char subkeys[16][6]) {
    initial_permutation(data);

    unsigned char L[4], R[4];
    memcpy(L, data, 4);
    memcpy(R, data + 4, 4);

    for (int round = 15; round >= 0; round--) {
        unsigned char next_L[4];
        memcpy(next_L, R, 4);

        unsigned char F_result[4] = { 0 };
        feistel(R, subkeys[round], F_result);

        for (int i = 0; i < 4; i++) R[i] = L[i] ^ F_result[i];
        memcpy(L, next_L, 4);
    }

    unsigned char combined[8];
    memcpy(combined, R, 4);
    memcpy(combined + 4, L, 4);

    inverse_initial_permutation(combined);
    memcpy(data, combined, 8);
}

// 打印十六进制
void print_hex(unsigned char* data, int len) {
    for (int i = 0; i < len; i++)
        printf("%02X", data[i]);
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "chs");
    unsigned char plaintext[8] = { 0 };   // 初始化为全0
    unsigned char ciphertext[8] = { 0 };
    unsigned char key[8] = { 0 };
    unsigned char subkeys[16][6];

    // 安全输入处理
    printf("请输入明文（最多7个字符）:");
    if (scanf("%7s", plaintext) != 1) {  // 限制输入长度
        printf("输入错误！\n");
        return 1;
    }

    printf("请输入密钥（最多7个字符）:");
    if (scanf("%7s", key) != 1) {        // 限制输入长度
        printf("输入错误！\n");
        return 1;
    }

    // 自动填充空白字符（可选）
    for (int i = strlen((char*)plaintext); i < 8; i++) plaintext[i] = ' ';
    for (int i = strlen((char*)key); i < 8; i++) key[i] = ' ';

    generate_subkeys(key, subkeys);

    // 加密过程
    memcpy(ciphertext, plaintext, 8);
    des_encrypt(ciphertext, subkeys);
    printf("\n加密结果（HEX）: ");
    print_hex(ciphertext, 8);

    // 解密过程
    des_decrypt(ciphertext, subkeys);
    printf("解密结果（原文）: ");
    for (int i = 0; i < 8; i++) {
        if (ciphertext[i] >= 32) putchar(ciphertext[i]);  // 过滤控制字符
    }
    printf("\n");

    return 0;
}
