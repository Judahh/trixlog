#include "mbed.h"
#include <vector>
#include "vectorHandler.h"
// MESSAGEHANDLER.h
#ifndef MESSAGEHANDLER_H_
#define MESSAGEHANDLER_H_
//using namespace std;
class MessageHandler
{

  private:
//    static const char START = 0x01;
//    static const char END = 0x04;
//    static const char ESCAPE = 0x10;
//    static const char ESCAPE_OFFSET = 0x20;

    char peripheral;
    char protocol;
    short serialKey;
    short number;
    char type;
    char typeId;
    vector<char> message;
    vector<char> package;
    bool error;

  public:
    MessageHandler(vector<char> received);
    MessageHandler(char peripheral, char protocol, short serialKey, short number, char type, char typeId, vector<char> message);

    vector<char> checkScape(char element);

    vector<char> checkScape(char peripheral, char protocol, short serialKey, short number, char type, char typeId, vector<char> message);

    vector<char> checkScape(vector<char> package);

    char checksum(vector<char> package);

    bool checkSumError(vector<char> package);

    vector<char> removeStartAndEnd(vector<char> package);

    vector<char> removeChecksumAndEscape(vector<char> package);

    vector<char> removeEscape(vector<char> package);

    vector<char> getMessage();

    vector<char> getPackage();

    bool getError();
};

#endif