#include <vector>
#include <array>
#include "../include/file_resolution.h"

using namespace std;

const vector<char> keyCH={'U','R','F','D','L','B',' ','\'','2'};

extern int servo_data[6][5];

bool in_table(char input,vector<char> table){
    for(int i=0;i<table.size();i++){
        if(table.data()[i]==input){
            return true;
        }
    }
    return false;
}

char get_usful_CH(FILE* fd){
    auto ch=(char)fgetc(fd);
    while (!in_table(ch,keyCH)){
        ch=(char)fgetc(fd);
    }
    return ch;
}

void give_back_sequence(const char* filepath,vector<array<int,2> >& servo){
    FILE* fd=fopen(filepath,"r");
    int ch;
    ch=get_usful_CH(fd);
    array<int,2> tmp={0,0};
    while(ch!=EOF && ch!='\n'){
        switch (ch){
            case 'U':tmp[0]=0;
                servo.push_back(tmp);
                break;
            case 'R':tmp[0]=1;
                servo.push_back(tmp);
                break;
            case 'F':tmp[0]=2;
                servo.push_back(tmp);
                break;
            case 'D':tmp[0]=3;
                servo.push_back(tmp);
                break;
            case 'L':tmp[0]=4;
                servo.push_back(tmp);
                break;
            case 'B':tmp[0]=5;
                servo.push_back(tmp);
                break;
            default:exit(1);
        }
        ch=get_usful_CH(fd);
        if(ch == ' '){
            servo.back().back()=90;
            ch=fgetc(fd);
            continue;
        }
        else{
            switch (ch){
                case '2':servo.back().back()=180;
                    break;
                case '\'':servo.back().back()=270;
                    break;
                default:exit(1);
            }
            fgetc(fd);
            ch=fgetc(fd);
        }
    }
}

void print_servo(std::vector<std::array<int,2> > servo){
    for(int i=0;i<servo.size();i++){
        printf("servo: %d  angle:%d \n",servo.at(i)[0],servo.at(i)[1]);
    }
}

void store_result(const char* file_path,array<char, BLOCKSIZE>& stickers){
    FILE* fd=fopen(file_path,"a");
    if(fd==NULL){
        printf("fail to open file.\n");
        exit(1);
    }
    for(auto s:stickers){
        char sticker=s;
        switch (sticker){
            case 'Y':sticker='D';
                break;
            case 'B':sticker='B';
                break;
            case 'O':sticker='L';
                break;
            case 'R':sticker='R';
                break;
            case 'W':sticker='U';
                break;
            case 'G':sticker='F';
                break;
            default:sticker='E';
        }
        fwrite(&sticker, sizeof(char),1,fd);
    }
    fclose(fd);
}

string read_file(const string file_path){
    string output;
    FILE* fp=fopen(file_path.c_str(),"r");
    output.clear();
    auto ch=(char)getc(fp);
    while(ch!= EOF && ch!= '\n'){
        output.push_back(ch);
        ch=(char)getc(fp);
    }
    return output;
}