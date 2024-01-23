#ifndef __AST_H__
#define __AST_H__

#include <fstream>
#include "Operand.h"
#include "Type.h"
class SymbolEntry;
class Unit;
class Function;
class BasicBlock;
class Instruction;
class IRBuilder;

class SymbolEntry;


class Node 
{
private:
    static int counter;
    int seq;
    Node* next=nullptr;//将关联节点串起来
protected:
    std::vector<Instruction*> true_list;
    std::vector<Instruction*> false_list;
    static IRBuilder *builder;
    void backPatch(std::vector<Instruction*> &list, BasicBlock*bb);
    std::vector<Instruction*> merge(std::vector<Instruction*> &list1, std::vector<Instruction*> &list2);

public:
    Node();
    int getSeq() const {return seq;};
    virtual void output(int level) = 0;
    void setNext(Node *next);
    Node *getNext(){return this->next;};

    static void setIRBuilder(IRBuilder*ib) {builder = ib;};
    virtual void typeCheck() = 0;
    virtual void genCode() = 0;
    std::vector<Instruction*>& trueList() {return true_list;}
    std::vector<Instruction*>& falseList() {return false_list;}
};

class ExprNode : public Node
{
protected:
    SymbolEntry *symbolEntry;
    Operand *dst;   // The result of the subtree is stored into dst.
public:
    ExprNode(SymbolEntry *symbolEntry) : symbolEntry(symbolEntry){};
    Type* getType();
    SymbolEntry *getSymbolEntry(){return symbolEntry;}
    Operand* getOperand() {return dst;};
    SymbolEntry* getSymPtr() {return symbolEntry;};
    virtual int getIValue(){return -1;};
    virtual float getFValue(){return -1.0;};
};

class UnaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr;
public:
    enum {SUB,ADD,NOT};
    UnaryExpr(SymbolEntry *se, int op, ExprNode *expr) : ExprNode(se), op(op), expr(expr){
        dst=new Operand(se);
    };
    void output(int level);
    int getIValue();
    float getFValue();
    void typeCheck();
    void genCode();
};

class FuncExpr : public ExprNode {
   private:
    ExprNode* param;

   public:
    FuncExpr(SymbolEntry* se, ExprNode* param);
    void output(int level);
    int getIValue(){return 0;};
    float getFValue(){return 0.0;};
    void typeCheck();
    void genCode();
};


class BinaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr1, *expr2;
public:
    enum {ADD, SUB, MUL, DIV, MOD, AND, OR,
    LOGIC_AND, LOGIC_OR, 
    MORE, LESS, MOREOREQUAL, LESSOREQUAL, EQUAL, UNEQUAL};
    BinaryExpr(SymbolEntry *se, int op, ExprNode*expr1, ExprNode*expr2) : ExprNode(se), op(op), expr1(expr1), expr2(expr2){dst=new Operand(se);};
    void output(int level);
    int getIValue();
    float getFValue();
    void typeCheck();
    void genCode();
};

class Constant : public ExprNode
{
public:
    Constant(SymbolEntry *se) : ExprNode(se){dst=new Operand(se);};
    int getvalue(){return ((ConstantSymbolEntry*)symbolEntry)->getValue(); }
    void output(int level);
    int getIValue();
    float getFValue();
    void typeCheck();
    void genCode();
};

//ID类，存储变量用的，他是继承了表达式节点
class Id : public ExprNode
{
private:
    bool left;
    ExprNode *arrayIndices;
public:
    Id(SymbolEntry *se ,ExprNode *arrayIndices=nullptr) : ExprNode(se),arrayIndices(arrayIndices){
        left=false;
        if(se){
            if(getType()->isInt()){
                SymbolEntry* temp = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
                dst = new Operand(temp);
            }else if(getType()->isFloat()){
                SymbolEntry* temp = new TemporarySymbolEntry(TypeSystem::floatType,SymbolTable::getLabel());
                dst = new Operand(temp);
            }else if(getType()->isArray()){
                SymbolEntry* temp = new TemporarySymbolEntry(new PointerType(dynamic_cast<ArrayType*>(getType())->getElementType()),SymbolTable::getLabel());
                dst = new Operand(temp);
            }
        }
    };
    SymbolEntry* getSymbolEntry(){return symbolEntry;};
    void output(int level);
    std::string getValue(){return symbolEntry->toStr();}
    int getIValue(){return (int)getFValue();};
    float getFValue(){
        SymbolTable* nowTable=identifiers;
        while(nowTable){
            if(nowTable->lookup(getValue())){
                return ((IdentifierSymbolEntry*)(identifiers->lookup(getValue())))->getValue();
            }
            else{
                nowTable=nowTable->getPrev();
            }
        }
        return 0.0;
    }
    void typeCheck();
    void genCode();
    void setLeft(){left=true;};
};

class ArrayInit : public ExprNode
{
private:
    ExprNode* expr;
    int childExprCount;
    bool fullZero;
public:
    ArrayInit(SymbolEntry* se,bool fullZero = false):ExprNode(se),fullZero(fullZero) {
            childExprCount=0;
            expr=nullptr;
            dst=new Operand(se);
    };
    void output(int level);
    ExprNode* getExpr() const { return expr; };
    void addExpr(ExprNode* expr);
    bool isFull();
    int getIValue(){return 0;};
    float getFValue(){return 0;};
    void typeCheck();
    void genCode();
    bool isFullZero() {return fullZero;};
    void setFullZero() {fullZero =true;};
};

class StmtNode : public Node{};

class CompoundStmt : public StmtNode
{
private:
    StmtNode *stmt;
    
public:
    CompoundStmt(StmtNode *stmt) : stmt(stmt) {};
    void output(int level);
    void typeCheck();
    void genCode();
};

class SeqNode : public StmtNode
{
private:
    StmtNode *stmt1, *stmt2;
public:
    SeqNode(StmtNode *stmt1, StmtNode *stmt2) : stmt1(stmt1), stmt2(stmt2){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class DeclStmt : public StmtNode
{
private:
    Id *id;
    ExprNode *expr;  
public:
    DeclStmt(Id *id, ExprNode*expr=nullptr) : id(id), expr(expr){};
    Id* getId(){return id;}
    void output(int level);
    void typeCheck();
    void genCode();
};

class IfStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
public:
    IfStmt(ExprNode *cond, StmtNode *thenStmt) : cond(cond), thenStmt(thenStmt){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class IfElseStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
    StmtNode *elseStmt;
public:
    IfElseStmt(ExprNode *cond, StmtNode *thenStmt, StmtNode *elseStmt) : cond(cond), thenStmt(thenStmt), elseStmt(elseStmt) {};
    void output(int level);
    void typeCheck();
    void genCode();
};

class WhileStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *stmt;

    BasicBlock* condBB, *endBB;

public:
    WhileStmt(ExprNode *cond, StmtNode *stmt) : cond(cond), stmt(stmt){condBB=endBB=nullptr;};
    void setStmt(StmtNode* stmt){this->stmt=stmt;};
    void output(int level);
    void typeCheck();
    void genCode();

    BasicBlock* getCond(){return condBB;};
    BasicBlock* getFinal(){return endBB;};
    void setCondbb(BasicBlock*cond_bb){this->condBB=cond_bb;};
    void setFinalbb(BasicBlock*end_bb){this->endBB=end_bb;};
};

class BreakStmt : public StmtNode {

    WhileStmt* whileStmt;

    public:
        BreakStmt(WhileStmt* whileStmt){this->whileStmt=whileStmt;};
        void output(int level);
    void typeCheck();
    void genCode();
};

class ContinueStmt : public StmtNode {

    WhileStmt* whileStmt;

   public:
    ContinueStmt(WhileStmt* whileStmt){this->whileStmt=whileStmt;};
    void output(int level);
    void typeCheck();
    void genCode();
};

class ReturnStmt : public StmtNode
{
private:
    ExprNode *retValue;
public:
    ReturnStmt(ExprNode*retValue=nullptr) : retValue(retValue) {};
    void output(int level);
    void typeCheck();
    void genCode();
};

class AssignStmt : public StmtNode
{
private:
    ExprNode *lval;
    ExprNode *expr;
public:
    AssignStmt(ExprNode *lval, ExprNode *expr) : lval(lval), expr(expr) {};
    void output(int level);
    void typeCheck();
    void genCode();
};

class ExprStmt : public StmtNode {
   private:
    ExprNode* expr;

   public:
    ExprStmt(ExprNode* expr) : expr(expr){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class EmptyStmt : public StmtNode{
    public:
    EmptyStmt(){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class FunctionDef : public StmtNode
{
private:
    SymbolEntry* se;
    DeclStmt* decl;
    StmtNode* stmt;

   public:
    FunctionDef(SymbolEntry* se, DeclStmt* decl, StmtNode* stmt)
        : se(se), decl(decl), stmt(stmt){};
    void output(int level);
    void deleteCon(BasicBlock*block);
    void typeCheck();
    void genCode();
};

class Ast
{
private:
    Node* root;
public:
    Ast() {root = nullptr;}
    void setRoot(Node*n) {root = n;}
    void output();
    void typeCheck();
    void genCode(Unit *unit);
};


#endif
