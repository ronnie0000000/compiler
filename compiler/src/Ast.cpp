#include "Ast.h"
#include "SymbolTable.h"
#include "Unit.h"
#include "Instruction.h"
#include "IRBuilder.h"
#include <string>
#include "Type.h"

#include <stack>
#include <vector>
#include <cassert>

extern Unit unit;
extern FILE *yyout;
int Node::counter = 0;
IRBuilder* Node::builder = nullptr;

Type* retType = nullptr;
bool ret = false;

Node::Node()
{
    seq = counter++;
}

void Node::backPatch(std::vector<Instruction*> &list, BasicBlock*bb)
{
    for(auto &inst:list)
    {
        if(inst->isCond())
            dynamic_cast<CondBrInstruction*>(inst)->setTrueBranch(bb);
        else if(inst->isUncond())
            dynamic_cast<UncondBrInstruction*>(inst)->setBranch(bb);
    }
}

std::vector<Instruction*> Node::merge(std::vector<Instruction*> &list1, std::vector<Instruction*> &list2)
{
    std::vector<Instruction*> res(list1);
    res.insert(res.end(), list2.begin(), list2.end());
    return res;
}

void FunctionDef::deleteCon(BasicBlock* block){
        Instruction* i = (block)->begin();
        Instruction* last = (block)->rbegin();
        while (i != last) {
            if (i->isCond() || i->isUncond()) {
                (block)->remove(i);
            }
            i = i->getNext();
        }
}

void Ast::genCode(Unit *unit)
{
    IRBuilder *builder = new IRBuilder(unit);
    Node::setIRBuilder(builder);
    root->genCode();
}

void FunctionDef::genCode()
{
    Unit* unit = builder->getUnit();
    Function* func = new Function(unit, se);
    //插入函数的入口点位置
    BasicBlock* entry = func->getEntry();
    builder->setInsertBB(entry);
    
    //根据函数特性，如果不为空则生成中间代码
    if (this->decl!=nullptr){decl->genCode();}
    if (this->stmt!=nullptr){stmt->genCode();}
    /**
     * Construct control flow graph. You need do set successors and predecessors
     * for each basic block. Todo
     */

    for(auto block=func->begin();block!=func->end();block++){
        // jmp only happen at the end of a block
        Instruction* ins_begin=(*block)->begin();
        Instruction* ins_end=(*block)->rbegin();

        //删除基本块中的条件或无条件跳转语句
        Instruction* lastIns = (*block)->rbegin();
        deleteCon(*block);
        
        //针对函数的最后一条语句进行流程图绘制
        if(ins_end->isCond()){
            //如果是条件跳转语句
            BasicBlock* truebranch, *falsebranch;
            //设置好两个分支
            truebranch = dynamic_cast<CondBrInstruction*>(ins_end)->getTrueBranch();
            if(truebranch->empty()){
                //最后要做的工作就是在最后一个分支的位置要指定好ret语句
                if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::intType) {
                    new RetInstruction(new Operand(new ConstantSymbolEntry(TypeSystem::intType, 0)),truebranch);
                } else if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::floatType) {
                    new RetInstruction(new Operand(new ConstantSymbolEntry(TypeSystem::floatType, 0.0f)),truebranch);
                } else if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::voidType) {
                    new RetInstruction(nullptr, truebranch);
                }
            }
            falsebranch = dynamic_cast<CondBrInstruction*>(ins_end)->getFalseBranch();
            if(falsebranch->empty()){
                //保证无论函数是true还是false都有正确的ret语句

                if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::intType) {
                    new RetInstruction(new Operand(new ConstantSymbolEntry(TypeSystem::intType, 0)),falsebranch);
                } else if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::floatType) {
                    new RetInstruction(new Operand(new ConstantSymbolEntry(TypeSystem::floatType, 0.0f)),falsebranch);
                } else if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::voidType) {
                    new RetInstruction(nullptr, falsebranch);
                }
            }
            //框架代码，生成控制流图
            (*block)->addSucc(truebranch);
            (*block)->addSucc(falsebranch);
            truebranch->addPred((*block));
            falsebranch->addPred((*block));
        }
        else if(ins_end->isUncond()){
            BasicBlock* branch = dynamic_cast<UncondBrInstruction*>(ins_end)->getBranch();
            branch->addPred((*block));
            (*block)->addSucc(branch);
            //无条件跳转指令的生成代码
            if(branch->empty()){
                if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::intType) {
                    new RetInstruction(new Operand(new ConstantSymbolEntry(TypeSystem::intType, 0)),branch);
                } else if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::floatType) {
                    new RetInstruction(new Operand(new ConstantSymbolEntry(TypeSystem::floatType, 0.0f)),branch);
                } else if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::voidType) {
                    new RetInstruction(nullptr, branch);
                }
            }
        }
    }
}

void BinaryExpr::genCode()
{
    //运算部分的代码生成
    BasicBlock *bb = builder->getInsertBB();
    Function *func = bb->getParent();
    if (op == LOGIC_AND)
    {
        BasicBlock *trueBB = new BasicBlock(func);  // if the result of lhs is true, jump to the trueBB.
        expr1->genCode();
        backPatch(expr1->trueList(), trueBB);
        builder->setInsertBB(trueBB);               // set the insert point to the trueBB so that intructions generated by expr2 will be inserted into it.
        expr2->genCode();
        //只有都是true才是true
        true_list = expr2->trueList();
        //false则一起merge
        false_list = merge(expr1->falseList(), expr2->falseList());
    }
    else if(op == LOGIC_OR)
    {
        // Todo
        BasicBlock *trueBB = new BasicBlock(func);
        expr1->genCode();
        backPatch(expr1->falseList(), trueBB);
        builder->setInsertBB(trueBB);
        expr2->genCode();
        //但是只要有一个true就可以
        true_list = merge(expr1->trueList(), expr2->trueList());
        //全是false才有效
        false_list = expr2->falseList();
    }
    else if(op >= MORE && op <= UNEQUAL)
    {
        BasicBlock* samebb=new BasicBlock(func);
        // Todo
        expr1->genCode();
        expr2->genCode();
        Operand* src1 = expr1->getOperand();
        Operand* src2 = expr2->getOperand();
        if (src1->getType()->isBool()) {
            //可能需要进行类型转换，因为把int直接当成了bool来做判断
            Operand* dst = new Operand(new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel()));
            new ChanInstruction(dst, src1, bb);
            src1 = dst;
        }
        if (src2->getType()->isBool()) {
            Operand* dst = new Operand(new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel()));
            new ChanInstruction(dst, src2, bb);
            src2 = dst;
        }
        int cmpOp=-1;
        //比较指令的生成
        switch (op)
        {
        case MORE:
            cmpOp=CmpInstruction::G;
            break;
        case LESS:
            cmpOp=CmpInstruction::L;
            break;
        case MOREOREQUAL:
            cmpOp=CmpInstruction::GE;
            break;
        case LESSOREQUAL:
            cmpOp=CmpInstruction::LE;
            break;
        case EQUAL:
            cmpOp=CmpInstruction::E;
            break;
        case UNEQUAL:
            cmpOp=CmpInstruction::NE;
            break;
        default:
            fprintf(stderr,"no useful op\n");
        }
        //比较指令生成
        new CmpInstruction(cmpOp,this->getOperand(),src1,src2,bb);
        //两个分支分别绘制流程图
        BasicBlock* truebranch, *falsebranch;
        truebranch=new BasicBlock(func);
        falsebranch=new BasicBlock(func);
        true_list.push_back(new CondBrInstruction(truebranch,samebb,this->getOperand(),bb));
        false_list.push_back(new UncondBrInstruction(falsebranch,samebb));
    }
    else if(op >= ADD && op <= MOD)
    {
        expr1->genCode();
        expr2->genCode();
        Operand *src1 = expr1->getOperand();
        Operand *src2 = expr2->getOperand();
        int opcode;
        switch (op)
        {
        case ADD:
            opcode = BinaryInstruction::ADD;
            break;
        case SUB:
            opcode = BinaryInstruction::SUB;
            break;
        case MUL:
            opcode = BinaryInstruction::MUL;
            break;
        case MOD:
            opcode = BinaryInstruction::MOD;
            break;
        case DIV:
            opcode = BinaryInstruction::DIV;
            break;
        }
        new BinaryInstruction(opcode, dst, src1, src2, bb);
    }
}

void Constant::genCode()
{
    // we don't need to generate code.
}

void Id::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    Operand *addr = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getAddr();
    //根据类型去从内存load
    if(this->getType()->isInt()||this->getType()->isFloat()||this->getType()->isBool()){
        new LoadInstruction(dst, addr, bb);
    }
}


void IfStmt::genCode()
{
    //不同的分支放在不同的block下，同时对cond做关联
    Function *func;
    BasicBlock *then_bb, *end_bb;

    func = builder->getInsertBB()->getParent();
    then_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);
    cond->genCode();
    backPatch(cond->trueList(), then_bb);
    backPatch(cond->falseList(), end_bb);

    builder->setInsertBB(then_bb);
    thenStmt->genCode();
    then_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, then_bb);

    builder->setInsertBB(end_bb);
}

void IfElseStmt::genCode()
{
    Function* func;

    BasicBlock *thenbb, *elsebb, *finalbb ;
    func = builder->getInsertBB()->getParent();
    thenbb = new BasicBlock(func);
    elsebb = new BasicBlock(func);
    finalbb = new BasicBlock(func);
    //在当前基本快就能填写代码
    cond->genCode();
    backPatch(cond->trueList(), thenbb);
    backPatch(cond->falseList(), elsebb);
    builder->setInsertBB(thenbb);
    thenStmt->genCode();
    thenbb = builder->getInsertBB();
    //finalbb需要挂靠在两个分支上，而且都是无条件取得
    new UncondBrInstruction(finalbb, thenbb);
    builder->setInsertBB(elsebb);
    elseStmt->genCode();
    elsebb = builder->getInsertBB();
    new UncondBrInstruction(finalbb, elsebb);
    builder->setInsertBB(finalbb);
}

void EmptyStmt::genCode()
{
    //空语句不用生成代码
}

void ExprStmt::genCode()
{
    if(this->expr)
        this->expr->genCode();
}

void ContinueStmt::genCode()
{
    Function* func = builder->getInsertBB()->getParent();
    BasicBlock* n = new BasicBlock(func);
    BasicBlock* bb = builder->getInsertBB();
    //也就是回到whilestmt开始的地方，并且做一次条件判断，这个时候条件判断后面就应该已经生成了两个分支
    new UncondBrInstruction(((WhileStmt*)whileStmt)->getCond(), bb);
    builder->setInsertBB(n);
}

void BreakStmt::genCode()
{
    Function* func = builder->getInsertBB()->getParent();
    BasicBlock* n= new BasicBlock(func);
    BasicBlock* bb = builder->getInsertBB();
    //和上面那个同理，直接跳转到final去就好了
    new UncondBrInstruction(((WhileStmt*)whileStmt)->getFinal(), bb);
    builder->setInsertBB(n);
}

void WhileStmt::genCode()
{
     Function* func;
    //1.条件块
    //2.正确的分支
    //3.出去的分支
    //4.当前的分支
    BasicBlock *condbb, *truebb, *finalbb, *nowbb;
    nowbb = builder->getInsertBB();
    func = builder->getInsertBB()->getParent();
    condbb = new BasicBlock(func);
    truebb = new BasicBlock(func);
    finalbb = new BasicBlock(func);
    setCondbb(condbb);
    setFinalbb(finalbb);

    //增加无条件跳转语句，随后生成条件的中间代码
    new UncondBrInstruction(condbb, nowbb);
    builder->setInsertBB(condbb);
    cond->genCode();
    backPatch(cond->trueList(), truebb);
    backPatch(cond->falseList(), finalbb);
    builder->setInsertBB(truebb);
    stmt->genCode();
    truebb = builder->getInsertBB();

    //同理，在truebb加入条件判断，每执行一回合就要去cond
    new UncondBrInstruction(condbb, truebb);
    builder->setInsertBB(finalbb);
}


void CompoundStmt::genCode()
{
    // Todo
    if(this->stmt)
        this->stmt->genCode();
}


void SeqNode::genCode()
{
    // Todo
    if(this->stmt1)
        this->stmt1->genCode();
    if(this->stmt2)
        this->stmt2->genCode();
}

void DeclStmt::genCode()
{
 IdentifierSymbolEntry* se = dynamic_cast<IdentifierSymbolEntry*>(id->getSymbolEntry());
    if (se->isGlobal()) {
        //全局变量的填写
        Operand* addr;
        SymbolEntry* addr_se;
        addr_se = new IdentifierSymbolEntry(*se);
        addr_se->setType(new PointerType(se->getType()));
        addr = new Operand(addr_se);
        se->setAddr(addr);
        unit.insertGlobal(se);
    } else if (se->isLocal() || se->isParam()) {
        //局部变量的填写
        Function* func = builder->getInsertBB()->getParent();
        BasicBlock* entry = func->getEntry();
        Instruction* alloca;
        Operand* addr;
        SymbolEntry* addr_se;
        Type* type;
        type = new PointerType(se->getType());
        addr_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());
        addr = new Operand(addr_se);
        alloca = new AllocaInstruction(addr, se);
                                                              // allocate space for local id in function stack.
        entry->insertFront(alloca);                           // allocate instructions should be inserted
                                                              // into the begin of the entry block.
        Operand* temp;
        if (se->isParam()){
            temp = se->getAddr();
        }
        se->setAddr(addr);  

        //有初始化的情况
        if (expr) {
            //先计算值，再把值写入内存
                BasicBlock* bb = builder->getInsertBB();
                expr->genCode();
                Operand* src = expr->getOperand();
                new StoreInstruction(addr, src, bb);
        }
        if (se->isParam()) {
            //如果是参数，直接store
            BasicBlock* bb = builder->getInsertBB();
            new StoreInstruction(addr, temp, bb);
        }
    }
    //可能一次声明很多id
    if (this->getNext()) {
        this->getNext()->genCode();
    }
}

void ReturnStmt::genCode()
{
    Operand* ret;
    if (retValue!=nullptr) {
        //如果ret的值不为空，那么先生成代码再提取需要的东西
        retValue->genCode();
        ret = retValue->getOperand();
    }else{
        ret=nullptr;
    }
    BasicBlock* bb = builder->getInsertBB();
    new RetInstruction(ret, bb);
}

void AssignStmt::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    expr->genCode();
    Operand *addr;
    if(lval->getType()->isInt()||lval->getType()->isFloat())
        addr = dynamic_cast<IdentifierSymbolEntry*>(lval->getSymPtr())->getAddr();
    Operand *src = expr->getOperand();
    
    new StoreInstruction(addr, src, bb);
}

void ArrayInit::genCode()
{

}

FuncExpr::FuncExpr(SymbolEntry* se, ExprNode* param = nullptr): ExprNode(se), param(param){
    if(se){
        if(dynamic_cast<FunctionType*>(se->getType())->getRetType()->isInt()){
            SymbolEntry* temp = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            dst = new Operand(temp);
        }
        else if(dynamic_cast<FunctionType*>(se->getType())->getRetType()->isFloat()){
            SymbolEntry* temp = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            dst = new Operand(temp);
        }
    }
};
void FuncExpr::genCode()
{
    std::vector<Operand*> operands;
    ExprNode* paramTemp = param;
    while (paramTemp) {
        //把需要的参数压进去
        paramTemp->genCode();
        operands.push_back(paramTemp->getOperand());
        paramTemp = (ExprNode*)paramTemp->getNext();
    }
    BasicBlock* bb = builder->getInsertBB();
    new CallInstruction(dst, symbolEntry, operands, bb);
}


void Ast::typeCheck()
{
    if(root != nullptr)
        root->typeCheck();
}

void FunctionDef::typeCheck()
{
    // Todo
    ret = false;

    Type* funcRetType=((FunctionType*)(this->se->getType()))->getRetType();
    if(this->stmt==nullptr && funcRetType!=TypeSystem::voidType){
        fprintf(stderr, "function %s must return a vaild value\n",this->se->toStr().c_str());
        return;
    }
    
    retType = funcRetType;
    if(this->stmt != nullptr)
        this->stmt->typeCheck();

    if(!funcRetType->isVoid() && !ret){
        fprintf(stderr, "function \"%s\" shoule return a vaild type\n",this->se->toStr().c_str());

        assert(!funcRetType->isVoid() && !ret == false);
    }
}

void BinaryExpr::typeCheck()
{
    // Todo
    if(this->expr1->getType()->isVoid() || this->expr2->getType()->isVoid()){
        fprintf(stderr, "void expr cannot in a BinaryExpr\n");
        assert(false);
    }
}

void Constant::typeCheck()
{
    // Todo
}

void Id::typeCheck()
{
    // Todo
}

void IfStmt::typeCheck()
{
    // Todo
    if(this->cond)
        this->cond->typeCheck();
    if(this->thenStmt!=nullptr)
        this->thenStmt->typeCheck();
}

void IfElseStmt::typeCheck()
{
    // Todo
    if(this->thenStmt)
        this->thenStmt->typeCheck();
    if(this->elseStmt)
        this->elseStmt->typeCheck();
}

void CompoundStmt::typeCheck()
{
    // Todo
    if(this->stmt)
        this->stmt->typeCheck();
}

void SeqNode::typeCheck()
{
    // Todo
    if(this->stmt1)
        this->stmt1->typeCheck();
    if(this->stmt2)
        this->stmt2->typeCheck();
}

void DeclStmt::typeCheck()
{
    // Todo
    if(this->expr)
        expr->typeCheck();
    
    if(this->getNext())
        this->getNext()->typeCheck();
}

void ReturnStmt::typeCheck()
{
    // Todo
    Type* funcRetType;
    if(!this->retValue && !retType->isVoid()){
        fprintf(stderr, "you should return %s, but return void\n",retType->toStr().c_str());
        assert(!this->retValue && !retType->isVoid() == false);
    }
    if(!this->retValue && retType->isVoid()){
        goto Out;
    }
    if(this->retValue && retType->isVoid()){
        fprintf(stderr, "you should return void, but return %s\n",this->retValue->getSymbolEntry()->getType()->toStr().c_str());
        assert(this->retValue && retType->isVoid() == false);
    }
    funcRetType = this->retValue->getSymbolEntry()->getType();
    if(funcRetType->isFunc())
        funcRetType = dynamic_cast<FunctionType*>(funcRetType)->getRetType();
    if(this->retValue && funcRetType!=retType){
        if((retType->isInt() && funcRetType->isInt())||(retType->isFloat() && funcRetType->isFloat()))
            goto Out;
        if(this->retValue->getSymbolEntry()->getType()->isFunc())
        fprintf(stderr, "you should return:%s, but return %s\n",retType->toStr().c_str(),
                this->retValue->getSymbolEntry()->getType()->toStr().c_str());
        assert(this->retValue->getSymbolEntry()->getType() ==retType);
    }
Out:
    ret = true;
}

void AssignStmt::typeCheck()
{
    // Todo
    if(this->lval)
        this->lval->typeCheck();
    if(this->expr)
        this->expr->typeCheck();
}

void EmptyStmt::typeCheck()
{
    //to nothing
}

void ExprStmt::typeCheck()
{
    if(expr)
        expr->typeCheck();
}

void ContinueStmt::typeCheck()
{
    if(this->whileStmt==nullptr)
        fprintf(stderr, "\"continue\" should be included in a while stmt ");
}

void BreakStmt::typeCheck()
{
    if(this->whileStmt==nullptr)
        fprintf(stderr, "\"break\" should be included in a while stmt ");
}

void WhileStmt::typeCheck()
{
    if(this->stmt)
        this->stmt->typeCheck();
}

void ArrayInit::typeCheck()
{

}

void FuncExpr::typeCheck()
{

}

void UnaryExpr::typeCheck()
{
    if(this->expr->getType()->isVoid()){
        fprintf(stderr, "void expr cannot in a unaryExpr\n");
        assert(false);
    }
}

void Node::setNext(Node* node) {
    Node* n = this;
    while (n->getNext()) {
        n = n->getNext();
    }
    if (n == this) {
        this->next = node;
    } else {
        n->setNext(node);
    }
}

void Ast::output()
{
    fprintf(yyout, "program\n");
    if(root != nullptr)
        root->output(4);
}

Type* ExprNode::getType(){
    if(this->symbolEntry->getType()->isFunc())
        return ((FunctionType*)this->symbolEntry->getType())->getRetType();
    return this->symbolEntry->getType();
}

void UnaryExpr::output(int level) {
    std::string op_str;
    switch (op) {
        case NOT:
            op_str = "not";
            break;
        case SUB:
            op_str = "minus";
            break;
        case ADD:
            op_str = "add";    
    }
    fprintf(yyout, "%*cUnaryExpr\top: %s\n", level, ' ', op_str.c_str());
    expr->output(level + 4);
}

int UnaryExpr::getIValue() {
    int v;
    switch(op) {
        case NOT :
            v=!(expr->getIValue());
            break;
        case SUB:
            v=-(expr->getIValue());
            break;
        case ADD:
            v=+(expr->getIValue());
            break;
    }
    return v;
}

float UnaryExpr::getFValue() {
    float v;
    switch(op) {
        case NOT :
            v=!(expr->getFValue());
            break;
        case SUB:
            v=-(expr->getFValue());
            break;
        case ADD:
            v=+(expr->getFValue());
            break;
    }
    return v;
}

void FuncExpr::output(int level) {
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    fprintf(yyout, "%*cCallExpr\tfunction name: %s\tscope: %d\ttype: %s\n",
            level, ' ', name.c_str(), scope, type.c_str());
    Node* temp = param;
    while (temp) {
        temp->output(level + 4);
        temp = temp->getNext();
    }
}

void BinaryExpr::output(int level)
{
    std::string op_str;
    switch(op)
    {
        case ADD:
            op_str = "add";
            break;
        case SUB:
            op_str = "sub";
            break;
        case DIV:
            op_str = "div";
            break;
        case MUL:
            op_str = "mul";
            break;
        case MOD:
            op_str = "mod";
            break;
        case LOGIC_AND:
            op_str = "logic and";
            break;
        case LOGIC_OR:
            op_str = "logic and";
            break;
        case AND:
            op_str = "and";
            break;
        case OR:
            op_str = "or";
            break;
        case LESS:
            op_str = "less";
            break;
        case LESSOREQUAL:
            op_str="lessORequal";
            break;
        case MORE:
            op_str = "more";
            break;
        case MOREOREQUAL:
            op_str = "moreOrequal";
            break;
        case EQUAL:
            op_str = "equal";
            break;
        case UNEQUAL:
            op_str = "unequal";
            break;
        
        
    }
    fprintf(yyout, "%*cBinaryExpr\top: %s\n", level, ' ', op_str.c_str());
    expr1->output(level + 4);
    expr2->output(level + 4);
}

int BinaryExpr::getIValue(){
    int v;
    switch(op){
        case ADD:
            v=expr1->getIValue() + expr2->getIValue();
            break;
        case SUB:
            v=expr1->getIValue() - expr2->getIValue();
            break;
        case MUL:
            v=expr1->getIValue() * expr2->getIValue();
            break;
        case DIV:
            v=expr1->getIValue() / expr2->getIValue();
            break;
        case MOD:
            v=expr1->getIValue() % expr2->getIValue();
            break;
        case LOGIC_AND:
            v=expr1->getIValue() && expr2->getIValue();
            break;
        case LOGIC_OR:
            v=expr1->getIValue() || expr2->getIValue();
            break;
        case LESS:
            v=expr1->getIValue() < expr2->getIValue();
            break;
        case LESSOREQUAL:
            v=expr1->getIValue() <= expr2->getIValue();
            break;
        case MORE:
            v=expr1->getIValue() > expr2->getIValue();
            break;
        case MOREOREQUAL:
            v=expr1->getIValue() >= expr2->getIValue();
            break;
        case EQUAL:
            v=expr1->getIValue() == expr2->getIValue();
            break;
        case UNEQUAL:
            v=expr1->getIValue() != expr2->getIValue();
            break;
    }
    return v;
}

float BinaryExpr::getFValue(){
    float v;
    switch(op){
        case ADD:
            v=expr1->getFValue() + expr2->getFValue();
            break;
        case SUB:
            v=expr1->getFValue() - expr2->getFValue();
            break;
        case MUL:
            v=expr1->getFValue() * expr2->getFValue();
            break;
        case DIV:
            v=expr1->getFValue() / expr2->getFValue();
            break;
        case MOD:
            //这里c++要求只能是整数，所以强行取整就行
            v=expr1->getIValue() % expr2->getIValue();
            break;
        case LOGIC_AND:
            v=expr1->getFValue() && expr2->getFValue();
            break;
        case LOGIC_OR:
            v=expr1->getFValue() || expr2->getFValue();
            break;
        case LESS:
            v=expr1->getFValue() < expr2->getFValue();
            break;
        case LESSOREQUAL:
            v=expr1->getFValue() <= expr2->getFValue();
            break;
        case MORE:
            v=expr1->getFValue() > expr2->getFValue();
            break;
        case MOREOREQUAL:
            v=expr1->getFValue() >= expr2->getFValue();
            break;
        case EQUAL:
            v=expr1->getFValue() == expr2->getFValue();
            break;
        case UNEQUAL:
            v=expr1->getFValue() != expr2->getFValue();
            break;
    }
    return v;
}

void Constant::output(int level)
{
    std::string type, value;
    type = symbolEntry->getType()->toStr();
    value = symbolEntry->toStr();
    fprintf(yyout, "%*cIntegerLiteral\tvalue: %s\ttype: %s\n", level, ' ',
            value.c_str(), type.c_str());
}

int Constant::getIValue(){
    int v;
    v=((ConstantSymbolEntry*)symbolEntry)->getValue();
    return v;
}
float Constant::getFValue(){
    float v;
    v=((ConstantSymbolEntry*)symbolEntry)->getFvalue();
    return v;
}

void Id::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    fprintf(yyout, "%*cId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
            name.c_str(), scope, type.c_str());
}
void ArrayInit::output(int level)
{
    std::string type;
    type = symbolEntry->getType()->toStr();
    if(!fullZero){
        fprintf(yyout, "%*ctype: %s\n", level, ' ',type.c_str());
        ExprNode*temp=expr;
        while (temp){
            temp->output(level + 4);
            temp=(ExprNode*)temp->getNext();
        }
    }
    else{
        fprintf(yyout, "%*ctype: %s\tzero array\n", level, ' ',type.c_str());
    }
}
void ArrayInit::addExpr(ExprNode* expr){
    fullZero=false;
    childExprCount++;
    if(this->expr==nullptr){
        this->expr=expr;
        return;
    }
    this->expr->setNext(expr);
}

bool ArrayInit::isFull(){
    ArrayType* type = (ArrayType*)(this->symbolEntry->getType());
    return childExprCount == type->getLength();
}

void CompoundStmt::output(int level)    
{
    fprintf(yyout, "%*cCompoundStmt\n", level, ' ');
    if(stmt)
        stmt->output(level + 4);
}

void SeqNode::output(int level)
{
    fprintf(yyout, "%*cSequence\n", level, ' ');
    stmt1->output(level + 4);
    stmt2->output(level + 4);
}

void DeclStmt::output(int level)
{
    fprintf(yyout, "%*cDeclStmt\n", level, ' ');
    id->output(level + 4);
    if (expr)
        expr->output(level + 4);
    if (this->getNext()) {
        this->getNext()->output(level);
    }
}

void IfStmt::output(int level)
{
    fprintf(yyout, "%*cIfStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
}

void IfElseStmt::output(int level)
{
    fprintf(yyout, "%*cIfElseStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
    elseStmt->output(level + 4);
}

void WhileStmt::output(int level) {
    fprintf(yyout, "%*cWhileStmt\n", level, ' ');
    cond->output(level + 4);
    stmt->output(level + 4);
}

void BreakStmt::output(int level) {
    fprintf(yyout, "%*cBreakStmt\n", level, ' ');
}

void ContinueStmt::output(int level) {
    fprintf(yyout, "%*cContinueStmt\n", level, ' ');
}

void ReturnStmt::output(int level)
{
    fprintf(yyout, "%*cReturnStmt\n", level, ' ');
    if(retValue!=nullptr)
        retValue->output(level + 4);
}

void AssignStmt::output(int level)
{
    fprintf(yyout, "%*cAssignStmt\n", level, ' ');
    lval->output(level + 4);
    expr->output(level + 4);
}

void FunctionDef::output(int level)
{
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionDefine\tfunction name: %s\ttype: %s\n", level,
            ' ', name.c_str(), type.c_str());
    if (decl) {
        decl->output(level + 4);
    }
    stmt->output(level + 4);
}

void ExprStmt::output(int level) {
    fprintf(yyout, "%*cExprStmt\n", level, ' ');
    expr->output(level + 4);
}

void EmptyStmt::output(int level) {
    fprintf(yyout, "%*cExprStmt\n", level, ' ');
}

void UnaryExpr::genCode()
{
    BasicBlock* bb = builder->getInsertBB();
    expr->genCode();
    Type* unaryExprType = expr->getType();
    Operand* src = expr->getOperand();
    Operand* zero = nullptr;
    switch (op)
    {
    case SUB:
        if(unaryExprType->isFloat())
            zero = new Operand(new ConstantSymbolEntry(TypeSystem::floatType,0.0f));
        else if(unaryExprType->isBool()){
            zero = new Operand(new ConstantSymbolEntry(TypeSystem::intType,0));
            src = new Operand(new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel()));
            new ChanInstruction(src, expr->getOperand(), bb);
        }
        else
            zero = new Operand(new ConstantSymbolEntry(TypeSystem::intType,0));
        new BinaryInstruction(BinaryInstruction::SUB, dst, zero, src, bb);
        break;
    case NOT:
        if(unaryExprType->isInt() || unaryExprType->isFloat()){
            Operand* temp = new Operand(new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel()));
            new CmpInstruction(CmpInstruction::NE, temp, src, new Operand(new ConstantSymbolEntry(TypeSystem::intType, 0)),bb);
            src = temp;
        }
        new NotInstruction(dst, src, bb);
    }
}
