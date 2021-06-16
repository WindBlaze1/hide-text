#ifndef __RSA_H
#define __RSA_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <string>
#include <iomanip>
#define LIMIT 1000000

using namespace std;

typedef pair<long long int, long long int> PublicKey;
typedef pair<long long int, long long int> PrivateKey;

struct Keys {
    PublicKey public_key;
    PrivateKey private_key;
};

Keys generate_keys();

string valid_loc(string s);

int rsa_enc(string file_name, string msg_file, long long int p1, long long int p2);

string rsa_dec(string file_name, long long int p1, long long int p2);

long long int log_power(long long int n, long long int p, long long int mod);

bool rabin_miller(long long int n);

long long int generate_prime();

long long int gcd(long long int a, long long int b);

long long int generate_coprime(long long int n);

pair<long long int, long long int> euclid_extended(long long int a, long long int b);

long long int modular_inverse(long long int n, long long int mod);

long long int rsa_decrypt(PrivateKey key, long long int value);

long long int rsa_encrypt(PrivateKey key, long long int value);

#endif  // __RSA_H
