#pragma once
#include "scmath/ast.h"
#include "scmath/nodetype.h"
#include "scmath/output.h"

class scmath
{
public:
    static void Simplificate(BasicNode *&now);
    static BasicNode* Derivation(BasicNode* now, const string &value);
    static BasicNode* toAST(string s)
    {
        return ast::ToAST(s);
    }
    static BasicNode* eval(BasicNode *tree)
    {
        return copyHelp::copyNode(tree)->eval();
    }
    static double getVal(BasicNode *tree)
    {
        if(tree->getType() == Num)
            return ((NumNode*)tree)->getNum();
        else
            throw string("不是数字右值不可调用GetVal");
    }
    static void output(BasicNode *tree)
    {
        output::outputAST(tree);
    }
    static double caluExp(BasicNode* f,string name,double val)
    {
        record::globalScope.variableList[name]->setVal(new NumNode(val));
        BasicNode* result=scmath::eval(f);
        return scmath::getVal(result);
    }
};

