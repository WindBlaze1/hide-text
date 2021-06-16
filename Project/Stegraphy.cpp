#include"stegraphy.h"


int encrypt::messageSize() {
    int c(0);char t;
    ifstream msg(msg_url,ios::in);
    while(!msg.eof()){
        c++;
        msg>>noskipws>>t;       //so as to count \n and \t
    }
    return c;
}
bool encrypt::isSizeEnough() {
    if(messageSize() <= usableTargetSize())
        return true;
    return false;
}
char encrypt::inject_bit(char* target_byte, char message, int bit_count) {
    char r(message),t(target_byte[0]);
    r=r>>bit_count;
    if(r & 1)
        t |= 1;
    else
        t &= ~1;
    return t;
}

int encrypt_wav::usableTargetSize() {
    int size(0);
    ifstream file(file_url,ios::binary|ios::in);
    file.seekg(44);
    char c;
    while(!file.eof()) {
        size++;
        file>>c;
    }
    size/=8;                       //one byte stored in LSBs of 8 bytes
    return size/(SKIP+1);          //see the encryption
}


int encrypt_bmp::usableTargetSize() {
    bytecimg target(file_url.c_str());
    bytecimg::iterator it = target.begin();
    long c(0);
    while(it!=target.end()){
        it++;c++;
    }
    return c;       // In bytes...
}

int encrypt_bmp::cipher(string filename="copy") {
    bytecimg target(file_url.c_str());
    ifstream m(msg_url, ios::in);
    if(!m.is_open()){
        return 1; // File open error
    }
    bytecimg::iterator it = target.begin();
    string msg;
    char c;
    while(m>>noskipws>>c){
        msg+=c;
    }
    msg+=(unsigned char)26;
    int k(0);
    while(1){
        if(k>=msg.size()-1){
            break;
        }
        c = msg[k++];
        for(int i(0); i<8; i++){
            if(c>>i & 1){
                *it = *it | 1;
            }
            else{
                *it = *it & ~1;
            }
            it++;
        }
        if(it == target.end()){
            // File size error
            return 2;
        }
    }
    // filename+=".bmp";
    target.save(filename.c_str());
    return 0;
}

int encrypt_wav::cipher(string filename="copy") {
    ifstream target(file_url,ios::binary|ios::in);
    ifstream message(msg_url,ios::in);
    // filename += ".wav";
    ofstream encrypted(filename,ios::binary|ios::out);
    char t[40],c,temp[8];
    string m("");
    if(!target.is_open() && !message.is_open() && !encrypted.is_open())
    {
        return 1;   //Run as administrator
    }

    //read the whole message and store it in a string
    while(message >> noskipws >> c){
        m += c;
    }
    m+='\0';
    message.close();
    //cerr<<m<<endl;

    //deal with header
    target.read(t,40);
    encrypted.write(t,40);
    target.read(t,4);
    encrypted.write(t,4);
    //cout<<target.tellg();
    int size_target,k(0),size_message(m.size());
    //memcpy(&size_target,t,sizeof(int));
    //cerr<<"\nSize of target: "<<size_target<<" Bytes\nMessage size: "<<size_message<<" Bytes\n";
    // cout<<"\nEncryption in progress...";


    //Start encoding by inserting 1 byte of message in 8 bytes(LSB(s)) of target
    //and writing the resultant byte on encrypted file.
    //Assumption: Target size is big enough to insert every message byte.
    while(!target.eof()) {
        c=m[k++];                           //1 byte of message stored in char
        for(int i(0); i<8; i++){            //read 8 bytes of target for 1 byte of message
            target.read(t,SKIP);
            encrypted.write(t,SKIP);        //skip k bytes for better data hiding and for no loss in audio quality
            target.read(t,1);
            t[0] = inject_bit(t,c,7-i);     //returns an edited byte and stores it
            encrypted.write(t,1);
        }

        if(k>=size_message)
            break;
    }

    if(target.eof() && k < m.size()){
        remove(filename.c_str());
        return 2;       //File size error
    }

    //store the remaining file
    while(!target.eof()) {
        target.read(t,1);
        encrypted.write(t,1);
    }
    target.close();
    encrypted.close();
    // cout<<"\nDone.";
    return 0;
}

void decrypt::write_message_to_file(string filename="message_from_") {
    filename += encrypted_file + ".txt";
    cout<<"\nSaving...";
    ofstream fout(filename);
    int k(0);
    while(k<message.size()) {
        fout<<noskipws<<message[k++];
    }
    cout<<"\nSaved.";
}
string decrypt::decoded_message() {
    return message;
}
char decrypt::make_byte(char enc, char c, int a) {
    if(a<7)
    {
    if(enc & 1){
        c |= 1;
        c = c<<1;
    }
    else
        c = c<<1;
    }
    else{
        if(enc & 1)
            c |= 1;
    }
    return c;
}



void decrypt_wav::decipher() {
    ifstream encrypted(encrypted_file, ios::binary|ios::in);

    //skip the header
    encrypted.seekg(44);

    cout<<"\nDecrypting...";
    char c(0),temp[6];
    while(1) {
        c=0;
        //cout<<"Here";
        for(int i(0); i<8; i++) {
            //cout<<encrypted.tellg()<<endl;
            encrypted.read(temp,SKIP);         //skip 'K' just like before
            encrypted.read(temp,1);
            c = make_byte(temp[0], c, i);
        }
        if(encrypted.eof() || c=='\0')
            break;
        message += c;

    }
    encrypted.close();
    // cout<<"\nDone.";
}

void decrypt_bmp::decipher(){
    bytecimg encoded(encrypted_file.c_str());
    unsigned char c(0);
    int bit(0);
    for (bytecimg::iterator it = encoded.begin(); it != encoded.end() && c!=(unsigned char)26; ++bit, ++it) {
        c |= (*it & 1) << bit;
            if (bit == 7) {
                message += c;
                bit = -1;
                c = 0;
            }
    }
}

string make_loc(string s){
    string ret;
    for(int i(0); i<s.size(); i++){
        if(s[i]=='/')
            ret+="\\";
        else
            ret+=s[i];
    }
    return ret;
}

int for_encode(string target_loc, string msg_loc, string save_loc, int type){
    target_loc = make_loc(target_loc);
    msg_loc = make_loc(msg_loc);
    save_loc = make_loc(save_loc);
    //For Sound File
    if(type == 1){
        encrypt_wav enc(target_loc,msg_loc);
        return enc.cipher(save_loc);
    }
    //For Image File
    if(type == 2){
        encrypt_bmp bm(target_loc,msg_loc);
        return bm.cipher(save_loc);
    }
}

string for_decode(string file_loc){
    file_loc = make_loc(file_loc);
    if(file_loc.substr(file_loc.size()-3,file_loc.size()) == "bmp"){
        decrypt_bmp bm(file_loc);
        bm.decipher();
        return bm.decoded_message();
    }
    else{
        decrypt_wav enc(file_loc);
        enc.decipher();
        return enc.decoded_message();
    }
}
