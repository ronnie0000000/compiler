%option noyywrap
%{
    #define YY_NO_UNPUT
    #define YY_NO_INPUT

    #include "parser.h"
    #include "Unit.h"
    #include <ostream>
    #include <fstream>
    using namespace std;
    extern Unit unit;
    extern FILE *yyin; 
    extern FILE *yyout;
    extern bool dump_tokens;

    void DEBUG_FOR_LAB4(std::string s){
        std::string DEBUG_INFO = "[DEBUG LAB4]: \t" + s + "\n";
        fputs(DEBUG_INFO.c_str(), yyout);
    }
%}


HEX (0[xX][0-9a-fA-F]+)
OCT (0[0-7]+)
DECIMIAL_INT ([1-9][0-9]*|0)
DECIMIAL_FLOAT ((([0-9]*[.][0-9]*([eE][+-]?[0-9]+)?)|([0-9]+[eE][+-]?[0-9]+))[fLlL]?)
HEX_FLOAT (0[xX](([0-9A-Fa-f]*[.][0-9A-Fa-f]*([pP][+-]?[0-9]+)?)|([0-9A-Fa-f]+[pP][+-]?[0-9]+))[fLlL]?)
ID [[:alpha:]_][[:alpha:][:digit:]_]*
EOL (\r\n|\n|\r)
WHITE [\t ]
COMMENTLINE (\/\/.*)
COMMENTBEGIN "/*"
COMMENTELEMENT (.|\n)
COMMENTEND "*/"
%x BLOCKCOMMENT

%%
{COMMENTLINE} {}
{COMMENTBEGIN} {BEGIN BLOCKCOMMENT;}
<BLOCKCOMMENT>{COMMENTELEMENT} {}
<BLOCKCOMMENT>{COMMENTEND} {BEGIN INITIAL;}
"int" {
    /*
    * Questions: 
    *   Q1: Why we need to return INT in further labs?
    *   Q2: What is "INT" actually?
    */
    if(dump_tokens)
        DEBUG_FOR_LAB4("INT\tint");
    return INT;
}
"float" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("FLOAT\tfloat");
    return FLOAT;
}
"void" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("VOID\tvoid");
    return VOID;
}
"if" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("IF\tif");
    return IF;
}
"else" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ELSE\telse");
    return ELSE;
}
"while" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("WHILE\twhile");
    return WHILE;
}
"return" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RETURN\treturn");
    return RETURN;
}
"break" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("BREAK\tbreak");
    return BREAK;
}
"continue" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("CONTINUE\tcontinue");
    return CONTINUE;
}
"const" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("CONST\tconst");
    return CONST;
}
"==" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("EQUAL\t==");
    return EQUAL;
}

"<=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LESSOREQUAL\t<=");
    return LESSOREQUAL;
}
">=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("MOREOREQUAL\t>=");
    return MOREOREQUAL;
}
"!=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("UNEQUAL\t!=");
    return UNEQUAL;
}
"=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ASSIGN\t=");
    return ASSIGN;
}
"<" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LESS\t<");
    return LESS;
}
">" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("MORE\t>");
    return MORE;
}
"+" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ADD\t+");
    return ADD;
}
"-" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SUB\t-");
    return SUB;
}
"*" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("MUL\t*");
    return MUL;
}
"!" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("NOT\t!");
    return NOT;
}
"/" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("DIV\t/");
    return DIV;
}
"%" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("MOD\t%");
    return MOD;
}
"||" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LOGIC_OR\t||");
    return LOGIC_OR;
}
"&&" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LOGIC_AND\t&&");
    return LOGIC_AND;
}
"|" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("OR\t+");
    return OR;
}
"&" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("AND\t+");
    return AND;
}
";" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SEMICOLON\t;");
    return SEMICOLON;
}
"," {
    if(dump_tokens)
        DEBUG_FOR_LAB4("COMMA\t,");
    return COMMA;
}
"(" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LPAREN\t(");
    return LPAREN;
}
")" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RPAREN\t)");
    return RPAREN;
}
"{" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LBRACE\t{");
    return LBRACE;
}
"}" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RBRACE\t}");
    return RBRACE;
}
"[" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LSQUARE\t[");
    return LSQUARE;
}
"]" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RSQUARE\t[");
    return RSQUARE;
}
{HEX} {
    int num=0;
    sscanf(yytext, "%x", &num);
    if(dump_tokens)
        DEBUG_FOR_LAB4(string("NUMBER\t") + to_string(num));
    yylval.itype = num;
    return INTEGER;
}
{HEX_FLOAT} {
    float num;
    sscanf(yytext, "%f", &num);
    if (dump_tokens)
        DEBUG_FOR_LAB4(string("NUMBER\t") + to_string(num));
    yylval.ftype = num;
    return FLOATING;
}
{OCT} {
    int num=0;
    sscanf(yytext, "%o", &num);
    if(dump_tokens)
        DEBUG_FOR_LAB4(string("NUMBER\t") + to_string(num));
    yylval.itype = num;
    return INTEGER;
}
{DECIMIAL_INT} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(string("DECIMIAL_INT\t")+string(yytext));
    yylval.itype = atoi(yytext);
    return INTEGER;
}
{DECIMIAL_FLOAT} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(string("DECIMIAL_FLOAT\t")+string(yytext));
    float num=0.0;
    sscanf(yytext,"%f",&num);
    yylval.ftype = num;
    return FLOATING;
}
"getint" {//添加库函数的声明，避免语法分析无法识别的情况出现
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    std::vector<SymbolEntry*> vec;
    Type* funcType = new FunctionType(TypeSystem::intType, vec);
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    if(st->install(yytext, se))
        unit.insertDeclare(se);
    return ID;
}
"putint" {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    std::vector<SymbolEntry*> vec;
    vec.push_back(new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel()));
    Type* funcType = new FunctionType(TypeSystem::voidType, vec);
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    if(st->install(yytext, se))
        unit.insertDeclare(se);
    return ID;
}
"putch" {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    std::vector<SymbolEntry*> vec;
     vec.push_back(new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel()));
    Type* funcType = new FunctionType(TypeSystem::voidType, vec);
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    if(st->install(yytext, se))
        unit.insertDeclare(se);
    return ID;
}
"getch" {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    std::vector<SymbolEntry*> vec;
    Type* funcType = new FunctionType(TypeSystem::intType, vec);
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    if(st->install(yytext, se))
        unit.insertDeclare(se);
    return ID;
}
"putarray" {
    // 暂时先写这一个吧
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    std::vector<SymbolEntry*> vec;
    vec.push_back(new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel()));
    ArrayType* arr = new ArrayType(TypeSystem::intType, 0);
     vec.push_back(new TemporarySymbolEntry(arr, SymbolTable::getLabel()));
    Type* funcType = new FunctionType(TypeSystem::voidType, vec);
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    if(st->install(yytext, se))
        unit.insertDeclare(se);
    return ID;
}

"getarray" {
    // 暂时先写这一个吧
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    std::vector<SymbolEntry*> vec;
    ArrayType* arr = new ArrayType(TypeSystem::intType, 0);
     vec.push_back(new TemporarySymbolEntry(arr, SymbolTable::getLabel()));
    Type* funcType = new FunctionType(TypeSystem::intType, vec);
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    if(st->install(yytext, se))
        unit.insertDeclare(se);
    return ID;
}
"putfarray" {
    // 暂时先写这一个吧
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    std::vector<SymbolEntry*> vec;
    vec.push_back(new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel()));
    ArrayType* arr = new ArrayType(TypeSystem::floatType, 0);
    vec.push_back(new TemporarySymbolEntry(arr, SymbolTable::getLabel()));
    Type* funcType = new FunctionType(TypeSystem::voidType, vec);
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    if(st->install(yytext, se))
        unit.insertDeclare(se);
    return ID;
}

"getfarray" {
    // 暂时先写这一个吧
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    std::vector<SymbolEntry*> vec;
    ArrayType* arr = new ArrayType(TypeSystem::floatType, 0);
     vec.push_back(new TemporarySymbolEntry(arr, SymbolTable::getLabel()));
    Type* funcType = new FunctionType(TypeSystem::floatType, vec);
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    if(st->install(yytext, se))
        unit.insertDeclare(se);
    return ID;
}
"getfloat" {//添加库函数的声明，避免语法分析无法识别的情况出现
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    std::vector<SymbolEntry*> vec;
    Type* funcType = new FunctionType(TypeSystem::floatType, vec);
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    if(st->install(yytext, se))
        unit.insertDeclare(se);
    return ID;
}
"putfloat" {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    std::vector<SymbolEntry*> vec;
     vec.push_back(new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel()));
    Type* funcType = new FunctionType(TypeSystem::voidType, vec);
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    if(st->install(yytext, se))
        unit.insertDeclare(se);
    return ID;
}

{ID} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    return ID;
}
{EOL} yylineno++;
{WHITE}

%%
