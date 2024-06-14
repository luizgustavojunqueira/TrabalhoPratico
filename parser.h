#include "scanner.h"

class Parser
{
	private:
		Scanner* scanner;
		Token* lToken;

		void advance();
		void match(int); 
		
	public:
		Parser(string);
		void run();
        void program();
        void mainClass();
        void classDeclaration();
        void statement();
        void term();
        void varDeclaration();
        void methodDeclaration();
        void params();
        void type();
        void expression();
        void expressionLinha();
        void relExpression();
        void relExpressionLinha();
        void addExpression();
        void addExpressionLinha();
        void multExpression();
        void multExpressionLinha();
        void unExpression();
        void unExpressionLinha();
        void primExpression();
        void primExpressionLinha();
        void primExpressionDuasLinha();
        void expressionList();
        //Continuar....
        void error(string);
};
