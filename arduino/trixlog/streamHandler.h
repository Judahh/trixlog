//#include "mbed.h"
//#include <vector>
#include <ArduinoSTL.h>
#include "vectorHandler.h"
// STREAMHANDLER.h
#ifndef STREAMHANDLER_H_
#define STREAMHANDLER_H_
using namespace std;
class StreamHandler
{

  private:
//    static const char START = 0x01;
//    static const char END = 0x04;
//    static const char ESCAPE = 0x10;
//    static const char ESCAPE_OFFSET = 0x20;
    vector<char> stream;

  public:
    StreamHandler();

    vector< vector<char> > flow(vector<char> stream);
};

#endif
