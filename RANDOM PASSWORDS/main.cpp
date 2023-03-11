
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

class PasswordGenerator {
public:
    virtual std::string generate() = 0;
    virtual int length() const = 0;
    virtual std::string allowed_chars() const = 0;
    virtual void add(PasswordGenerator* generator) {}
    virtual ~PasswordGenerator() {}
};

class BasicPasswordGenerator : public PasswordGenerator {
public:
    BasicPasswordGenerator(int len) : m_len(len) {}
    std::string generate() override {
        std::string password;
        const std::string allowed = allowed_chars();
        for (int i = 0; i < m_len; ++i) {
            password += allowed[rand() % allowed.size()];
        }
        return password;
    }
    int length() const override { return m_len; }
    std::string allowed_chars() const override { return ""; }
private:
    int m_len;
};

class DigitGenerator : public BasicPasswordGenerator {
public:
    DigitGenerator(int len) : BasicPasswordGenerator(len) {}
    std::string allowed_chars() const override { return "0123456789"; }
};

class SymbolGenerator : public BasicPasswordGenerator {
public:
    SymbolGenerator(int len) : BasicPasswordGenerator(len) {}
    std::string allowed_chars() const override { return "!@#$%^&*()_+-={}|[]\\:\";'<>?,./"; }
};

class UpperLetterGenerator : public BasicPasswordGenerator {
public:
    UpperLetterGenerator(int len) : BasicPasswordGenerator(len) {}
    std::string allowed_chars() const override { return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; }
};

class LowerLetterGenerator : public BasicPasswordGenerator {
public:
    LowerLetterGenerator(int len) : BasicPasswordGenerator(len) {}
    std::string allowed_chars() const override { return "abcdefghijklmnopqrstuvwxyz"; }
};

class CompositePasswordGenerator : public PasswordGenerator {
public:
    std::string generate() override {
        std::string password;
        for (const auto& generator : m_generators) {
            password += generator->generate();
        }
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        std::random_shuffle(password.begin(), password.end());
        return password;
    }
    int length() const override {
        int len = 0;
        for (const auto& generator : m_generators) {
            len += generator->length();
        }
        return len;
    }
    std::string allowed_chars() const override {
        std::string allowed;
        for (const auto& generator : m_generators) {
            allowed += generator->allowed_chars();
        }
        return allowed;
    }
    void add(PasswordGenerator* generator) override {
        m_generators.push_back(generator);
    }
private:
    std::vector<PasswordGenerator*> m_generators;
};

int main() {
    CompositePasswordGenerator generator;

    generator.add(new LowerLetterGenerator(2));
    generator.add(new UpperLetterGenerator(2));
    generator.add(new DigitGenerator(2));
    generator.add(new SymbolGenerator(2));

    std::cout << "Password length: " << generator.length() << std::endl;
    std::cout << "Allowed characters: " << generator.allowed_chars() << std::endl;
    std::cout << "Generated password: " << generator.generate() << std::endl;

    return 0;
}
