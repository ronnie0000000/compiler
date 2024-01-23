#include "Function.h"
#include <list>
#include "Type.h"
#include "Unit.h"

extern FILE* yyout;

Function::Function(Unit* u, SymbolEntry* s) {
    u->insertFunc(this);
    entry = new BasicBlock(this);
    sym_ptr = s;
    parent = u;
}

Function::~Function() {
    // auto delete_list = block_list;
    // for (auto& i : delete_list)
    //     delete i;
    // parent->removeFunc(this);
}

// remove the basicblock bb from its block_list.
void Function::remove(BasicBlock* bb) {
    block_list.erase(std::find(block_list.begin(), block_list.end(), bb));
}

//函数定义语句
void Function::output() const {
    FunctionType* funcType = dynamic_cast<FunctionType*>(sym_ptr->getType());
    Type* retType = funcType->getRetType();
    std::vector<SymbolEntry*> paramsSe = funcType->getParamsSe();
    //没有参数
    if (paramsSe.size()==0)
        fprintf(yyout, "define %s %s() {\n", retType->toStr().c_str(),sym_ptr->toStr().c_str());
    //有参数，一次打印参数
    else {
        fprintf(yyout, "define %s %s(", retType->toStr().c_str(),sym_ptr->toStr().c_str());
        long unsigned int i = 0;
        for (i; i < paramsSe.size(); i++) {
            if (i!=0)
                fprintf(yyout, ", ");
            fprintf(yyout, "%s %s", paramsSe[i]->getType()->toStr().c_str(), paramsSe[i]->toStr().c_str());
        }
        fprintf(yyout, ") {\n");
    }

//框架代码
//完成每个函数的output
    std::set<BasicBlock*> v;
    std::list<BasicBlock*> q;
    q.push_back(entry);
    v.insert(entry);
    while (!q.empty()) {
        auto bb = q.front();
        q.pop_front();
        bb->output();
        for (auto succ = bb->succ_begin(); succ != bb->succ_end(); succ++) {
            if (v.find(*succ) == v.end()) {
                v.insert(*succ);
                q.push_back(*succ);
            }
        }
    }
    //最后输出一个右大括号
    fprintf(yyout, "}\n");
}
