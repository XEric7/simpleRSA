# Requirement

- 必须：64位系统环境 64位gcc编译器
- 可选：gcc.exe (tdm64-1) 10.3.0

# Usage

## 编译

```bash
make
```

## 密钥生成

```bash
.\keyGenerator.exe
```
分别存放在p.txt q.txt n.txt e.txt d.txt 中

## 数字签名
```bash
.\e3rsa.exe -p rsa_plain.txt -n rsa_n.txt -d rsa_d.txt -c rsa_sign.txt
```

## 数字加密
```bash
.\e3rsa.exe -p rsa_plain.txt -n rsa_n.txt -e rsa_e.txt -c rsa_cipher.txt
```