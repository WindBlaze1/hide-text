#ifndef __STEGRAPHY
#define __STEGRAPHY
#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#define cimg_display 0
#include"CImg.h"
#define bytecimg CImg<unsigned char>
#define SKIP 3          //No. of bytes to skip while injecting
using namespace std;
using namespace cimg_library;

string make_loc(string s);

int for_encode(string target_loc, string msg_loc, string save_loc, int type);

string for_decode(string file_loc);

class encrypt {
    public:
    string msg_url;
    string file_url;
    encrypt(string target_file_url, string message_url="-"):
        file_url(target_file_url), msg_url(message_url) {}
    virtual int cipher(string filename) = 0;
    virtual int usableTargetSize() = 0;
    int messageSize();
    bool isSizeEnough();
    char inject_bit(char* target_byte, char message, int bit_count);
};

class encrypt_wav:public encrypt {
    public:
    encrypt_wav(string target_file_url, string message_url="-"):
        encrypt(target_file_url,message_url) {}
    virtual int cipher(string filename);
    virtual int usableTargetSize();
};

class encrypt_bmp:public encrypt {
    public:
    encrypt_bmp(string target_file_url, string message_url="-"):
        encrypt(target_file_url,message_url) {}
    virtual int cipher(string filename);
    virtual int usableTargetSize();
};

class decrypt {
public:
    string message;
    string encrypted_file;
    decrypt(string file_to_decrypt):
        encrypted_file(file_to_decrypt), message("") {}
    virtual void decipher() = 0;
    void write_message_to_file(string filename);
    string decoded_message();
    char make_byte(char enc, char c, int a);
};

class decrypt_wav: public decrypt {
    public:
        decrypt_wav(string file_to_decrypt):
            decrypt(file_to_decrypt) {}
        virtual void decipher();
};

class decrypt_bmp: public decrypt {
    public:
        decrypt_bmp(string file_to_decrypt):
            decrypt(file_to_decrypt) {}
        virtual void decipher();
};

#endif
