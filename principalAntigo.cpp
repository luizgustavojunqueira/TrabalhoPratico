#include "scanner.h"

string *vet;
void print(Token *);
void allocVetor();
void freeVetor();

int main(int argc, char *argv[])
{
    // Verifica se foi executado corretamente
    // Essa main espera receber o nome do arquivo a ser
    // executado na linha de comando.
    if (argc != 2)
    {
        cout << "Uso: ./compiler nome_arquivo.mj\n";
        return 1;
    }

    string input;

    // getline(cin, input);

    Scanner *scanner = new Scanner(argv[1]);

    allocVetor();

    Token *t;

    int a = 0;

    int linhaAnterior = 0;
    int linha = 0;

    do
    {
        t = scanner->nextToken();

        linha = scanner->getLine();
        if(linha != linhaAnterior)
        {
            cout << endl;
            linhaAnterior = linha;
        }

        print(t);
    } while (t->name != END_OF_FILE);

    delete scanner;

    freeVetor();

    return 0;
}

void allocVetor()
{
    vet = new string[50];

    vet[0] = "UNDEF";              // 0
    vet[1] = "ID";                 // 1
    vet[2] = "NUMBER";             // 2
    vet[3] = "INTEGER_LITERAL";    // 3
    vet[4] = "RELOP";              // 4
    vet[5] = "AND";                // 5
    vet[6] = "GREATERTHAN";        // 6
    vet[7] = "LESSTHAN";           // 7
    vet[8] = "PLUS";               // 8
    vet[9] = "MINUS";              // 9
    vet[10] = "MULT";              // 10
    vet[11] = "DIV";               // 11
    vet[12] = "EQUAL";             // 12
    vet[13] = "ATRIBB";            // 13
    vet[14] = "NOTEQUAL";          // 14
    vet[15] = "NOT";               // 15
    vet[16] = "SEP";               // 16
    vet[17] = "LEFTPAREN";         // 17
    vet[18] = "RIGHTPAREN";        // 18
    vet[19] = "LEFTBRACKET";       // 19
    vet[20] = "RIGTHBRACKET";      // 20
    vet[21] = "LEFTCURLYBRACKET";  // 21
    vet[22] = "RIGHTCURLYBRACKET"; // 22
    vet[23] = "SEMICOLON";         // 23
    vet[24] = "DOT";               // 24
    vet[25] = "COMMA";             // 25
    vet[26] = "RESERVED_WORD";     // 26
    vet[27] = "BOOLEAN";           // 27
    vet[28] = "CLASS";             // 28
    vet[29] = "ELSE";              // 29
    vet[30] = "EXTENDS";           // 30
    vet[31] = "FALSE";             // 31
    vet[32] = "IF";                // 32
    vet[33] = "INT";               // 33
    vet[34] = "LENGTH";            // 34
    vet[35] = "MAIN";              // 35
    vet[36] = "NEW";               // 36
    vet[37] = "PUBLIC";            // 37
    vet[38] = "RETURN";            // 38
    vet[39] = "STATIC";            // 39
    vet[40] = "STRING";            // 40
    vet[41] = "SOUT";              // 41 System.out.println
    vet[42] = "THIS";              // 42
    vet[43] = "TRUE";              // 43
    vet[44] = "VOID";              // 44
    vet[45] = "WHILE";             // 45
    vet[46] = "COMMENT";           // 46
    vet[47] = "LINE_COMMENT";      // 47
    vet[48] = "BLOCK_COMMENT";     // 48
    vet[49] = "END_OF_FILE";       // 49
}

void freeVetor()
{
    delete[] vet;
}

void print(Token *t)
{
    cout << vet[t->name];

    if (t->attribute != UNDEF)
        cout << "(" << vet[t->attribute] << ")";

    if (t->lexeme != "")
        cout << "(" << t->lexeme << ")";

    cout << " ";
}