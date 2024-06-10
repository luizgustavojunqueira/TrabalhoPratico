# Gramática Corrigida da Linguagem MiniJava

| não terminal | regras de produção |
| :---------: | :-------|
| _Program_ | _MainClass_ **(**_ClassDeclaration_**)** * **EOF** |
| _MainClass_ | **class ID** **{ public static void main (String[] ID){** _Statement_ **}}**|
| _ClassDeclaration_ | **class ID (extendsID) ?** **{ (**_VarDeclaration_**)* (**_MethodDeclaration_**)* }**|
|_VarDeclaration_| _Type_ **ID**|
|_MethodDeclaration_| **public** _Type_ **ID** **( (** _Params_ **) ? )** {(_VarDeclaration_)* (_Statement_)* **return** _Expression_ **; }** |
|_Params_| _Type_ **ID** (, _Type_ **ID**)*|
|_Type_ | <ul><li>**int**([])?</li><li>**boolean**</li><li>**ID**</li><ul>|
|_Statement_|<ul><li>{ ( _Statement_ ) }</li><li>**if**( _Expression_ ) _Statement_ **else** _Statement_</li><li>**while**( _Expression_ ) _Statement_</li><li>**System.out.println** ( _Expression_ ) ;</li><li>**ID** _Statement'_<ul>|
|_Statement'_|<ul><li>= _Expression_ ;</li><li> [ _Expression_ ] = _Expression_ ;</li><ul>|
|_Expression_|<ul><li> _Expression_ && _RelExpression_</li>  <li> _RelExpression_ </li><ul>|
|_RelExpression_| _AddExpression_ _RelExpression'_|
|_RelExpression'_| <ul><li>< _AddExpression_ _RelExpression'_</li><li> > _AddExpression_ _RelExpression'_</li><li> == _AddExpression_ _RelExpression'_</li><li>!= _AddExpression_ _RelExpression'_</li><li>void (palavra vazia)</li><ul>|
|_AddExpression_|_MultExpression_ _AddExpression'_|
|_AddExpression'_|<ul><li>+ _MultExpressoion_ _AddExpression'_</li><li>- _MultExpression_ _AddExpression'_</li><li>void (palavra vazia)</li><ul>|
|_MultExpression_|_UnExpression_ _MultExpression'_|
|_MultExpression'_|<ul><li>* _UnExpression_ _MultExpression'_</li><li> / _UnExpression_ _MultExpression'_</li><li>void (void palavra vazia)</li><ul>|
|_UnExpression_|<ul><li> ! _UnExpression_</li><li> - _UnExpression_</li><li> **INTEGER_LITERAL**</li><li> **true**</li><li> **false**</li><li> **new int** [ _Expression_ ]</li><li> _PrimExpression_ _UnExpression'_</li><ul>|
|_UnExpression'_|<ul><li> **.length** </li><li> [ _Expression_ ]</li><li> void (palavra vazia)<ul>|
|_PrimExpression_|<ul><li>**ID** _PrimExpression'_</li><li>**this** _PrimExpression'_</li><li> **new ID ()** _PrimExpression'_ </li><li> ( _Expression_ ) _PrimExpression'_</li><ul>|
|_PrimExpression'_|<ul><li> **.ID** _PrimExpression'_</li><li> **.ID** ( ( _ExpressionsList_ ) ? ) _PrimExpression'_</li><li>void (palavra vazia)</li><ul>|
|_ExpressionsList_| _Expression_ (, _Expression_) *|

