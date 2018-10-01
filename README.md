# trixlog
## PackageHandler
  Programa para empacotamento e desenpacotamento de dados.
 
## Protocolo 
Toda troca de mensagens entre o equipamento X e o sistema Y deve seguir as instruções
contidas neste documento.

### Caracteres reservados
Para a montagem de uma mensagem de comunicação válida, os seguintes caracteres devem
ser reservados:

- 0x01 - Início de pacote
- 0x04 - Fim de pacote
- 0x10 - Caractere de "Fuga"

Se um desses caracteres estiver contido entre o primeiro e o último byte da mensagem, eles
devem ser convertidos para o caractere 0x10 seguido do próprio caractere somado a 0x20(caractere
de mascaramento).

#### Exemplo
O caractere a ser transmitido é 0x01, como o mesmo é um caractere reservado apenas para o
início da mensagem, ele não pode se repetir na região de dados, por isso foi convertido para 0x10
seguido de 0x21(0x01 + 0x20).

### Checksum
Toda mensagem contém um caractere antes do fim do pacote (0x04) chamado checksum,
onde o mesmo é uma variável de tamanho 1 byte apenas, com a soma de todos os caracteres da
mensagem desde o caractere posterior ao início (0x01), até o caractere imediatamente anterior ao
checksum. 

Caso seu valor coincida com um dos caracteres reservados, também será convertido
conforme procedimento descrito anteriormente.

#### Exemplo
Checksum = 0x02+0x00+0x00+0x03+0x09+0x05+0x03+0x00+0x10+0x21+0x00 = 0x47

### Formato de uma mensagem
Todos as mensagens seguem a seguinte formação:

- Início do Pacote - 0x01
- Identificador do Periférico - código que identifica o periférico (1 byte). (utilizar o código 0xFF)
- Versão do Protocolo - número que identifica versão do protocolo (1 byte). (utilizar 0x00)
- Serial do Equipamento - número único do equipamento (2 bytes, obs.: byte menos significativo
primeiro). (escolher)
- Número da Mensagem - número sequencial que identifica a mensagem (2 bytes, obs.: byte
menos significativo primeiro).
- Tipo do Mensagem - identificação o tipo de mensagem (1 byte). (utilizar 0x09)
- Identificador do Tipo de Mensagem - identificação referente ao tipo de mensagem (1 byte).
(utilizar 0x80)
- Parâmetros da Mensagem - região de dados de parâmetro da mensagem (Tamanho Variável).
- Checksum - somatório de todos os caracteres da mensagem desde o caractere posterior ao
início do pacote, até o caractere imediatamente anterior ao checksum.
- Final do Pacote - 0x04

#### Exemplo
[0x01 0xFF 0x00 0x02 0x00 0x0A 0x00 0x09 0x80 0x68 0x65 0x6C 0x6C 0x6F 0x21
0xC9 0x04]

- 0x01 – início de pacote.
- 0xFF – identificado do periférico.
- 0x00 - versão do protocolo.
- 0x02 0x00 - serial do equipamento 00002.
- 0x0A 0x00 - mensagem número 00010.
- 0x09 – mensagem tipo "evento".
- 0x80 - mensagem de evento "mensagem de texto".
- 0x68 0x65 0x6C 0x6C 0x6F 0x21 - Dados* (mensagem -> "hello!").
- 0xC9 - checksum.
- 0x04 - final de pacote.

## Estruturas

### MessageHandler
Manipulador de mensagens recebe uma mensagem e transforma em um pacote seguindo o protocolo ou recebe o pacote completo e desempacota a mensagem contida.

#### checkScape(char)
Checa se um "char" é um caractere reservado e caso seja faz a manipulação necessária.

#### checkScape(vector<char>)
Checa se um conjunto de "char" possui caracteres reservados e caso exista faz a manipulação necessária.
  
#### checkScape(char, char, short, short, char, char, vector<char>)
Checa se o conjunto de estruturas da mensagem possui caracteres reservados e caso exista faz a manipulação necessária.

#### checksum(vector<char>)
Retorna o checksum do pacote.
  
#### checkSumError(vector<char>)
Retorna se houve erro no pacote.
  
#### removeStartAndEnd(vector<char>)
Remove os caracteres reservados de início e fim do pacote.
  
#### removeChecksumAndEscape(vector<char>)
Remove os caracteres reservados de escape e checksum do pacote.

#### removeEscape(vector<char>)
Remove os caracteres reservados de escape do pacote fazendo a manipulação necessária para retornar aos caracteres iniciais.

#### getMessage()
Retorna a mensagem do pacote.

#### getPackage()
Retorna o pacote completo.

#### getError()
Retorna se houve erro com o pacote.

### StreamHandler
Manipulador de de fluxo de dados recebe dados e retorna os pacotes completos recebidos até o momento.

#### flow(vector<char>)
Recebe fluxo de dados e retorna os pacotes completos recebidos até o momento.

### VectorHandler
Manipulador de vetor com funções úteis para manipulá-lo.

#### split(vector<char>, int, int)
Retorna um subVetor a partir de um index inicial até um final

#### concat(vector<char>, vector<char>)
Retorna um vetor a partir da união de outros dois. 
  
#### concat(vector<vector<char>>)
Retorna um vetor a partir da união de um vetor de vetores.   
  
#### print(vector<char>)
Imprime um vetor.     

#### printHex(vector<char>)
Imprime um vetor no formato hexadecimal.   
  
#### toVector(const char* a)
Transforma uma string em um vetor.

#### toVector(const char a)
Transforma um char em um vetor.
