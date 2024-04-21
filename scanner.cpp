#include "scanner.h"
#include <vector>
#include <algorithm>

vector<string> reserved_words = {"boolean", "class", "else", "extends", "false", "if",
                                 "int", "length", "main", "new", "public", "return",
                                 "static", "String", "System.out.println", "this", "true",
                                 "void", "while"};

// Construtor que recebe uma string com o nome do arquivo
// de entrada e preenche input com seu conteúdo.
Scanner::Scanner(string input)
{
    /*this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: "
         << input.length() << endl;*/
    pos = 0;
    line = 1;

    ifstream inputFile(input, ios::in);
    string line;

    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            this->input.append(line + '\n');
        }
        inputFile.close();
    }
    else
        cout << "Unable to open file\n";

    // A próxima linha deve ser comentada posteriormente.
    // Ela é utilizada apenas para verificar se o
    // preenchimento de input foi feito corretamente.
    // cout << this->input;
}

int Scanner::getLine()
{
    return line;
}

// Método que retorna o próximo token da entrada
Token *Scanner::nextToken()
{
    Token *tok;
    string lexeme = "";

    int state = 0;

    while (true)
    {
        switch (state)
        {
        case 0:
            if(input[pos] == '\n'){
                line++;
            }
            if (input[pos] == '\0')
            {
                tok = new Token(END_OF_FILE);
                return tok;
            }
            if (isalpha(input[pos]))
            {
                lexeme += input[pos];
                state = 26;
            }
            else if (isdigit(input[pos]))
            {
                state = 1;
            }
            else if (input[pos] == '&')
            {
                state = 3;
            }
            else if (input[pos] == '=')
            {
                state = 5;
            }
            else if (input[pos] == '<')
            {
                state = 8;
            }
            else if (input[pos] == '>')
            {
                state = 9;
            }
            else if (input[pos] == '+')
            {
                state = 10;
            }
            else if (input[pos] == '-')
            {
                state = 11;
            }
            else if (input[pos] == '*')
            {
                state = 12;
            }
            else if (input[pos] == '/')
            {
                state = 13;
            }
            else if (input[pos] == '!')
            {
                state = 14;
            }
            else if (input[pos] == '(')
            {
                state = 17;
            }
            else if (input[pos] == ')')
            {
                state = 18;
            }
            else if (input[pos] == '[')
            {
                state = 19;
            }
            else if (input[pos] == ']')
            {
                state = 20;
            }
            else if (input[pos] == '{')
            {
                state = 21;
            }
            else if (input[pos] == '}')
            {
                state = 22;
            }
            else if (input[pos] == ';')
            {
                state = 23;
            }
            else if (input[pos] == '.')
            {
                state = 24;
            }
            else if (input[pos] == ',')
            {
                state = 25;
            }

            pos++;
            break;

        case 1:
            if (!isdigit(input[pos]))
            {
                state = 2;
            }
            pos++;
            break;

        case 2:
            tok = new Token(NUMBER, INTEGER_LITERAL);
            pos--;
            return tok;
        case 3:
            if (input[pos] == '&')
            {
                state = 4;
            }
            else
            {
                lexicalError("erro, esperava um operador &");
            }
            pos++;
            break;
        case 4:
            tok = new Token(RELOP, AND);
            return tok;
        case 5:
            if (input[pos] == '=')
            {
                state = 6;
            }
            else
            {
                state = 7;
            }
            pos++;
            break;
        case 6:
            tok = new Token(RELOP, EQUAL);
            return tok;
        case 7:
            tok = new Token(RELOP, ATRIBB);
            return tok;
        case 8:
            tok = new Token(RELOP, LESSTHAN);
            return tok;
        case 9:
            tok = new Token(RELOP, GREATERTHAN);
            return tok;
        case 10:
            tok = new Token(RELOP, PLUS);
            return tok;
        case 11:
            tok = new Token(RELOP, MINUS);
            return tok;
        case 12:
            tok = new Token(RELOP, MULT);
            return tok;
        case 13:
            if (input[pos] == '/' || input[pos] == '*')
            {
                state = 28;
            }
            else
            {
                tok = new Token(RELOP, DIV);
                return tok;
            }
            break;
        case 14:
            if (input[pos] == '=')
            {
                state = 15;
            }
            else
            {
                state = 16;
            }
            pos++;
            break;
        case 15:
            tok = new Token(RELOP, NOTEQUAL);
            return tok;
        case 16:
            tok = new Token(RELOP, NOT);
            return tok;
        case 17:
            tok = new Token(SEP, LEFTPAREN);
            return tok;
        case 18:
            tok = new Token(SEP, RIGHTPAREN);
            return tok;
        case 19:
            tok = new Token(SEP, LEFTBRACKET);
            return tok;
        case 20:
            tok = new Token(SEP, RIGTHBRACKET);
            return tok;
        case 21:
            tok = new Token(SEP, LEFTCURLYBRACKET);
            return tok;
        case 22:
            tok = new Token(SEP, RIGHTCURLYBRACKET);
            return tok;
        case 23:
            tok = new Token(SEP, SEMICOLON);
            return tok;
        case 24:
            tok = new Token(SEP, DOT);
            return tok;
        case 25:
            tok = new Token(SEP, COMMA);
            return tok;
        case 26:
            if (!isalnum(input[pos]) && input[pos] != '_' && input[pos] != '.')
            {
                state = 27;
            }
            else
            {
                lexeme += input[pos];
            }
            pos++;
            break;
        case 27:
            if (find(reserved_words.begin(), reserved_words.end(), lexeme) != reserved_words.end())
            {
                tok = new Token(RESERVED_WORD, lexeme);
            }
            else
            {
                tok = new Token(ID, lexeme);
            }

            pos--;
            return tok;
        case 28:
            if (input[pos] == '/')
            {
                state = 29;
            }
            else if (input[pos] == '*')
            {
                state = 30;
            }
            pos++;
            break;
        case 29:
            if (input[pos] == '\n')
            {
                state = 0;
                line++;
            }
            pos++;
            break;
        case 30:
            if (input[pos] == '*')
            {
                state = 31;
            }
            pos++;
            break;
        case 31:
            if (input[pos] == '/')
            {
                state = 0;
            }
            else
            {
                state = 30;
            }
            pos++;
            break;
        }
    }
}

void Scanner::lexicalError(string msg)
{
    cout << "Linha " << line << ": " << msg << endl;

    exit(EXIT_FAILURE);
}
