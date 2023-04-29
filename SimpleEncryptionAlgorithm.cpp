#include <iostream>
#include <string>
#include <vector>

const std::string kCharSet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*(){}|/<>~`-=_+. ";

unsigned char EncryptChar(unsigned char c, int key, const std::string& charSet) {
    const auto pos = charSet.find(c);
    return pos == std::string::npos ? 0xDE : charSet[(pos + key) % charSet.size()];
}

std::string EncryptString(const std::string& str, const std::vector<int>& keys) {
    std::string result(str.size(), ' ');
    for (std::size_t i = 0; i < str.size() && !keys.empty(); ++i) {
        result[i] = EncryptChar(str[i], keys[i % keys.size()], kCharSet);
        if (result[i] == 0xDE) return "";
    }
    return result;
}

int main() {
    std::cout << "CharSet: " << kCharSet << '\n';
    std::cout << "Enter a string to encrypt:\n";
    std::string input;
    std::getline(std::cin, input);

    std::cout << "Enter an encryption key as positive integers. Type -1 to finish input:\n";
    std::vector<int> keys;
    for (int key; std::cin >> key && key != -1; keys.push_back(std::abs(key)));
    
    const std::string output = EncryptString(input, keys);
    if (output.empty()) {
        std::cout << "Encryption failed.\n";
        return -1;
    }

    std::cout << "\nOriginal:  " << input << "\nEncrypted: " << output << '\n';
    return main();
}