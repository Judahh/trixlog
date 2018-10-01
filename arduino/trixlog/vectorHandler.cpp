#include "vectorHandler.h"

//template <typename char>
vector<char> VectorHandler::split(vector<char> v, int startIndex, int endIndex)
{
    vector<char> vec(v.begin() + startIndex, v.begin() + endIndex + 1);
    return vec;
}

//template <typename char>
vector<char> VectorHandler::concat(vector<char> a, vector<char> b)
{
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

//template <typename char>
vector<char> VectorHandler::concat(vector< vector<char> > vectors)
{
    for (int index = 1; index < vectors.size(); index++)
    {
        vectors[0] = VectorHandler::concat(vectors[0], vectors[index]);
    }
    return vectors[0];
}

//template <typename char>
void VectorHandler::print(vector<char> a)
{
    for (int index = 0; index < a.size(); index++)
    {
//        cout << a[index];
        printf("%c", a[index]);
    }
}

void VectorHandler::printHex(vector<char> a)
{
    for (int index = 0; index < a.size(); index++)
    {
//        cout << a[index];
        printf("0x%X ", a[index]);
    }
}

vector<char> VectorHandler::toVector(const char* a){
    vector<char> v;
    for(int index = 0; a[index] != '\0'; index++){
        v.push_back(a[index]);
    }
    return v;
}

vector<char> VectorHandler::toVector(const char a){
    vector<char> v;
    v.push_back(a);
    return v;
}
