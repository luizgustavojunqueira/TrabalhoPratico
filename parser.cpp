#include "parser.h"

Parser::Parser(string input) { scanner = new Scanner(input); }

void Parser::advance() { lToken = scanner->nextToken(); }

void Parser::match(int t) {
  cout << "Name " << lToken->name << " Attribute: " << lToken->attribute
       << " Should be: " << t << endl;

  if (lToken->name == t || lToken->attribute == t)
    advance();
  else {
    error("Erro inesperado");
  }
}

void Parser::run() {
  advance();

  program();

  cout << "Compilação encerrada com sucesso!\n";
}

void Parser::program() {
  // Program -> MainClass ( ClassDeclaration )* EOF
  mainClass();
  while (lToken->name == CLASS) {
    classDeclaration();
  }
  match(END_OF_FILE);
}

void Parser::mainClass() {
  // MainClass -> class ID { public static void main ( String [ ] ID ) {
  // Statement } }
  match(CLASS);
  match(ID);
  match(LEFTCURLYBRACKET);
  match(PUBLIC);
  match(STATIC);
  match(VOID);
  match(MAIN);
  match(LEFTPAREN);
  match(STRING);
  match(LEFTBRACKET);
  match(RIGHTBRACKET);
  match(ID);
  match(RIGHTPAREN);
  match(LEFTCURLYBRACKET);
  statement();
  match(RIGHTCURLYBRACKET);
  match(RIGHTCURLYBRACKET);
}

void Parser::statement() {
  // Statement -> ID[Expression] = Expression | ID = Expression; | if (
  // Expression ) Statement else Statement | while ( Expression ) Statement | {
  // Statement* } | System.out.println ( Expression ) ;

  if (lToken->name == ID) {
    match(ID);
    if (lToken->attribute == LEFTBRACKET) {
      match(LEFTBRACKET);
      expression();
      match(RIGHTBRACKET);
      match(ATRIBB);
      expression();
      match(SEMICOLON);
    } else if (lToken->attribute == ATRIBB) {
      match(ATRIBB);
      expression();
      match(SEMICOLON);
    }
  } else if (lToken->name == IF) {
    match(IF);
    match(LEFTPAREN);
    expression();
    match(RIGHTPAREN);
    statement();
    match(ELSE);
    statement();
  } else if (lToken->name == WHILE) {
    match(WHILE);
    match(LEFTPAREN);
    expression();
    match(RIGHTPAREN);
    statement();
  } else if (lToken->attribute == LEFTCURLYBRACKET) {
    match(LEFTCURLYBRACKET);
    while (lToken->name == ID || lToken->name == IF || lToken->name == WHILE ||
           lToken->name == SOUT || lToken->name == EQUAL) {
      statement();
    }
    match(RIGHTCURLYBRACKET);
  } else if (lToken->name == SOUT) {
    match(SOUT);
    match(LEFTPAREN);
    expression();
    match(RIGHTPAREN);
    match(SEMICOLON);
  }
}

void Parser::expression() {
  // Expression -> Expression && RelExpression | RelExpression
  relExpression();
  if (lToken->attribute == AND) {
    match(AND);
    expression();
  }
}

void Parser::expressionList() {
  expression();
  while (lToken->attribute == COMMA) {
    match(COMMA);
    expression();
  }
}

void Parser::relExpression() {
  addExpression();
  if (lToken->attribute == LESSTHAN) {
    match(LESSTHAN);
    addExpression();
  } else if (lToken->attribute == GREATERTHAN) {
    match(GREATERTHAN);
    addExpression();
  } else if (lToken->attribute == EQUAL) {
    match(EQUAL);
    addExpression();
  } else if (lToken->attribute == NOTEQUAL) {
    match(NOTEQUAL);
    addExpression();
  }
}

void Parser::addExpression() {
  multExpression();
  if (lToken->attribute == PLUS) {
    match(PLUS);
    addExpression();
  } else if (lToken->attribute == MINUS) {
    match(MINUS);
    addExpression();
  }
}

void Parser::multExpression() {
  unExpression();
  if (lToken->attribute == MULT) {
    match(MULT);
    multExpression();
  } else if (lToken->attribute == DIV) {
    match(DIV);
    multExpression();
  }
}

void Parser::primExpression() {
  if (lToken->name == ID) {
    match(ID);
  } else if (lToken->name == TRUE) {
    match(TRUE);
  } else if (lToken->name == FALSE) {
    match(FALSE);
  } else if (lToken->name == NEW) {
    match(NEW);
    match(ID);
    match(LEFTPAREN);
    match(RIGHTPAREN);
  } else if (lToken->attribute == LEFTPAREN) {
    match(LEFTPAREN);
    expression();
    match(RIGHTPAREN);
  }
}

void Parser::classDeclaration() {
  // ClassDeclaration -> class ID (extends ID)? { VarDeclaration*
  // MethodDeclaration* }
  match(CLASS);
  match(ID);
  if (lToken->name == EXTENDS) {
    match(EXTENDS);
    match(ID);
  }
  match(LEFTCURLYBRACKET);
  while (lToken->name == INT || lToken->name == BOOLEAN || lToken->name == ID) {
    varDeclaration();
  }
  while (lToken->name == PUBLIC) {
    methodDeclaration();
  }
  match(RIGHTCURLYBRACKET);
}

void Parser::unExpression() {
  if (lToken->attribute == NOT) {
    match(NOT);
    unExpression();
  } else if (lToken->attribute == MINUS) {
    match(MINUS);
    unExpression();
  } else if (lToken->attribute == INTEGER_LITERAL) {
    match(INTEGER_LITERAL);
  } else if (lToken->name == TRUE) {
    match(TRUE);
  } else if (lToken->name == FALSE) {
    match(FALSE);
  } else if (lToken->name == NEW) {
    match(NEW);
    match(INT);
    match(LEFTBRACKET);
    expression();
    match(RIGHTBRACKET);
  } else {
    primExpression();

    if (lToken->attribute == LEFTBRACKET) {
      match(LEFTBRACKET);
      expression();
      match(RIGHTBRACKET);
    } else if (lToken->attribute == DOT) {
      match(DOT);
      match(LENGTH);
    }
  }
}

void Parser::varDeclaration() {
  type();
  match(ID);
  match(SEMICOLON);
}

void Parser::methodDeclaration() {
  // MethodDeclaration -> public Type ID ( Params ) { VarDeclaration* Statement*
  // return Expression; }
  match(PUBLIC);
  type();
  match(ID);
  match(LEFTPAREN);
  params();
  match(RIGHTPAREN);
  match(LEFTCURLYBRACKET);
  while (lToken->name == INT || lToken->name == BOOLEAN || lToken->name == ID) {
    varDeclaration();
  }
  while (lToken->name == ID || lToken->name == IF || lToken->name == WHILE ||
         lToken->name == SOUT || lToken->attribute == EQUAL) {
    statement();
  }
  match(RETURN);
  expression();
  match(SEMICOLON);
  match(RIGHTCURLYBRACKET);
}

void Parser::params() {
  // Params -> Type ID (, Type ID)*
  
  if(lToken->name == INT || lToken->name == BOOLEAN || lToken->name == ID){
    type();
    match(ID);
  }
  while (lToken->attribute == COMMA) {
    match(COMMA);
    type();
    match(ID);
  }
}

void Parser::type() {
  if (lToken->name == INT) {
    match(INT);
    if (lToken->attribute == LEFTBRACKET) {
      match(LEFTBRACKET);
      match(RIGHTBRACKET);
    }
  } else if (lToken->name == BOOLEAN) {
    match(BOOLEAN);
  } else if (lToken->name == ID) {
    match(ID);
  }
}

void Parser::error(string str) {
  cout << "Linha " << scanner->getLine() << ": " << str << endl;

  exit(EXIT_FAILURE);
}
