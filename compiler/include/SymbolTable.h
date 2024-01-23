#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__

#include <string>
#include <map>

class Type;
class Operand;
class SymbolEntry
{
private:
    int kind;
protected:
    enum {CONSTANT, VARIABLE, TEMPORARY};
    Type *type;
    SymbolEntry *next;
public:
    SymbolEntry(Type *type, int kind);
    virtual ~SymbolEntry() {};
    bool isConstant() const {return kind == CONSTANT;};
    bool isTemporary() const {return kind == TEMPORARY;};
    bool isVariable() const {return kind == VARIABLE;};
    Type* getType() {return type;};
    void setType(Type *type) {this->type = type;};
    virtual std::string toStr() = 0;
    // You can add any function you need here.

    bool setNext(SymbolEntry *se) ;
    SymbolEntry *getNext() const {return next;};
};


class SymbolTable
{
private:
    std::map<std::string, SymbolEntry*> symbolTable;
    SymbolTable *prev;
    int level;
    static int counter;
public:
    SymbolTable();
    SymbolTable(SymbolTable *prev);
    bool install(std::string name, SymbolEntry* entry);
    SymbolEntry* lookup(std::string name);
    SymbolTable* getPrev() {return prev;};
    int getLevel() {return level;};
    static int getLabel() {return counter++;};
};

/*  
    Symbol entry for literal constant. Example:

    int a = 1;

    Compiler should create constant symbol entry for literal constant '1'.
*/

class ConstantSymbolEntry : public SymbolEntry
{
private:

    int value;
    float fvalue;
    
    float* arrayFValue;
    int* arrayValue;

public:
    ConstantSymbolEntry(Type *type, int value);
    ConstantSymbolEntry(Type *type,float fvalue);
    ConstantSymbolEntry(Type *type) : SymbolEntry(type, SymbolEntry::CONSTANT){};
    virtual ~ConstantSymbolEntry() {};
    int getValue() const {return value;};
    float getFvalue() const {return fvalue;};
    std::string toStr();
    // You can add any function you need here.

    int* getArray(){return this->arrayValue;};
    float* getFArray(){return this->arrayFValue;};
};


/* 
    Symbol entry for identifier. Example:

    int a;
    int b;
    void f(int c)
    {
        int d;
        {
            int e;
        }
    }

    Compiler should create identifier symbol entries for variables a, b, c, d and e:

    | variable | scope    |
    | a        | GLOBAL   |
    | b        | GLOBAL   |
    | c        | PARAM    |
    | d        | LOCAL    |
    | e        | LOCAL +1 |
*/
class IdentifierSymbolEntry : public SymbolEntry
{
private:
    enum {GLOBAL, PARAM, LOCAL};
    std::string name;
    int scope;
    Operand *addr;  
    // You can add any field you need here.
    bool allZero;
    bool constant;

    int value;
    float fvalue;

    float* arrayFValue;
    int* arrayValue;

    int label;
    bool funcParam;

public:
    IdentifierSymbolEntry(Type *type, std::string name, int scope) 
    : SymbolEntry(type, SymbolEntry::VARIABLE), name(name)
    {
        this->scope = scope;
        this->allZero = false;
        this->arrayValue = nullptr;
        this->arrayFValue = nullptr;
    };

    virtual ~IdentifierSymbolEntry() {};
    std::string toStr();
    bool isGlobal() const {return scope == GLOBAL;};
    bool isParam() const {return scope == PARAM;};
    bool isLocal() const {return scope >= LOCAL;};
    int getScope() const {return scope;};
    void setAddr(Operand *addr) {this->addr = addr;};
    void setAllZero(bool allZero){this->allZero=allZero;};
    bool isAllZero(){return allZero;};
    Operand* getAddr(){return addr;};

    int getValue(){return value;};
    float getFValue(){return fvalue;};
    void setValue(int v){value=v;};
    void setFValue(float v){fvalue=v;};

    int* getArrayValue(){return arrayValue;};
    float* getFArrayValue(){return arrayFValue;};
    void setArrayValue(int*v){this->arrayValue=v;};
    void setFArrayValue(float*v){this->arrayFValue=v;};

    void setParam(){this->funcParam = true;this->label=SymbolTable::getLabel();};
    // You can add any function you need here.
};


/* 
    Symbol entry for temporary variable created by compiler. Example:

    int a;
    a = 1 + 2 + 3;

    The compiler would generate intermediate code like:

    t1 = 1 + 2
    t2 = t1 + 3
    a = t2

    So compiler should create temporary symbol entries for t1 and t2:

    | temporary variable | label |
    | t1                 | 1     |
    | t2                 | 2     |
*/

class TemporarySymbolEntry : public SymbolEntry
{
private:
    int label;
public:
    TemporarySymbolEntry(Type *type, int label);
    virtual ~TemporarySymbolEntry() {};
    std::string toStr();
    // You can add any function you need here.
};


extern SymbolTable *identifiers;
extern SymbolTable *globals;

#endif
