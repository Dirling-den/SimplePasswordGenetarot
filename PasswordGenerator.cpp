#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>

std::string generatePassword(int length, bool useLower, bool useUpper, bool useDigits, bool useSymbols) {
    const std::string lower = "abcdefghijklmnopqrstuvwxyz";
    const std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digits = "0123456789";
    const std::string symbols = "!@#$%^&*()-_=+[]{};:,.<>?/";

    std::string pool;

    if (useLower) pool += lower;
    if (useUpper) pool += upper;
    if (useDigits) pool += digits;
    if (useSymbols) pool += symbols;

    if (pool.empty()) return "";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, static_cast<int>(pool.size() - 1));

    std::string password;
    password.reserve(length);

    for (int i = 0; i < length; ++i) {
        password += pool[dist(gen)];
    }

    return password;
}

bool hasArg(int argc, char* argv[], const std::string& flag) {
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == flag) return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    int length = 12;

    if (argc > 1) {
        try {
            length = std::stoi(argv[1]);
        } catch (...) {
            std::cerr << "Invalid length\n";
            return 1;
        }
    }

    if (length < 1) {
        std::cerr << "Length must be positive\n";
        return 1;
    }

    bool useLower = hasArg(argc, argv, "--lower") || argc == 2;
    bool useUpper = hasArg(argc, argv, "--upper") || argc == 2;
    bool useDigits = hasArg(argc, argv, "--digits") || argc == 2;
    bool useSymbols = hasArg(argc, argv, "--symbols");

    if (argc == 2) {
        useSymbols = true;
    }

    std::string password = generatePassword(length, useLower, useUpper, useDigits, useSymbols);

    if (password.empty()) {
        std::cerr << "No character sets selected\n";
        return 1;
    }

    std::cout << "Generated password: " << password << "\n";
    return 0;
}