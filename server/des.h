#ifndef DES_H
#define DES_H

#include <string>

class DES {
public:
    std::string encrypt(const std::string& plainText, const std::string& key);
    std::string decrypt(const std::string& cipherText, const std::string& key);
private:
    std::string hex2bin(const std::string& hex);
    std::string bin2hex(const std::string& bin);
    std::string permute(const std::string& input, const int* table, int n);
    std::string shift_left(const std::string& k, int shifts);
    std::string xor_(const std::string& a, const std::string& b);
    int bin2dec(const std::string& bin);
    std::string dec2bin(int dec);
    std::string f(const std::string& r, const std::string& sk);
};

#endif // DES_H
