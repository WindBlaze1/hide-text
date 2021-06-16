#include "rsa.h"

long long int log_power(long long int n, long long int p, long long int mod) {
    long long int result = 1;
    for (; p; p >>= 1)
    {
        if (p & 1)
            result = (1LL * result * n) % mod;
        n = (1LL * n * n) % mod;
    }
    return result;
}

bool rabin_miller(long long int n) {
    bool ok = true;

    for (long long int i = 1; i <= 5 && ok; i++) {
        long long int a = rand() + 1;
        long long int result = log_power(a, n - 1, n);
        ok &= (result == 1);
    }

    return ok;
}

long long int generate_prime() {
    long long int generated = rand() % LIMIT;
    while (!rabin_miller(generated))
        generated = rand() % LIMIT;
    return generated;
}

long long int gcd(long long int a, long long int b) {
    while (b)
    {
        long long int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long long int generate_coprime(long long int n) {
    long long int generated = rand() % LIMIT;
    while (gcd(n, generated) != 1)
        generated = rand() % LIMIT;
    return generated;
}

pair<long long int, long long int> euclid_extended(long long int a, long long int b) {
    if(!b) {
        return {1, 0};
    }

    auto result = euclid_extended(b, a % b);
    return { result.second, result.first - (a / b) * result.second };
}

long long int modular_inverse(long long int n, long long int mod) {
    long long int inverse = euclid_extended(n, mod).first;
    while(inverse < 0)
        inverse += mod;
    return inverse;
}

Keys generate_keys() {
    Keys result;

    long long int p, q;

    p = generate_prime();
    q = generate_prime();

    long long int n = p * q;
    long long int phi = (p -1) * (q - 1);
    long long int e = generate_coprime(phi);

    result.public_key =  make_pair(n, e);

    long long int d = modular_inverse(e, phi);

    result.private_key = make_pair(n, d);

    return result;
}

long long int rsa_encrypt(PublicKey key, long long int value) {
    return log_power(value, key.second, key.first);
}

long long int rsa_decrypt(PrivateKey key, long long int value) {
    return log_power(value, key.second, key.first);
}

string valid_loc(string s){
    string ret;
    for(size_t i(0); i<s.size(); i++){
        if(s[i]=='/')
            ret+="\\";
        else
            ret+=s[i];
    }
    return ret;
}

string rsa_dec(string file_name, long long int p1, long long int p2){
    file_name = valid_loc(file_name);
    ifstream file(file_name);
    string s;
    PrivateKey p(p1,p2);
    long long int c;
    while(file >> c){
        c = rsa_decrypt(p, c);
        s += c;
    }
    file.close();
    return s;
}

int rsa_enc(string file_name, string msg_file, long long int p1, long long int p2){
    file_name = valid_loc(file_name);
    msg_file = valid_loc(msg_file);
    ofstream wfile(file_name);
    ifstream rfile(msg_file);
    if(!wfile.is_open() && !rfile.is_open()){
        return 1;
        //file open error
    }
    char c;
    long long int l;
    PublicKey p(p1,p2);
    while(rfile >> noskipws >> c){
        l = rsa_encrypt(p, c);
        wfile << l << " ";
    }
    return 0;   //success
}
