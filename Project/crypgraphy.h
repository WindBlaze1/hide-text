#ifndef CIPHER_H
#define CIPHER_H
#include <string>
#include <sstream>

int for_encrypt(std::string inp_path, std::string out_path, std::string key, int choice);
std::string for_decrypt(std::string inp_path, std::string key, int choice, std::string out_path);
std::string make_locc(std::string s);

class Cipher
{
    protected:
        std::string input_path;
        std::string output_path;

    public:
        Cipher(std::string inp_path, std::string out_path);
        virtual std::string encrypt(std::string word) = 0;
        virtual std::string decrypt(std::string word) = 0;
        virtual int read_and_write(bool choice) = 0;
};

class caesar_c : public Cipher {
    int shift;

    public:
        caesar_c(std::string inp_path, std::string out_path, int x);
        std::string encrypt(std::string word);
        std::string decrypt(std::string word);
        int read_and_write(bool choice);
};

class vigenere_v : public Cipher {
    std::string key;

    public:
        vigenere_v(std::string inp_path, std::string out_path, std::string k);
        std::string get_full_key(std::string pt, std::string k);
        std::string encrypt(std::string word);
        std::string decrypt(std::string word);
        int read_and_write(bool choice);
};

#endif // CIPHER_H
