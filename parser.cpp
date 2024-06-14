#include "parser.h"

Parser::Parser(string input) { scanner = new Scanner(input); }

void Parser::advance() { lToken = scanner->nextToken(); }

void Parser::match(int t) {
  //cout << "Name " << lToken->name << " Attribute: " << lToken->attribute
  //     << " Should be: " << t << endl;

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
  mainClass();
  while (lToken->name == CLASS) {
    classDeclaration();
  }
  match(END_OF_FILE);
}

void Parser::mainClass() {
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

  if (lToken->attribute == LEFTCURLYBRACKET) {
    match(LEFTCURLYBRACKET);
    while (lToken->attribute == IF || lToken->attribute == WHILE ||
           lToken->attribute == SOUT || lToken->attribute == ID ||
           lToken->attribute == LEFTCURLYBRACKET) {
      statement();
    }
    match(RIGHTCURLYBRACKET);
  } else if (lToken->attribute == IF) {
    match(IF);
    match(LEFTPAREN);
    expression();
    match(RIGHTPAREN);
    match(RIGHTPAREN);
    statement();
    match(ELSE);
    statement();
  } else if (lToken->attribute == WHILE) {
    match(WHILE);
    match(LEFTPAREN);
    expression();
    match(RIGHTPAREN);
    statement();
  } else if (lToken->name == SOUT) {
    match(SOUT);
    match(LEFTPAREN);
    expression();
    match(RIGHTPAREN);
    match(SEMICOLON);
  } else if (lToken->name == ID) {
    match(ID);
    if (lToken->attribute == ATRIBB) {
      match(ATRIBB);
      expression();
      match(SEMICOLON);
    } else if (lToken->attribute == LEFTBRACKET) {
      match(LEFTBRACKET);
      expression();
      match(RIGHTBRACKET);
      match(ATRIBB);
      expression();
      match(SEMICOLON);
    }
  }
}
void Parser::expression() {
  relExpression();
  expressionLinha();
}

void Parser::expressionLinha() {
  if (lToken->attribute == AND) {
    match(AND);
    expression();
  }
}

void Parser::relExpression() {
  addExpression();
  relExpressionLinha();
}

void Parser::relExpressionLinha() {
  if (lToken->attribute == LESSTHAN) {
    match(LESSTHAN);
    relExpression();
  } else if (lToken->attribute == GREATERTHAN) {
    match(GREATERTHAN);
    relExpression();
  } else if (lToken->attribute == EQUAL) {
    match(EQUAL);
    relExpression();
    relExpressionLinha();
  } else if (lToken->attribute == NOTEQUAL) {
    match(NOTEQUAL);
    relExpression();
  }
}

void Parser::addExpression() {
  multExpression();
  addExpressionLinha();
}

void Parser::addExpressionLinha() {
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
  multExpressionLinha();
}

void Parser::multExpressionLinha() {
  if (lToken->attribute == MULT) {
    match(MULT);
    multExpression();
  } else if (lToken->attribute == DIV) {
    match(DIV);
    multExpression();
  }
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
    unExpressionLinha();
  } else {
    primExpression();

    if (lToken->attribute == LEFTBRACKET) {
      match(LEFTBRACKET);
      expression();
      match(RIGHTBRACKET);
    } else if (lToken->attribute == LENGTH) {
      match(LENGTH);
    }
  }
}

void Parser::unExpressionLinha() {
  if (lToken->attribute == INT) {
    match(INT);
    match(LEFTBRACKET);
    expression();
    match(RIGHTBRACKET);
  }else if (lToken->attribute == ID){
    match(ID);
    match(LEFTPAREN);
    match(RIGHTPAREN);
  }
}

void Parser::primExpression() {
  if (lToken->attribute == ID) {

    match(ID);
    primExpressionLinha();
  } else if (lToken->attribute == THIS) {
    match(THIS);
    primExpressionLinha();
  } else if (lToken->attribute == LEFTPAREN) {
    match(LEFTPAREN);
    expression();
    match(RIGHTPAREN);
    primExpressionLinha();
  }
}

void Parser::primExpressionLinha() {
  if (lToken->attribute == DOT) {
    match(DOT);
    if (lToken->attribute == ID) {

      match(ID);

      primExpressionDuasLinha();
      primExpressionLinha();
    }
  }
}

void Parser::primExpressionDuasLinha() {
  if (lToken->attribute == LEFTPAREN) {
    match(LEFTPAREN);
    expressionList();
    match(RIGHTPAREN);
  }
}

void Parser::expressionList() {
  expression();
  while (lToken->attribute == COMMA) {
    match(COMMA);
    expression();
  }
}

void Parser::classDeclaration() {
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

void Parser::varDeclaration() {
  type();
  match(ID);
  match(SEMICOLON);
}

void Parser::methodDeclaration() {
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
         lToken->name == SOUT || lToken->attribute == LEFTCURLYBRACKET) {
    statement();
  }
  match(RETURN);
  expression();
  match(SEMICOLON);
  match(RIGHTCURLYBRACKET);
}

void Parser::params() {

  if (lToken->name == INT || lToken->name == BOOLEAN || lToken->name == ID) {
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
