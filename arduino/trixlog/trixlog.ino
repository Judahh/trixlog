//#include "test.h" 
#include "streamHandler.h"
#include "messageHandler.h"
#include "vectorHandler.h"

StreamHandler streamHandler;

void setup()
{
//  string received;
  Serial.begin(57600);
//
//  printf("sizeof(char) = %d\n", sizeof(char));
//  printf("sizeof(short) = %d\n", sizeof(short));
}

//void loop()
//{
////  char* received;
//  string received;
//  printf("Digite a mensagem para empacotamento:\n");
////  scanf("%s", received);
//  cin >> received;
//  printf("Recebido %s \n", received);
//  MessageHandler message(0xFF, 0x00, 2, 10, 0x09, 0x80, received);//VectorHandler::toVector(received));
//  printf("Pacote criado:");
//  VectorHandler::print(message.getPackage());
//  printf("\n");
//  printf("Pacote criado HEX:");
//  VectorHandler::printHex(message.getPackage());
//  printf("\n");
//  MessageHandler messageReceived(message.getPackage());
//  printf("Mensagem recriada:");
//  VectorHandler::print(messageReceived.getMessage());
//  printf("\n");
//  printf("Mensagem recriada Hex:");
//  VectorHandler::printHex(messageReceived.getMessage());
//  printf("\n");
//  
//  vector<char> v;
//  v.push_back(0x01);
//  v.push_back(0xFF);
//  v.push_back(0x00);
//  v.push_back(0x02);
//  v.push_back(0x00);
//  v.push_back(0x0A);
//  v.push_back(0x00);
//  v.push_back(0x09);
//  v.push_back(0x80);
//  v.push_back(0x68);
//  v.push_back(0x65);
//  v.push_back(0x6C);
//  v.push_back(0x6C);
//  v.push_back(0x6F);
//  v.push_back(0x21);
//  v.push_back(0xC9);
//  v.push_back(0x04);
//  MessageHandler messageTest(v);
//  printf("Mensagem TEST recriada:");
//  VectorHandler::print(messageTest.getMessage());
//  printf("\n");
//  printf("Mensagem TEST recriada Hex:");
//  VectorHandler::printHex(messageTest.getMessage());
//  printf("\n");
//  if(messageTest.getError()){
//      printf("Error!");
//      printf("\n");
//  }
//}

void dataPrint(vector<vector<char>> data)
{
  printf("Checa se Pacote foi formado!");
  printf("\n");
  for(int index = 0; index < data.size(); index++){
        MessageHandler message(data[index]);
        printf("Mensagem recriada:");
        VectorHandler::print(message.getMessage());
        printf("\n");
        printf("Pacote:");
        VectorHandler::print(message.getPackage());
        printf("\n");
        printf("Pacote Hex:");
        VectorHandler::printHex(message.getPackage());
        printf("\n");
        if(message.getError()){
            printf("Error!");
            printf("\n");
        }
  }
}

void loop()
{
  vector<char> v;
  v.push_back(0x01);//start
  v.push_back(0xFF);
  v.push_back(0x00);
  v.push_back(0x02);
  v.push_back(0x00);
  v.push_back(0x0A);
  v.push_back(0x00);
  v.push_back(0x09);
  v.push_back(0x80);
  vector<vector<char>> data = streamHandler.flow(v);
  dataPrint(data);
  string received;
  printf("Digite a mensagem para empacotamento:\n");
//  scanf("%s", received);
  cin >> received;
  printf("Recebido %s \n", received);

  data = streamHandler.flow(received);
  dataPrint(data);
  vector<char> v2;
  v2.push_back(0xC9);//checksum
  v2.push_back(0x04);//end
  data = streamHandler.flow(v2);
  dataPrint(data);
}
