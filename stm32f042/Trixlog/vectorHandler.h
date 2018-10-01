#include "mbed.h"
#include <vector>
//#include <string>

// VECTORHANDLER.h
#ifndef VECTORHANDLER_H_
#define VECTORHANDLER_H_
//using namespace std;
// template <typename char>
class VectorHandler
{
  public:
//    template <typename char>
    static vector<char> split(vector<char> v, int startIndex, int endIndex);

//    template <typename char>
    static vector<char> concat(vector<char> a, vector<char> b);

//    template <typename char>
    static vector<char> concat(vector< vector<char> > vectors);

//    template <typename char>
    static void print(vector<char> a);

    static void printHex(vector<char> a);
    
    static vector<char> toVector(const char* a);
    
    static vector<char> toVector(const char a);
};

#endif