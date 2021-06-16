#include "crypgraphy.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

//cipher class functions:
Cipher::Cipher(std::string inp_path, std::string out_path)
    : input_path(inp_path), output_path(out_path) {}


caesar_c::caesar_c(std::string inp_path, std::string out_path, int x)
    : Cipher(inp_path, out_path), shift(x) {}


//caeasar class functions:
std::string caesar_c :: encrypt(std::string word) {
    std::string result = "";

    for (size_t i = 0; i < word.size(); i++) {
        if (isupper(word[i]))
            result += char(int(word[i] + shift%26 - 65)%26 + 65);
        else
            result += char(int(word[i] + shift%26 - 97)%26 + 97);
    }

    return result;
}

std::string caesar_c :: decrypt(std::string word) {
    std::string result = "";

    for (size_t i = 0; i < word.length(); i++) {
        if (isupper(word[i])) {
            if (word[i] - shift%26 - 65 < 0)
                result += char(26 - (shift%26 - (word[i] - 65)) + 65);
            else
                result += char(word[i] - shift%26);
        }
        else {
            if (word[i] - shift%26 - 97 < 0)
                result += char(26 - (shift%26 - (word[i] - 97)) + 97);
            else
                result += char(word[i] - shift%26);
        }
        // cout << (int)word[i] << " -> " << (int)result[i] << endl;
    }

    return result;
}

//choice = 0 -> means encrypt whole file
//choice = 1 -> means decrypt whole file
int caesar_c :: read_and_write(bool choice) {
    std::string word, changed;
    std::ifstream inp_file;
    std::ofstream out_file;
    inp_file.open(input_path.c_str());
    out_file.open(output_path.c_str());

    if(!inp_file.is_open() && !out_file.is_open()){
        return 1;  //File open error
    }

    while (inp_file >> word) {
        if (choice == 0)
            changed = encrypt(word);
        else
            changed = decrypt(word);
        out_file << changed << ' ';
        out_file.flush();
    }
    return 0;
}


//vigenere_v class functions:
vigenere_v::vigenere_v(std::string inp_path, std::string out_path, std::string k)
    : Cipher(inp_path, out_path), key(k) {}

//Function to extend the key to the length of plaintext
//case of key doesn't matter
//case of all letters in word will be preserved
std::string vigenere_v :: get_full_key(std::string word, std::string k){
    std::string temp_word = word;
    std::string temp_k = k;
    //to change the strings to lower case
    transform(temp_word.begin(), temp_word.end(), temp_word.begin(), ::tolower);
    transform(temp_k.begin(), temp_k.end(), temp_k.begin(), ::tolower);

    int x = word.size() % k.size();
    int n = word.size() / k.size();

    std::string final_key = "";
    for (int i = 1; i <= n; i++) {
        final_key += temp_k;
    }
    final_key += temp_k.substr(0, x);

    for (int i = 0; i < word.size(); i++) {
        if (isupper(word[i]))
            final_key[i] -= 32;
    }
    return final_key;
}

std::string vigenere_v :: encrypt(std::string word) {
    std::string temp_key = get_full_key(word, key);
    std::string enc_word = "";

    for(int i = 0; i < word.size(); i++) {
        if (isupper(word[i]))
            enc_word += (char) (((int)word[i]-'A' + (int)temp_key[i]-'A') % 26) + 'A';
        else
            enc_word += (char) (((int)word[i]-'a' + (int)temp_key[i]-'a') % 26) + 'a';
    }

    return enc_word;
}

std::string vigenere_v :: decrypt(std::string word) {
    std::string temp_key = get_full_key(word, key);
    std::string dec_word = "";

    for(size_t i = 0; i < word.size(); i++) {
        if (isupper(word[i]))
            dec_word += (char) ((((int)word[i]-'A' - ((int)temp_key[i]-'A')) + 26) % 26) + 'A';
        else
            dec_word += (char) ((((int)word[i]-'a' - ((int)temp_key[i]-'a')) + 26) % 26) + 'a';
    }
    return dec_word;
}

//choice = 0 -> means encrypt whole file
//choice = 1 -> means decrypt whole file
int vigenere_v :: read_and_write(bool choice) {
    std::string word, changed;
    std::ifstream inp_file;
    std::ofstream out_file;
    inp_file.open(input_path.c_str());
    out_file.open(output_path.c_str());
    if(!inp_file.is_open() && !out_file.is_open()){
        return 1;  //File open error
    }

    while (inp_file >> word) {
        if (choice == 0)
            changed = encrypt(word);
        else
            changed = decrypt(word);
        out_file << changed << ' ';
        out_file.flush();
    }
    return 0;
}

std::string make_locc(std::string s){
    std::string ret;
    for(size_t i(0); i<s.size(); i++){
        if(s[i]=='/')
            ret+="\\";
        else
            ret+=s[i];
    }
    return ret;
}

int for_encrypt(std::string inp_path, std::string out_path, std::string key, int choice){
    inp_path = make_locc(inp_path);
    out_path = make_locc(out_path);
    //caesar_c
    if(choice == 1){
        int c(stoi(key));
        caesar_c cr(inp_path, out_path, c);
        return cr.read_and_write(0);    //encrypt
    }
    if(choice == 2){
        vigenere_v v(inp_path, out_path, key);
        return v.read_and_write(0);
    }
}

std::string for_decrypt(std::string input, std::string key, int choice, std::string out="1.txt"){
    input = make_locc(input);
    out = make_locc(out);
    //caesar_c
    if(choice == 1){
//        int c(stoi(key));
        int c;
        std::stringstream ss(key);
        ss >> c;
//        std::cerr<<c;
        std::string s(""); char t;
        caesar_c cr(input,out,c);
        cr.read_and_write(1);    //decrypt
        std::ifstream f(out);
        while(f >> std::noskipws >> t)
            s+=t;
        f.close();
        remove(out.c_str());
        return s;
    }
    //vigenere_v
    if(choice == 2){
        std::string s; char t;
        vigenere_v v(input, out, key);
        v.read_and_write(1);    //decrypt
        std::ifstream f("1.txt");
        while(f >> std::noskipws >> t)
            s+=t;
        f.close();
        remove(out.c_str());
        return s;
    }
}
