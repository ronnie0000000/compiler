#ifndef __TYPE_H__
#define __TYPE_H__
#include <vector>
#include <string>

#include<SymbolTable.h>
class SymbolEntry;

class Type
{
private:
    int kind;
protected:
    enum {INT, VOID, FUNC, FLOAT, ARRAY, BOOL, PTR};
    int size;
public:
    Type(int kind, int size=0) : kind(kind),size(size){};
    virtual ~Type() {};
    virtual std::string toStr() = 0;
    bool isInt() const {return kind == INT && size == 32;};
    bool isVoid() const {return kind == VOID;};
    bool isFunc() const {return kind == FUNC;};
    bool isFloat() const {return kind == FLOAT;};
    bool isArray() const {return kind == ARRAY;};
    bool isBool() const {return kind == INT && size == 1;};
    bool isPtr() const {return kind == PTR;};
    int getSize() const {return this->size;};
};

class IntType : public Type
{
private:
    bool isConst;
public:
    IntType(int size, bool isConst=false) : Type(Type::INT, size), isConst(isConst){};
    std::string toStr();
};

class FloatType : public Type
{
private:
    bool isConst;
public:
    FloatType(int size, bool isConst=false) : Type(Type::FLOAT, size), isConst(isConst){};
    std::string toStr();
};

class VoidType : public Type
{
public:
    VoidType() : Type(Type::VOID){};
    std::string toStr();
};

class FunctionType : public Type
{
private:
    Type *returnType;
    std::vector<Type*> paramsType;
    std::vector<SymbolEntry*> paramsSe;
public:
    FunctionType(Type* returnType, std::vector<SymbolEntry*> paramsSe) : 
    Type(Type::FUNC), returnType(returnType), paramsSe(paramsSe){
        for(auto it = paramsSe.begin();it!=paramsSe.end();it++){
            paramsType.push_back((*it)->getType());
        }
    };
    Type* getRetType(){return this->returnType;};
    std::vector<Type*> getParamsType(){return this->paramsType;};
    std::vector<SymbolEntry*> getParamsSe(){return this->paramsSe;};
    std::string toStr();
};

class ArrayType : public Type {
   private:
    Type* elementType;
    int length;
    bool isConst;
    Type* arrayType =nullptr;

   public:
    ArrayType(Type* elementType,
              int length,
              bool constant = false)
        : Type(Type::ARRAY,elementType->getSize()*length),
          elementType(elementType),length(length),isConst(constant) {};
    std::string toStr();
    int getLength() const { return length; };
    Type* getElementType() const { return elementType; };
    void setArrayType(Type* arrayType) { this->arrayType = arrayType; };
    Type* getArrayType() const { return arrayType; };
    int getSize() const {return size;}
};

class PointerType : public Type
{
private:
    Type *valueType;
public:
    PointerType(Type* valueType) : Type(Type::PTR) {this->valueType = valueType;};
    std::string toStr();
};

class TypeSystem
{
private:
    static IntType commonInt;
    static FloatType commonFloat;
    static IntType commonConstInt;
    static FloatType commonConstFloat;
    static VoidType commonVoid;
    static IntType commonBool;

public:
    static Type *intType;
    static Type *floatType;
    static Type *constIntType;
    static Type *constFloatType;
    static Type *voidType;
    static Type *boolType;
};

#endif
