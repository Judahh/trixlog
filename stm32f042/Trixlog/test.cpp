#include "test.h"

void Test::setup()
{
//  string received;
//  Serial.begin(57600);
//
//  printf("sizeof(char) = %d\n", sizeof(char));
//  printf("sizeof(short) = %d\n", sizeof(short));
}

void Test::loop()
{
  char* received;
  printf("Digite a mensagem para empacotamento:\n");
  scanf("%s", received);
  printf("Recebido %s \n", received);
  MessageHandler message(0xFF, 0x00, 2, 10, 0x09, 0x80, VectorHandler::toVector(received));
  printf("Pacote criado:");
  VectorHandler::print(message.getPackage());
  printf("\n");
  //printf("Pacote criado HEX:");
//  VectorHandler::printHex(message.getPackage());
//  printf("\n");
  //MessageHandler messageReceived(message.getPackage());
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
}