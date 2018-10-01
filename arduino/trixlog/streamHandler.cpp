#include "streamHandler.h"

#define START 0x01
#define END 0x04
#define ESCAPE 0x10
#define ESCAPE_OFFSET 0x20

StreamHandler::StreamHandler()
{
    //   this->stream = {};
}

vector< vector<char> > StreamHandler::flow(vector<char> stream)
{
    int start = -1;
    int end = -1;
    vector< vector<char> > packages;
    stream = VectorHandler::concat(this->stream, stream); //concat
    for (int index = 0; index < stream.size(); index++)
    {
        char element = stream[index];
        bool nextEnd = false;

        if (element == START || element == END)
        {
            if (index + 1 < stream.size())
            {
                char nextElement = stream[index + 1];
                nextEnd = (nextElement == END);
            }

            if (element == START)
            {
                if (nextEnd)
                {
                }
                else
                {
                    start = index;
                    end = -1;
                }
            }

            if (element == END)
            {
                if (nextEnd)
                {
                }
                else if (start != -1)
                {
                    end = index;
//                    vector<char> package = VectorHandler::split(stream, start, index);
                    packages.push_back(VectorHandler::split(stream, start, index));
                }
            }
        }
    }

    if (start != -1 && end == -1)
    {
        this->stream = VectorHandler::split(stream, start, stream.size() - 1);
    }

    return packages;
}
