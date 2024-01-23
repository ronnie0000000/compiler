#include "Type.h"
#include <assert.h>
#include <sstream>


IntType TypeSystem::commonInt = IntType(32); //TypeSystem中的commonInt就是一个四字节的int类型，等于号的右边是调用int的构造函数
FloatType TypeSystem::commonFloat = FloatType(32);
IntType TypeSystem::commonConstInt = IntType(32,true);
FloatType TypeSystem::commonConstFloat = FloatType(32,true);
VoidType TypeSystem::commonVoid = VoidType();
IntType TypeSystem::commonBool = IntType(1);


Type* TypeSystem::intType = &commonInt; //这句话的意思是其实TypeSystem中那个public的类型intType就是那个private类型commonInt
Type* TypeSystem::floatType=&commonFloat;
Type* TypeSystem::voidType = &commonVoid;
Type* TypeSystem::constIntType=&commonConstInt;
Type* TypeSystem::constFloatType=&commonConstFloat;
Type* TypeSystem::boolType = &commonBool;

//int类型 常量返回const int，非常量返回int
std::string IntType::toStr()
{
    /*if(isConst){
        return "const i32";
    }else{
        return "i32";
    }*/
    if(size == 32)
        return "i32";
    return "i1";
}
//float类型 常量返回const float，非常量返回float
std::string FloatType::toStr()
{
    /*if(isConst){
        return "const float";
    }else{
        return "float";
    }*/
    return "float";
}
//void类型 返回void
std::string VoidType::toStr()
{
    return "void";
}
//函数类型 返回函数的返回类型
std::string FunctionType::toStr()
{
    std::ostringstream buffer;
    buffer << returnType->toStr() << "(";
    for (auto it = paramsType.begin(); it != paramsType.end(); it++) {
        buffer << (*it)->toStr();
        if (it + 1 != paramsType.end())
            buffer << ", ";
    }
    buffer << ')';
    return buffer.str();
}
//输出数组大小，格式为：const int【4】【5】
std::string ArrayType::toStr() {
   std::vector<std::string> vec;
    Type* temp = this;
    int count = 0;
    bool flag = false;
    while (temp && temp->isArray()) {
        std::ostringstream buffer;
        if (((ArrayType*)temp)->getLength() == 0) {
            flag = true;
        } else {
            buffer << "[" << ((ArrayType*)temp)->getLength() << " x ";
            count++;
            vec.push_back(buffer.str());
        }
        temp = ((ArrayType*)temp)->getElementType();
    }
    assert(temp->isInt());
    std::ostringstream buffer;
    for (auto it = vec.begin(); it != vec.end(); it++)
        buffer << *it;
    buffer << "i32";
    while (count--)
        buffer << ']';
    if(flag)
        buffer << '*';
    return buffer.str();
}

std::string PointerType::toStr()
{
    std::ostringstream buffer;
    buffer << valueType->toStr() << "*";
    return buffer.str();
}