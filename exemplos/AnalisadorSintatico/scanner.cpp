#include "scanner.h"    

//Construtor
Scanner::Scanner(string input)
{
    this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: " 
         << input.length() << endl;
    pos = 0;
}

//Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{
    //TODO
}//Fim nextToken

void 
Scanner::lexicalError()
{
    cout << "Token mal formado\n";
    
    exit(EXIT_FAILURE);
}
