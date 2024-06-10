#include <iostream>
#include <ctype.h> //Funções de caracteres
#include <string>

using namespace std;

enum Names
{
    UNDEF,             // 0
    ID,                // 1
    NUMBER,            // 2
    INTEGER_LITERAL,   // 3
    RELOP,             // 4
    AND,               // 5
    GREATERTHAN,       // 6
    LESSTHAN,          // 7
    PLUS,              // 8
    MINUS,             // 9
    MULT,              // 10
    DIV,               // 11
    EQUAL,             // 12
    ATRIBB,            // 13
    NOTEQUAL,          // 14
    NOT,               // 15
    SEP,               // 16
    LEFTPAREN,         // 17
    RIGHTPAREN,        // 18
    LEFTBRACKET,       // 19
    RIGHTBRACKET,      // 20
    LEFTCURLYBRACKET,  // 21
    RIGHTCURLYBRACKET, // 22
    SEMICOLON,         // 23
    DOT,               // 24
    COMMA,             // 25
    RESERVED_WORD,     // 26
    BOOLEAN,           // 27
    CLASS,             // 28
    ELSE,              // 29
    EXTENDS,           // 30
    FALSE,             // 31
    IF,                // 32
    INT,               // 33
    LENGTH,            // 34
    MAIN,              // 35
    NEW,               // 36
    PUBLIC,            // 37
    RETURN,            // 38
    STATIC,            // 39
    STRING,            // 40
    SOUT,              // 41 System.out.println
    THIS,              // 42
    TRUE,              // 43
    VOID,              // 44
    WHILE,             // 45
    COMMENT,           // 46
    LINE_COMMENT,      // 47
    BLOCK_COMMENT,     // 48
    END_OF_FILE        // 49
};

class Token
{
public:
    int name;
    int attribute;
    string lexeme;

    Token(int name)
    {
        this->name = name;
        attribute = name;
    }

    Token(int name, string l)
    {
        this->name = name;
        attribute = name;
        lexeme = l;
    }

    Token(int name, int attr)
    {
        this->name = name;
        attribute = attr;
    }
};
