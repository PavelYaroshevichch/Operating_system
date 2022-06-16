#pragma once
#ifndef RECEIVER_MESSAGE_H
#define RECEIVER_MESSAGE_H
#include<iostream>
#include<fstream>
#include<Windows.h>

using namespace std;

wstring ConvertIntegerNumberToWstring(int number);

struct Message {
    Message() {}

    Message(string str) {
        strcpy(message, str.c_str());
    }

    char* GetMes(){
        return message;
    }

    friend fstream& operator <<(fstream& file, const Message& msg) {
        file.write((const char*)& msg, sizeof(struct Message));
        return file;
    }

    friend fstream& operator >>(fstream& file, Message& msg) {
        file.read((char*)& msg, sizeof(struct Message));
        return file;
    }

private:
    char message[20];
};

wstring ConvertIntegerNumberToWstring(int number) {
    wchar_t* buf = new wchar_t[20];
    swprintf(buf, 20, L"%d", number);
    return (wstring)buf;
}
#endif //RECEIVER_MESSAGE_H