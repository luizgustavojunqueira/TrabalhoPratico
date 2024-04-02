#include "parser.h"

Parser::Parser(string input)
{
	scanner = new Scanner(input);
    advance();
}

void
Parser::run()
{
    goal();
}

void
Parser::advance()
{
	lToken = scanner->nextToken();

    //cout << lToken->name << endl;
}

void
Parser::match(int t)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else
		error("Erro inesperado");
}

void 
Parser::goal()
{
	expr();
}
//CONTINUAR
void
Parser::error(string str)
{
	cout << str << endl;

	exit(EXIT_FAILURE);
}