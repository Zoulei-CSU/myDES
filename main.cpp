#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>

#include "progress.hpp"
#include "des.h"

using namespace std;

#define BUFFER_SIZE 4096
static unsigned char s_buffer_in[BUFFER_SIZE + 8];
static unsigned char s_buffer_out[BUFFER_SIZE + 8];
static bool s_showMessage = true;

int encrypt_decrypt(string key, string input, string output, int isDecrypt)
{
    ifstream ifile;
    ofstream ofile;

    if(input.length()  < 1) input  = "/dev/stdin";
    if(output.length() < 1) output = "/dev/stdout";

    if(s_showMessage){
        if(!isDecrypt)
            cout << "Encryption." << endl;
        else
            cout << "Decryption." << endl;
        cout << "Input file:" << input.c_str() << endl;
        cout << "Output file:" << output.c_str() << endl;
    }


    ifile.open(input,  ios::binary | ios::in | ios::ate);
    ofile.open(output, ios::binary | ios::out);

    if(!(ifile.is_open() && ofile.is_open()))
    {
        if(s_showMessage)
            cout << "Cannot open file!" << endl;
        return -1;
    }

    uint64_t size = ifile.tellg();
    ifile.seekg(0, ios::beg);

    DES myDes;

    if(s_showMessage)
        cout << "Input file size:" << size << endl;

    uint64_t size_org = size;

    static char magic[9] = {'S', 'G', 'D', 'E', 28, 30, 'S', 'P', '\0'};
    if(!isDecrypt) { //加密
        ofile.write(static_cast<char *>(magic), 8);
        void *p = &size;
        ofile.write(static_cast<char *>(p), 8);
        if(s_showMessage)
            cout << "Output file size:" << 16 + (size / 8 +1) * 8 << endl;
    }else { //解密
        ifile.read((char*)s_buffer_in, 8);
        s_buffer_in[8] = '\0';
        if(strcmp((const char*)s_buffer_in, magic) != 0){
            if(s_showMessage)
                cout << "Input file is not an encrypted file." << endl;
            ifile.close();
            ofile.close();
            return -2;
        }

        void *p = &size_org;
        ifile.read((char*)p, 8);
        if(s_showMessage)
            cout << "Original file size:" << size_org << endl;
    }

    boost::progress_display *pd = nullptr;
    if(s_showMessage)
        pd = new boost::progress_display(size);

    uint64_t current = 0;
    do {
        if(current + BUFFER_SIZE > size)
        {
            uint64_t len = size - current;
            ifile.read((char*)s_buffer_in, len);
            myDes.CDesEnter(s_buffer_in , s_buffer_out, (len / 8 +1) * 8, (const unsigned char*)key.c_str(), isDecrypt);

            if(!isDecrypt)
                ofile.write((char*)s_buffer_out, (len / 8 +1) * 8);
            else
                ofile.write((char*)s_buffer_out, size_org - current);//解密

            if(s_showMessage)
                *pd += len;
            break;
        }
        else
        {
            ifile.read((char*)s_buffer_in, BUFFER_SIZE);
            myDes.CDesEnter(s_buffer_in , s_buffer_out, BUFFER_SIZE, (const unsigned char*)key.c_str(), isDecrypt);
            ofile.write((char*)s_buffer_out, BUFFER_SIZE);
            current += BUFFER_SIZE;
            if(s_showMessage)
                *pd += BUFFER_SIZE;
            //cout << current << " / " << size << endl;
        }
    }while(true);


    if(pd != nullptr)
        delete pd;

    if(s_showMessage)
        cout << "Done!" << endl;

    ifile.close();
    ofile.close();

    return 0;
}

void usage()
{
    cout << "Usage: myDES -e/-d key [input-file] [output-file] [-s]" << endl;
    cout << "\t The key must be 8 bits." << endl;
    cout << "\t -e: Encryption \t-d: Decryption." << endl;
    cout << "\t -s: Keep quiet and do not output any information." << endl << endl;
    cout << "Example: myDES -e ABCDEFGH input.txt output.txt.des -s" << endl;
    cout << "\t myDES -d ABCDEFGH output.txt.des output.txt" << endl;
}

int main(int argc, char **argv)
{

    if(argc < 5)
    {
        usage();
        return 1;
    }

    string enc_dec = argv[1];
    if(enc_dec != "-e" && enc_dec != "-d")
    {
        usage();
        return 2;
    }

    string key = argv[2];
    if(key.size() != 8)
    {
        usage();
        return 2;
    }

    string input,output;
    if(argc > 3)
        input  = argv[3];
    if(argc > 4)
        output = argv[4];

    if(argc > 5)
    {
        string s = argv[5];
        if(s == "-s")
            s_showMessage = false;
    }


    assert(sizeof(uint64_t) == 8);

//    string key = "8654321";
//    string enc_dec = "-e";
//    string input = "E:\\MyGitRepo\\myDES\\pgAdmin3.7z";
//    string output = "E:\\MyGitRepo\\myDES\\pgAdmin3.7z.des";
//    string enc_dec = "-d";
//    string input = "E:\\MyGitRepo\\myDES\\pgAdmin3.7z.des";
//    string output = "E:\\MyGitRepo\\myDES\\pgAdmin3.7z.des.7z";

    if(enc_dec == "-e")
        return encrypt_decrypt(key, input, output, 0);
    if(enc_dec == "-d")
        return encrypt_decrypt(key, input, output, 1);

    return 0;
}
