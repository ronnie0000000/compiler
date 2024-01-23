#include "SymbolTable.h"
#include "Type.h"
#include <iostream>
#include <sstream>

SymbolEntry::SymbolEntry(Type *type, int kind) 
{
    this->type = type;
    this->kind = kind;
    this->next = nullptr;
}

bool SymbolEntry::setNext(SymbolEntry *se)
{
    int paramSize = (dynamic_cast<FunctionType*>(se->getType()))->getParamsType().size();
    SymbolEntry *nextSe = this;

    if(this->next == nullptr){
        if(dynamic_cast<FunctionType*>(this->getType())->getParamsType().size() == paramSize)
        {
            fprintf(stderr, "a func is reDef\n");
            return false;
        }
        this->next=se;
        return true;
    }

    while(nextSe->getNext()){
        int params = (dynamic_cast<FunctionType*>(nextSe->getType()))->getParamsType().size();
        if (params == paramSize){
            fprintf(stderr, "a func is reDef\n");
            return false;
        }
        nextSe = nextSe->getNext();
    }

    nextSe->next = se;
    return false;
}

ConstantSymbolEntry::ConstantSymbolEntry(Type *type, int value) : SymbolEntry(type, SymbolEntry::CONSTANT)
{
    this->value = value;
}

ConstantSymbolEntry::ConstantSymbolEntry(Type *type, float fvalue) : SymbolEntry(type, SymbolEntry::CONSTANT)
{
    this->fvalue = fvalue;
}

std::string ConstantSymbolEntry::toStr()
{
    
    std::ostringstream buffer;
    if(((IntType*)this->type)->isInt()){
        buffer << value;
        return buffer.str();
    }else{
        buffer << fvalue;
        return buffer.str();
    }    
    
   /*
       std::ostringstream buffer;
        buffer << value;
        return buffer.str();
   */

}

std::string IdentifierSymbolEntry::toStr()
{
    std::ostringstream buffer;
    if(this->funcParam){
        buffer << "%t" << label;
        return buffer.str();
    }
    if(this->scope == GLOBAL){
        buffer << "@" << name;
        return buffer.str();
    }
    return name;
}

TemporarySymbolEntry::TemporarySymbolEntry(Type *type, int label) : SymbolEntry(type, SymbolEntry::TEMPORARY)
{
    this->label = label;
}

std::string TemporarySymbolEntry::toStr()
{
    std::ostringstream buffer;
    buffer << "%t" << label;
    return buffer.str();
}

SymbolTable::SymbolTable()
{
    prev = nullptr;
    level = 0;
}

SymbolTable::SymbolTable(SymbolTable *prev)
{
    this->prev = prev;
    this->level = prev->level + 1;
}

/*
    Description: lookup the symbol entry of an identifier in the symbol table
    Parameters: 
        name: identifier name
    Return: pointer to the symbol entry of the identifier

    hint:
    1. The symbol table is a stack. The top of the stack contains symbol entries in the current scope.
    2. Search the entry in the current symbol table at first.
    3. If it's not in the current table, search it in previous ones(along the 'prev' link).
    4. If you find the entry, return it.
    5. If you can't find it in all symbol tables, return nullptr.
*/
SymbolEntry* SymbolTable::lookup(std::string name)
{
    // Todo
    SymbolTable* table = this;
    while (table != nullptr)
        if (table->symbolTable.find(name) != table->symbolTable.end()) {//找到了
            return table->symbolTable[name];//返回
        } else {
            table = table->prev;//没找到，找前一个符号表
        }
    return nullptr;
}

// install the entry into current symbol table.
bool SymbolTable::install(std::string name, SymbolEntry* entry)
{
    if(this->symbolTable.find(name)!= this->symbolTable.end()){
        SymbolEntry *se = symbolTable[name];
        if(se->getType()->isFunc()){
            if(se->setNext(entry))
                return true;
            return false;
        }
        return false;
    }
    symbolTable[name] = entry;
    return true;
}

int SymbolTable::counter = 0;
static SymbolTable t;
SymbolTable *identifiers = &t;
SymbolTable *globals = &t;
