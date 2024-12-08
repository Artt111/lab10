#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <openssl/evp.h>

namespace fs = std::filesystem;
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <openssl/evp.h>

namespace fs = std::filesystem;

void menu();
void calculateFileHash();
void calculateTextHash();
std::string calculateMD5(const std::string& input);
std::string calculateSHA256(const std::string& input);
bool fileExists(const std::string& filePath); 

int main() {
    menu(); 
    return 0;
}

// Մենյուի իրագործում
void menu() {
    while (true) {
        std::cout << "===================================\n";
        std::cout << "       Հեշի հաշվարկի մենյու         \n";
        std::cout << "===================================\n";
        std::cout << "1. Հաշվարկել հեշ տեքստի համար\n";
        std::cout << "2. Հաշվարկել հեշ ֆայլի համար\n";
        std::cout << "0. Ելք\n";
        std::cout << "===================================\n";
        std::cout << "Ընտրեք գործողություն: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                calculateTextHash(); // Հեշ տեքստի համար
                break;
            case 2:
                calculateFileHash(); // Հեշ ֆայլի համար
                break;
            case 0:
                std::cout << "Ելք... Ցտեսություն!\n";
                return;
            default:
                std::cout << "Սխալ ընտրություն։ Փորձեք կրկին։\n";
        }
    }
}

// Ֆունկցիա՝ տեքստի հեշի հաշվարկի համար
void calculateTextHash() {
    std::cin.ignore();
    std::cout << "Մուտքագրեք տեքստ՝ հեշի համար: ";
    std::string text;
    std::getline(std::cin, text);

    std::cout << "===================================\n";
    std::cout << "MD5 Հեշ: " << calculateMD5(text) << "\n";
    std::cout << "SHA256 Հեշ: " << calculateSHA256(text) << "\n";
    std::cout << "===================================\n";
}

// Ֆունկցիա՝ ֆայլի հեշի հաշվարկի համար
void calculateFileHash() {
    std::cin.ignore(); 
    std::cout << "Մուտքագրեք ֆայլի ուղին: ";
    std::string filePath;
    std::getline(std::cin, filePath);

    // Ստուգում ենք՝ ֆայլը գոյություն ունի՞
    if (!fs::exists(filePath)) {
        std::cerr << "Սխալ: Ֆայլը գոյություն չունի։ Փորձեք կրկին։\n";
        return;
    }

    // Բացում ենք ֆայլը և կարդում բովանդակությունը
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Սխալ: Չհաջողվեց բացել ֆայլը։\n";
        return;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string fileContent = buffer.str();

    std::cout << "===================================\n";
    std::cout << "MD5 Հեշ: " << calculateMD5(fileContent) << "\n";
    std::cout << "SHA256 Հեշ: " << calculateSHA256(fileContent) << "\n";
    std::cout << "===================================\n";
}

// Ֆունկցիա՝ MD5 հեշի հաշվարկի համար
std::string calculateMD5(const std::string& input) {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new(); 
    unsigned char result[EVP_MAX_MD_SIZE];
    unsigned int resultLen = 0;

    // MD5 հեշի հաշվարկ
    EVP_DigestInit_ex(ctx, EVP_md5(), nullptr);
    EVP_DigestUpdate(ctx, input.c_str(), input.size());
    EVP_DigestFinal_ex(ctx, result, &resultLen);

    EVP_MD_CTX_free(ctx); 

    // Հեշի արդյունքը վերածում ենք հեքսադեցիմալ տողին։
    std::ostringstream hashStream;
    for (unsigned int i = 0; i < resultLen; ++i) {
        hashStream << std::hex << std::setw(2) << std::setfill('0') << (int)result[i];
    }
    return hashStream.str();
}

// Ֆունկցիա՝ SHA256 հեշի հաշվարկի համար
std::string calculateSHA256(const std::string& input) {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new(); // Ստեղծում ենք հեշի հաշվարկի կոնտեքստ։
    unsigned char result[EVP_MAX_MD_SIZE]; // Հեշի արդյունքը պահելու համար։
    unsigned int resultLen = 0;

    // SHA256 հեշի հաշվարկ
    EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);
    EVP_DigestUpdate(ctx, input.c_str(), input.size());
    EVP_DigestFinal_ex(ctx, result, &resultLen);

    EVP_MD_CTX_free(ctx); 

    // Հեշի արդյունքը վերածում ենք հեքսադեցիմալ տողին։
    std::ostringstream hashStream;
    for (unsigned int i = 0; i < resultLen; ++i) {
        hashStream << std::hex << std::setw(2) << std::setfill('0') << (int)result[i];
    }
    return hashStream.str();
}

// Օժանդակ ֆունկցիա՝ ֆայլի առկայությունը ստուգելու համար
bool fileExists(const std::string& filePath) {
    return fs::exists(filePath); 
}


