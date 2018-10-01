#include "messageHandler.h"

#define START 0x01
#define END 0x04
#define ESCAPE 0x10
#define ESCAPE_OFFSET 0x20

MessageHandler::MessageHandler(vector<char> received)
{
    this->error = false;
    this->package = received;
    vector<char> package = this->removeStartAndEnd(received);
    this->checkSumError(package);
    package = this->removeChecksumAndEscape(package);
//    cout << "removeEscape:\n";
//    VectorHandler::printHex(package);
//    cout << "\n";
    this->peripheral = package[0];
    this->protocol = package[1];
    this->serialKey = (package[2] & 0xFF) + (((package[3] & 0xFF) << 8) & 0xFF00); //concat ----
    this->number = (package[4] & 0xFF) + (((package[5] & 0xFF) << 8) & 0xFF00);    //concat -------
    this->type = package[6];
    this->typeId = package[7];
    this->message = VectorHandler::split(package, 8, package.size() - 1);
//    cout << "message:\n";
//    VectorHandler::printHex(this->message);
//    cout << "\n";
}

MessageHandler::MessageHandler(char peripheral, char protocol, short serialKey, short number, char type, char typeId, vector<char> message)
{
    this->error = false;
    this->peripheral = peripheral;
    this->protocol = protocol;
    this->serialKey = serialKey;
    this->number = number;
    this->type = type;
    this->typeId = typeId;
    this->message = message;
    // cout << "message A:\n";
    // VectorHandler::print(message);
    // cout << "\n";
    this->package = this->checkScape(peripheral, protocol, serialKey, number, type, typeId, message);
    // cout << "this->package A:\n";
    // VectorHandler::print(this->package);
    // cout << "\n";
//    VectorHandler::printHex(this->package);
//    cout << "\n";

    vector< vector<char> > newVector;
//    vector<char> tempVector; 
//    tempVector.push_back((char)START));
    newVector.push_back(VectorHandler::toVector((char)START));
    newVector.push_back(this->package);
    //vector<char> tempVector2; 
//    tempVector2.push_back(this->checksum(this->package));
    newVector.push_back(VectorHandler::toVector(this->checksum(this->package)));
    //vector<char> tempVector3; 
//    tempVector3.push_back((char)END);
    newVector.push_back(VectorHandler::toVector((char)END));

    this->package = VectorHandler::concat(newVector);
    // cout << "this->package A2:\n";
    // VectorHandler::print(this->package);
    // cout << "\n";
}

vector<char> MessageHandler::checkScape(char element)
{
    vector<char> newElement;
    if (element == START || element == END || element == ESCAPE)
    {
        char temp = (element + (char)ESCAPE_OFFSET);
        char temp2 = (char)ESCAPE;
        newElement.push_back(temp2);
        newElement.push_back(temp);
        // cout << "S\n";
    }
    else
    {
        newElement.push_back(element);
        // cout << "Z\n";
    }
    // cout << "newElement A:\n";
    // VectorHandler::print(newElement);
    // cout << "\n";
    // VectorHandler::printHex(newElement);
    // cout << "\n";
    return newElement;
}

vector<char> MessageHandler::checkScape(vector<char> packagePart)
{
    vector<char> newPackage = packagePart;
    for (int index = 0; index < newPackage.size(); index++)
    {
        char element = newPackage[index];

        vector<char> newElement = this->checkScape(element);

        vector< vector<char> > newVector;
        newVector.push_back(VectorHandler::split(newPackage, 0, index - 1));
        newVector.push_back(newElement);
        newVector.push_back(VectorHandler::split(newPackage, index + 1, (newPackage.size() - 1)));
        newPackage = VectorHandler::concat(newVector);

        index = index + newElement.size() - 1;
    }
//    printf("newPackage #%s# \n", newPackage);
    // cout << "newPackage A:\n";
    // VectorHandler::print(newPackage);
    // cout << "\n";
    return newPackage;
}

vector<char> MessageHandler::checkScape(char peripheral, char protocol, short serialKey, short number, char type, char typeId, vector<char> message)
{
    char sk0 = (char)serialKey & 0xFF;
    char sk1 = (char)serialKey >> 8;
    char n0 = (char)number & 0xFF;
    char n1 = (char)number >> 8;
//    vector<char> sk0T =  this->checkScape(sk0);
    
    // cout << "checkScape(sk0):\n";
    // VectorHandler::print(sk0T);
    // cout << "\n";
//    printf("this->checkScape(sk0) #%s# \n", this->checkScape(sk0));

    vector< vector<char> > newVector;
    newVector.push_back(this->checkScape(peripheral));
    newVector.push_back(this->checkScape(protocol));
    newVector.push_back(this->checkScape(sk0));
    newVector.push_back(this->checkScape(sk1));
    newVector.push_back(this->checkScape(n0));
    newVector.push_back(this->checkScape(n1));
    newVector.push_back(this->checkScape(type));
    newVector.push_back(this->checkScape(typeId));
    newVector.push_back(this->checkScape(message));
    vector<char> newPackage = VectorHandler::concat(newVector);

//    printf("package M #%s# \n", newPackage);
    // cout << "newPackage M:\n";
    // VectorHandler::print(newPackage);
    // cout << "\n";
    //    char test = 0x00;
    //    vector<char> sPackage2 =  vector<char>() + test;
    //    sPackage2 = sPackage2 + "asdas" + "FGJ";
    //    printf("package2 #%s# \n", sPackage2.c_str());

    //   vector<char> s = "Hello";
    //   vector<char> greet = s + " World"; //concatenation easy!
    //
    //   printf("package T %s \n", greet.c_str());

    return newPackage;
}

char MessageHandler::checksum(vector<char> packageCS)
{
    char sum = 0;
    for (int index = 0; index < packageCS.size(); index++)
    {
        char element = packageCS[index];
        sum += element; // regular sum
//        printf("0x%X ",element);
    }
//    printf("\n0x%X\n",sum);
    return sum;
}

bool MessageHandler::checkSumError(vector<char> packageCS)
{
    char last = packageCS[packageCS.size() - 1];
    packageCS = VectorHandler::split(packageCS, 0, packageCS.size() - (1 + 1));
    char current = this->checksum(packageCS);
    this->error = (current != last);
//    cout << "CHECKSUM\n";
//    printf("0x%X\n",current);
//    printf("0x%X\n",last);
    return this->error;
}

vector<char> MessageHandler::removeStartAndEnd(vector<char> packageS)
{
    return VectorHandler::split(packageS, 1, packageS.size() - (1 + 1));
}

vector<char> MessageHandler::removeChecksumAndEscape(vector<char> packageE)
{
    packageE = VectorHandler::split(packageE, 0, packageE.size() - (1 + 1));
    packageE = this->removeEscape(packageE);
    return packageE;
}

vector<char> MessageHandler::removeEscape(vector<char> packageE)
{
//    cout << "removeEscape 1:\n";
//    VectorHandler::printHex(packageE);
//    cout << "\n";
    for (int index = 0; index < packageE.size(); index++)
    {
        char element = packageE[index];
        if (element == ESCAPE)
        {
            if (index + 1 < packageE.size())
            {
                char nextElement = packageE[index + 1] - ESCAPE_OFFSET; //remove offset
                packageE[index] = nextElement;
                if (index + 2 < packageE.size())
                {
                    packageE = VectorHandler::concat(
                        VectorHandler::split(packageE, 0, index),
                        VectorHandler::split(packageE, index + 2, packageE.size() - 1)
                    );
                }
                else
                {
                    packageE = VectorHandler::split(packageE, 0, index);
                }
            }
            else
            {
                printf("ERROR ESCAPE\n");
                this->error = true;
                return packageE;
            }
        }
    }
//    cout << "removeEscape 2:\n";
//    VectorHandler::printHex(packageE);
//    cout << "\n";
    return packageE;
}

vector<char> MessageHandler::getMessage()
{
    return this->message;
}

vector<char> MessageHandler::getPackage()
{
    return this->package;
}

bool MessageHandler::getError()
{
    return this->error;
}
