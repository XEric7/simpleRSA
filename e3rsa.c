#include <stdio.h>
#include "rsa.h"
#include <string.h>

bool cipher(char *n_path, char *e_path, char *message_path, char *out_path)
{
    // rsa_cipher
    FILE *n_fp = fopen(n_path, "r");
    if (n_fp == NULL)
    {
        printf("Unable to open %s\n", n_path);
        return false;
    }

    FILE *e_fp = fopen(e_path, "r");
    if (e_fp == NULL)
    {
        printf("Unable to open %s\n", e_path);
        return false;
    }

    FILE *m_fp = fopen(message_path, "r");
    if (m_fp == NULL)
    {
        printf("Unable to open %s\n", message_path);
        return false;
    }

    FILE *out_fp = fopen(out_path, "w");
    if (out_fp == NULL)
    {
        printf("Unable to open %s\n", out_path);
        return false;
    }

    char n_str[50];
    fscanf(n_fp, "%s", n_str);
    fclose(n_fp);

    char e_str[50];
    fscanf(e_fp, "%s", e_str);
    fclose(e_fp);

    char m_str[50];
    fscanf(m_fp, "%s", m_str);
    fclose(m_fp);

    bignum n = stringToInt128(n_str);
    bignum e = stringToInt128(e_str);
    bignum m = stringToInt128(m_str);

    bignum c = rsaEncrypt(m, e, n);

    int128tofile(c, out_fp);
    fclose(out_fp);
    return true;
}

bool sign(char *hash_path, char *n_path, char *d_path, char *out_path)
{
    FILE *hash_fp = fopen(hash_path, "r");
    if (hash_fp == NULL)
    {
        printf("Unable to open %s\n", hash_path);
        return false;
    }

    FILE *n_fp = fopen(n_path, "r");
    if (n_fp == NULL)
    {
        printf("Unable to open %s\n", n_path);
        return false;
    }

    FILE *d_fp = fopen(d_path, "r");
    if (d_fp == NULL)
    {
        printf("Unable to open %s\n", d_path);
        return false;
    }

    FILE *out_fp = fopen(out_path, "w");
    if (out_fp == NULL)
    {
        printf("Unable to open %s\n", out_path);
        return false;
    }

    char n_str[50];
    fscanf(n_fp, "%s", n_str);
    fclose(n_fp);

    char d_str[50];
    fscanf(d_fp, "%s", d_str);
    fclose(d_fp);

    char hash_str[50];
    fscanf(hash_fp, "%s", hash_str);
    fclose(hash_fp);

    bignum n = stringToInt128(n_str);
    bignum d = stringToInt128(d_str);
    bignum hash = stringToInt128(hash_str);

    bignum c = rsaSign(hash, d, n);

    int128tofile(c, out_fp);
    fclose(out_fp);
    return true;
}
int main(int argc, char *argv[])
{
    char *plainfile = NULL;
    char *nfile = NULL;
    char *efile = NULL;
    char *dfile = NULL;
    char *cipherfile = NULL;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-p") == 0)
        {
            plainfile = argv[++i];
        }
        else if (strcmp(argv[i], "-n") == 0)
        {
            nfile = argv[++i];
        }
        else if (strcmp(argv[i], "-e") == 0)
        {
            efile = argv[++i];
        }
        else if (strcmp(argv[i], "-d") == 0)
        {
            dfile = argv[++i];
        }
        else if (strcmp(argv[i], "-c") == 0)
        {
            cipherfile = argv[++i];
        }
        else
        {
            printf("-p plainfile\t指定明文文件的位置和名称\n");
            printf("-n nfile\t指定存放整数 n 的文件的位置和名称\n");
            printf("-e efile\t在数据加密时, 指定存放整数 e 的文件的位置和名称\n");
            printf("-d dfile\t在数字签名时, 指定存放整数 d 的文件的位置和名称\n");
            printf("-c cipherfile\t指定密文文件的位置和名称\n");
        }
    }
    
    if (efile != NULL && dfile == NULL)
    {
        if (cipher(nfile, efile, plainfile, cipherfile))
        {
            printf("RSA Encryption success!\n");
        }
    }
    else if (efile == NULL && dfile != NULL)
    {
        if (sign(plainfile, nfile, dfile, cipherfile))
        {
            printf("RSA Sign success!\n");
        }
    }
    else
    {
        printf("arguments error!\n");
    }
   
    return 0;
}