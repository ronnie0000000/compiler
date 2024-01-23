%code top{
    #include <iostream>
    #include <assert.h>
    #include <string>
    #include <stack>
    #include "parser.h"
    extern Ast ast;
    int yylex();
    int yyerror( char const * );
    Type *nowType;
    ArrayType *currentArray;
    std::stack<ArrayInit*> arrayStack;
    std::stack<WhileStmt*> whileStack;
    unsigned int leftBraceCount=0;
    unsigned int arrayIndex=0;
    int *arrayValue;
}

%code requires {
    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"
}

%union {
    int itype;
    float ftype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;
}

%start Program
%token <strtype> ID 
%token <itype> INTEGER
%token <ftype> FLOATING
%token IF ELSE WHILE BREAK CONTINUE
%token CONST
%token INT VOID FLOAT
%token LPAREN RPAREN LBRACE RBRACE LSQUARE RSQUARE SEMICOLON COMMA NOT
%token ADD SUB MUL DIV MOD OR AND LOGIC_OR LOGIC_AND LESS MORE LESSOREQUAL MOREOREQUAL EQUAL UNEQUAL ASSIGN
%token RETURN

%nterm <stmttype> Stmts Stmt AssignStmt BlockStmt ExprStmt VarDeclStmt
%nterm <stmttype> DeclStmt ConstDeclStmt ConstDefList ConstDefStmt VarDefStmt VarDefList
%nterm <stmttype> IfStmt WhileStmt BreakStmt ContinueStmt ReturnStmt 
%nterm <stmttype> FuncFParam FuncFParams FuncDef
%nterm <exprtype> Exp AddExp Cond LOrExp PrimaryExp LVal RelExp EqExp LAndExp MulExp UnaryExp ConstExp ConstInitVal InitVal ArrayIndices
%nterm <exprtype> FuncRParams InitValList
%nterm <type> Type

%precedence THEN
%precedence ELSE
%%
//程序起始
Program
    : Stmts {
        ast.setRoot($1);
    }
    ;
//可能有很多条语句
Stmts
    : Stmt {$$=$1;}
    | Stmts Stmt{
        $$ = new SeqNode($1, $2);
    }
    ;
// 语句也分很多种 赋值语句、表达式语句、语句块、if语句、while语句、break语句、continue语句、return语句、声明语句、函数语句
Stmt
    : AssignStmt {$$=$1;}
    | ExprStmt {$$=$1;}
    | BlockStmt {$$=$1;}
    | IfStmt {$$=$1;}
    | WhileStmt {$$=$1;}
    | BreakStmt {$$=$1;}
    | ContinueStmt {$$=$1;}
    | ReturnStmt {$$=$1;}
    | DeclStmt {$$=$1;}
    | FuncDef {$$=$1;}
    | SEMICOLON{$$=new EmptyStmt();}
    ;
//左值表达式，暂时只包括id
LVal
    : ID {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        Id *id= new Id(se);
        $$ = id;
        delete []$1;
    }
    |
    ID ArrayIndices{
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        Id *id = new Id(se,$2);
        $$ = id;
        delete []$1;
    }
    ;
//赋值语句（给id赋值）
AssignStmt
    :
    LVal ASSIGN Exp SEMICOLON {
        $$ = new AssignStmt($1, $3);
    }
    ;
//表达式语句
ExprStmt
    : Exp SEMICOLON {
        $$ = new ExprStmt($1);
    }
    ;
//语句块 建立新的符号表
BlockStmt
    :   LBRACE 
        {identifiers = new SymbolTable(identifiers);} 
        Stmts RBRACE 
        {
            $$ = new CompoundStmt($3);
            SymbolTable *currentSymbolTable = identifiers;
            identifiers = identifiers->getPrev();
            delete currentSymbolTable;
        }
    | LBRACE RBRACE {
        $$ = new CompoundStmt(nullptr);
    }
    ;
IfStmt
    : IF LPAREN Cond RPAREN Stmt %prec THEN {
        if(!$3->getType()->isBool()){
            SymbolEntry *se_temp = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            SymbolEntry *se_zero = new ConstantSymbolEntry(TypeSystem::intType, 0);
            $3 = new BinaryExpr(se_temp, BinaryExpr::UNEQUAL, $3, new Constant(se_zero));
        }
        $$ = new IfStmt($3, $5);
    }
    | IF LPAREN Cond RPAREN Stmt ELSE Stmt {
        if(!$3->getType()->isBool()){
            SymbolEntry *se_temp = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            SymbolEntry *se_zero = new ConstantSymbolEntry(TypeSystem::intType, 0);
            $3 = new BinaryExpr(se_temp, BinaryExpr::UNEQUAL, $3, new Constant(se_zero));
        }
        $$ = new IfElseStmt($3, $5, $7);
    }
    ;
WhileStmt
    : WHILE LPAREN Cond RPAREN {
        if(!$3->getType()->isBool()){
            SymbolEntry *se_temp = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            SymbolEntry *se_zero = new ConstantSymbolEntry(TypeSystem::intType, 0);
            $3 = new BinaryExpr(se_temp, BinaryExpr::UNEQUAL, $3, new Constant(se_zero));
        }
        WhileStmt* whileStmt = new WhileStmt($3,nullptr);
        $<stmttype>$ = whileStmt;
        whileStack.push(whileStmt);
    }
    Stmt {
        StmtNode *whileStmt = $<stmttype>5; 
        ((WhileStmt*)whileStmt)->setStmt($6);
        $$=whileStmt;
        whileStack.pop();
    }
    ;
BreakStmt
    : BREAK SEMICOLON {
        if(whileStack.empty()){
            fprintf(stderr,"break stmt is not in a while stmt\n");
            assert(!whileStack.empty());
        }
        $$ = new BreakStmt(whileStack.top());
    }
    ;
ContinueStmt
    : CONTINUE SEMICOLON {
        if(whileStack.empty()){
            fprintf(stderr,"continue stmt is not in a while stmt\n");
            assert(!whileStack.empty());
        }
        $$ = new ContinueStmt(whileStack.top());
    }
    ;
ReturnStmt
    : RETURN SEMICOLON {
        $$ = new ReturnStmt();
    }
    | RETURN Exp SEMICOLON {
        $$ = new ReturnStmt($2);
    }
    ;
//Exp的种类只有addExp
Exp
    :
    AddExp {$$ = $1;}
    ;
Cond
    :
    LOrExp {$$ = $1;}
    ;
PrimaryExp
    : LPAREN Exp RPAREN {
        $$ = $2;
    }
    | LVal {
        $$ = $1;
    }
    | INTEGER {
        //符号表元素添加值
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, $1);
        $$ = new Constant(se);
    }
    | FLOATING {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::floatType, $1);
        $$ = new Constant(se);
    }
    ;
UnaryExp
    :
    PrimaryExp {
        $$ = $1;
    }
    //调用函数是一个一元表达式
    | ID LPAREN FuncRParams RPAREN{
        
        SymbolEntry* se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "function \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        std::vector<Type*> paramsType = ((FunctionType*)(se->getType()))->getParamsType();
        ExprNode* callParamsType = $3;
        int paramCount = 0;
        
        while(callParamsType){
            paramCount++;
            callParamsType = (ExprNode*)callParamsType->getNext();
        }
        
        while(se){
            if(((FunctionType*)(se->getType()))->getParamsType().size() == paramCount){
                break;
            }
            se = se->getNext();
        }
        if(se == nullptr){
            fprintf(stderr, "function \"%s\" having %d params, is undefined\n", (char*)$1, paramCount);
            delete [](char*)$1;
            assert(se != nullptr);
        }

        callParamsType = $3;

        for(auto &params:paramsType){
            if(params != callParamsType->getSymbolEntry()->getType()){
                 if(callParamsType->getSymbolEntry()->getType()->isArray() && params->isArray()){
                    callParamsType = (ExprNode*)callParamsType->getNext();
                    continue;
                }
                fprintf(stderr, "your param TYPE should be %s, but when you call func you use %s\n",
                        params->toStr().c_str(),callParamsType->getSymbolEntry()->getType()->toStr().c_str());
            }
            callParamsType = (ExprNode*)callParamsType->getNext();
        }
        $$ = new FuncExpr(se,$3);
    }
    | ADD UnaryExp{
        /*SymbolEntry *se;
        if($2->getType()->isFloat())
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        else
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());

        $$ = new UnaryExpr(se,UnaryExpr::ADD, $2);*/
        $$ = $2;
    }
    | SUB UnaryExp{
        SymbolEntry *se;
        if($2->getType()->isFloat())
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        else
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::SUB, $2);

    }
    | NOT UnaryExp{
        SymbolEntry *se;
        se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::NOT, $2);
    }
    ;
FuncRParams 
    : Exp {$$ = $1;}
    | FuncRParams COMMA Exp {
        $$ = $1;
        $$->setNext($3);
    }
    | %empty {$$=nullptr;}
    ;
MulExp
    :
    UnaryExp{
        $$=$1;
    }
    | MulExp MUL UnaryExp{
        SymbolEntry* se;

        if ($1->getType()->isBool() || $3->getType()->isBool()) {
            fprintf(stderr,"bool cannot use in MUL\n");
            assert(!$1->getType()->isBool());
            assert(!$3->getType()->isBool());
        }

        if ($1->getType()->isFloat() || $3->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::MUL, $1, $3);
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::MUL, $1, $3);
        }
    }
    | MulExp DIV UnaryExp{
        SymbolEntry* se;

        if ($1->getType()->isBool() || $3->getType()->isBool()) {
            fprintf(stderr,"bool cannot use in DIV\n");
            assert(!$1->getType()->isBool());
            assert(!$3->getType()->isBool());
        }

        if ($1->getType()->isFloat() || $3->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::DIV, $1, $3);
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::DIV, $1, $3);
        }
    }
    | MulExp MOD UnaryExp{
        SymbolEntry* se;
        
        if ($1->getType()->isBool() || $3->getType()->isBool()) {
            fprintf(stderr,"bool cannot use in MOD\n");
            assert(!$1->getType()->isBool());
            assert(!$3->getType()->isBool());
        }

        if ($1->getType()->isFloat() || $3->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::MOD, $1, $3);
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::MOD, $1, $3);
        }
    }
    ;
AddExp
    :
    MulExp {$$ = $1;}
    |
    AddExp ADD MulExp
    {
        SymbolEntry* se;

        if ($1->getType()->isFloat() || $3->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
        }
    }
    |
    AddExp SUB MulExp
    {
        SymbolEntry* se;

        if ($1->getType()->isFloat() || $3->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
        }
    }
    ;
RelExp
    :
    AddExp {$$ = $1;}
    |
    RelExp LESS AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESS, $1, $3);
    }
    |
    RelExp MORE AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MORE, $1, $3);
    }
    |
    RelExp LESSOREQUAL AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESSOREQUAL, $1, $3);
    }
    |
    RelExp MOREOREQUAL AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MOREOREQUAL, $1, $3);
    }
    ;
EqExp
    :
    RelExp {$$=$1;}
    |
    EqExp EQUAL RelExp{
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::EQUAL, $1, $3);
    }
    |
    EqExp UNEQUAL RelExp{
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::UNEQUAL, $1, $3);
    }
    ;
LAndExp
    :
    EqExp {$$ = $1;}
    |
    LAndExp LOGIC_AND EqExp
    {
        SymbolEntry *boolSe;
        if(!$1->getType()->isBool()){
            boolSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $1 = new BinaryExpr(boolSe, BinaryExpr::UNEQUAL, $1, new Constant(new ConstantSymbolEntry(TypeSystem::intType, 0))); 
        }
        if(!$3->getType()->isBool()){
            boolSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $3 = new BinaryExpr(boolSe, BinaryExpr::UNEQUAL, $3, new Constant(new ConstantSymbolEntry(TypeSystem::intType, 0))); 
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LOGIC_AND, $1, $3);
    }
    |
    LAndExp AND EqExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::AND, $1, $3);
    }
    ;
LOrExp
    :
    LAndExp {$$ = $1;}
    |
    LOrExp LOGIC_OR LAndExp
    {
        SymbolEntry *boolSe;
        if(!$1->getType()->isBool()){
            boolSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $1 = new BinaryExpr(boolSe, BinaryExpr::UNEQUAL, $1, new Constant(new ConstantSymbolEntry(TypeSystem::intType, 0))); 
        }
        if(!$3->getType()->isBool()){
            boolSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $3 = new BinaryExpr(boolSe, BinaryExpr::UNEQUAL, $3, new Constant(new ConstantSymbolEntry(TypeSystem::intType, 0))); 
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LOGIC_OR, $1, $3);
    }
    |
    LOrExp OR LAndExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::OR, $1, $3);
    }
    ;
ConstExp
    :
    AddExp{
        $$ = $1;
    }
    ;
Type
    : INT {
        $$ = TypeSystem::intType;
        nowType = TypeSystem::intType;
    }
    | VOID {
        $$ = TypeSystem::voidType;
        nowType = TypeSystem::voidType;
    }
    | FLOAT {
         $$ = TypeSystem::floatType;
         nowType = TypeSystem::floatType;
    }
    ;
ArrayIndices
    : LSQUARE Exp RSQUARE {
        $$=$2;
    }
    | ArrayIndices LSQUARE Exp RSQUARE {
        $$=$1;
        $1->setNext($3);
    }
    | LSQUARE RSQUARE{
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, 0);
        $$ = new Constant(se);
    }
//声明语句
DeclStmt
    :
    ConstDeclStmt{
        $$=$1;
    }
    |
    VarDeclStmt{
        $$=$1;
    }
    ;
ConstDeclStmt
    :
    CONST Type ConstDefList SEMICOLON{
        $$=$3;
    }
ConstDefList
    : ConstDefList COMMA ConstDefStmt {
        $$ = $1;
        $1->setNext($3);
    }
    | ConstDefStmt {$$ = $1;}
    ;
ConstDefStmt
    : ID ASSIGN ConstInitVal {
        SymbolEntry* se;
        if(nowType->isInt()){
            se = new IdentifierSymbolEntry(TypeSystem::constIntType, $1, identifiers->getLevel());
            ((IdentifierSymbolEntry*)se)->setValue($3->getIValue());
        }else{
            if(nowType->isFloat()){
                se = new IdentifierSymbolEntry(TypeSystem::constFloatType, $1, identifiers->getLevel());
                ((IdentifierSymbolEntry*)se)->setFValue($3->getFValue());
            }
        }
        if (!identifiers->install($1, se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)$1);
            assert(false);
        }
        $$ = new DeclStmt(new Id(se), $3);
        delete []$1;
    }
    |
    ID ArrayIndices ASSIGN{
        // type a[]={...}
        ExprNode* t=$2;
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        //数组基础数据类型
        Type*arrayType=nowType->isInt()?TypeSystem::constIntType:TypeSystem::constFloatType;
        Type*tempType;
        while(!v.empty()){
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                //赋值给前一个数组
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        currentArray=(ArrayType*)arrayType;
        leftBraceCount=0;
    }
    InitVal{
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(currentArray, $1, identifiers->getLevel());
        if (!identifiers->install($1, se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)$1);
            assert(false);
        }
        $$ = new DeclStmt(new Id(se), $5);
        delete []$1;
    }
    ;
ConstInitVal
    :
    ConstExp{
        //需要补充
        $$=$1;
    }
    ;
//变量声明语句，使用varDefList做详细声明
VarDeclStmt
    :
    Type VarDefList SEMICOLON{
        $$=$2;
    }
    ;
//COMMA就是逗号，这句话的意思是可以有很多个VarDefList，每一个都是一个VarDefStmt
VarDefList
    :
    VarDefList COMMA VarDefStmt {
        $$ = $1;
        $1->setNext($3);
    } 
    | VarDefStmt { $$ = $1; }
    ;

VarDefStmt
    :
    //只定义一个变量，不赋值
    ID {
        SymbolEntry* se;
        if(nowType->isInt()){
            se = new IdentifierSymbolEntry(TypeSystem::intType, $1, identifiers->getLevel());
        }else{
            if(nowType->isFloat()){
                se = new IdentifierSymbolEntry(TypeSystem::floatType, $1, identifiers->getLevel()); 
            }
        }
        if (!identifiers->install($1, se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)$1);
            assert(false);
        }
        //identifiers->install($1,se);
        $$ = new DeclStmt(new Id(se));
        delete []$1;
    }
    //定义一个变量并赋值
    |
    ID ASSIGN InitVal {
        SymbolEntry*se;
            if(nowType->isInt()){
                se=new IdentifierSymbolEntry(TypeSystem::intType,$1,identifiers->getLevel());
                ((IdentifierSymbolEntry*)se)->setValue($3->getIValue());
        }else{
            if(nowType->isFloat()){
                se = new IdentifierSymbolEntry(TypeSystem::floatType, $1, identifiers->getLevel());
                ((IdentifierSymbolEntry*)se)->setFValue($3->getFValue());
            }
        }
        if (!identifiers->install($1, se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)$1);
            assert(false);
        }
        $$ = new DeclStmt(new Id(se),$3);
        delete []$1;
    }
    |
    //定义一个数组，但不赋值
    ID ArrayIndices {
        ExprNode* t=$2;
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        //数组基础数据类型
        Type*arrayType=nowType->isInt()?TypeSystem::intType:TypeSystem::floatType;
        
        Type*tempType;
        while(!v.empty()){            //te用来接受最新的数组
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                //赋值给前一个数组
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(arrayType, $1, identifiers->getLevel());
        //全局变量，初始化为全0
        if(dynamic_cast<IdentifierSymbolEntry*>(se)->isGlobal()){
            dynamic_cast<IdentifierSymbolEntry*>(se)->setAllZero(true);
        }
        if (!identifiers->install($1, se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)$1);
            assert(false);
        }
        $$ = new DeclStmt(new Id(se));
        delete []$1;
    }
    |
    ID ArrayIndices ASSIGN{
        // type a[]={...}
        ExprNode* t=$2;
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        //数组基础数据类型
        Type*arrayType=nowType->isInt()?TypeSystem::intType:TypeSystem::floatType;
        Type*tempType;
        while(!v.empty()){
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                //赋值给前一个数组
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        currentArray=(ArrayType*)arrayType;
        leftBraceCount=0;
    }
    InitVal{
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(currentArray, $1, identifiers->getLevel());
        if (!identifiers->install($1, se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)$1);
            assert(false);
        }
        $$ = new DeclStmt(new Id(se), $5);
        delete []$1;
    }
    ;
InitVal
    :
    Exp{
        //需要补充
        $$=$1;
        if(!arrayStack.empty()){
            //初始化数组
            arrayStack.top()->addExpr($1);
        }  

    }
    | LBRACE RBRACE{
        SymbolEntry* se;
        if(!arrayStack.empty()){
            currentArray = (ArrayType*)(((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()))->getElementType());
        }
        se = new ConstantSymbolEntry(currentArray);
        ArrayInit *arrayNode = new ArrayInit(se,true);
        if(!arrayStack.empty())
            arrayStack.top()->addExpr(arrayNode);

        if(!arrayStack.empty())
            currentArray=(ArrayType*)(((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()))->getElementType());
        $$=arrayNode;

    }
    | LBRACE {
        SymbolEntry* se;
        if(!arrayStack.empty()){
            currentArray = (ArrayType*)(((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()))->getElementType());
        }
        se = new ConstantSymbolEntry(currentArray);

        //if(currentArray->getElementType() != TypeSystem::intType && currentArray->getElementType() != TypeSystem::floatType){
        //    currentArray = (ArrayType*)(currentArray->getElementType());
        //}

        ArrayInit *arrayNode = new ArrayInit(se);
        if(!arrayStack.empty())
            arrayStack.top()->addExpr(arrayNode);
        
        arrayStack.push(arrayNode);
        //$<exprtype>$=arrayNode;
    }
    InitValList RBRACE{
        //assert(arrayStack.top()==$<exprtype>2);
        $$ = arrayStack.top();
        arrayStack.pop();
        if(!arrayStack.empty())
            currentArray=((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()));
        //把0补充上?没必要，遇到第一个大括号就把整个数组设置为0就行
    }
    ;
InitValList
    :   
    InitValList COMMA InitVal{
        $$ = $1;
    }
    |
    InitVal{
        $$ = $1;
    }
    ;
FuncDef
    :
    Type ID {
        identifiers = new SymbolTable(identifiers);
    }
    LPAREN FuncFParams RPAREN {

        Type* funcType;
        std::vector<SymbolEntry*> vec;
        //std::vector<SymbolEntry*> symVec;
        DeclStmt* temp = (DeclStmt*)$5;
        while(temp){
            vec.push_back(temp->getId()->getSymbolEntry());
            //symVec.push_back(temp->getId()->getSymbolEntry());
            temp = (DeclStmt*)(temp->getNext());
        }
        //funcType = new FunctionType($1, vec, symVec);
        funcType = new FunctionType($1, vec);
        SymbolEntry* se = new IdentifierSymbolEntry(funcType, $2, identifiers->getPrev()->getLevel());
        assert(identifiers->getPrev()->install($2, se));
    }
    BlockStmt
    {
        SymbolEntry *se;
        se = identifiers->lookup($2);
        assert(se != nullptr);
        $$ = new FunctionDef(se, (DeclStmt*)$5,$8);
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete []$2;
    }
    ;
FuncFParams
    :
    FuncFParam{
        $$=$1;
    }
    |
    FuncFParams COMMA FuncFParam{
        $$=$1;
        $$->setNext($3);
    }
    | %empty {$$=nullptr;}
    ;
FuncFParam
    :
    Type ID{
        SymbolEntry*se;
        se=new IdentifierSymbolEntry($1,$2,identifiers->getLevel());
        dynamic_cast<IdentifierSymbolEntry*>(se)->setParam();
        dynamic_cast<IdentifierSymbolEntry*>(se)->setAddr(new Operand(se));
        identifiers->install($2,se);
        $$=new DeclStmt(new Id(se));
        delete[]$2;
    }
    |
    Type ID ArrayIndices{
        ExprNode* t=$3;
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        //数组基础数据类型
        Type*arrayType=$1->isInt()?TypeSystem::intType:TypeSystem::floatType;
        Type*tempType;
        while(!v.empty()){
            //te用来接受最新的数组
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                //赋值给前一个数组
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(arrayType, $2, identifiers->getLevel());
        dynamic_cast<IdentifierSymbolEntry*>(se)->setParam();
        dynamic_cast<IdentifierSymbolEntry*>(se)->setAddr(new Operand(se));
        identifiers->install($2, se);
        $$ = new DeclStmt(new Id(se));
        delete []$2;
    }
    //其实这里还有一种情况没有考虑，就是允许最后几个参数有默认值，以后可以加上
    ;
%%

int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
