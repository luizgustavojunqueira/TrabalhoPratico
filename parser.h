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
        void relExpression();
        void addExpression();
        void multExpression();
        void unExpression();
        void primExpression();
        void expressionList();
        //Continuar....
        void error(string);
};
