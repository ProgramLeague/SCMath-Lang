#include <iostream>
#include <string>
#include "scmath/ast.h"
#include "scmath/output.h"
#include "scmath/matrix.hpp"
#include "scmath.h"
#include <stdio.h>
#include "help.h"

using namespace std;

void getmatrix(matrixNode &A)
{
    printf("{\n");
    for (unsigned int i = 0; i < A.getr(); i++)
    {
        help::t();
        for (unsigned int j = 0; j < A.getc(); j++)
        {
            scanf("%lf", &A.m[i][j]);
        }
    }
    printf("}\n");
    getchar();
}

void getvector(vectorNode &B)
{
    printf("{\n");
    help::t();
    for (unsigned int i = 0; i < B.getl(); i++)
    {
        scanf("%lf", &B.v[i]);
    }
    printf("}\n");
    getchar();
}

int main()
{
    map<string,BasicNode*>allExp; //丑陋的临时解法

    while(1)
    {
        bool isCommand=false;
        string input;
        printf(">>");
        getline(cin,input);
        if(input=="")
            continue;
        if(input.find(" ")!=-1) //是命令初步判断
        {
            auto com=help::split(input," ");
            if(com[0]=="matrix")
            {
                isCommand=true;
                matrixNode* m=new matrixNode(help::toint(com[2]),help::toint(com[3]));
                Variable *v=record::globalScope.addVariable(com[1]);
                v->setVal(m);
                Variable* pv=record::globalScope.addVariable("ptr"+com[1]);
                pv->setBorrowVal(v);
                getmatrix(*m);
            }
            if(com[0]=="vector")
            {
                isCommand=true;
                vectorNode* vec=new vectorNode(help::toint(com[2]));
                Variable *v=record::globalScope.addVariable(com[1]);
                v->setVal(vec);
                Variable* pv=record::globalScope.addVariable("ptr"+com[1]);
                pv->setBorrowVal(v);
                getvector(*vec);
            }
            if(com[0]=="del") //都使用指针赋值的话这个命令就没什么用了
            {
                isCommand=true;
                if(record::globalScope.haveVariable(com[1]))
                    record::globalScope.variableList[com[1]]->clearVal();
                else
                    cout<<"Error: "+com[1]+" is not variable"<<endl;
            }
        }
        if(isCommand==false)
        {
            BasicNode* tree=scmath::toAST(input);
            BasicNode* result=tree->eval();
            help::t();
            scmath::output(result);
            //如果局部求值这个会出错，因为字面量会delete两次
            copyHelp::delTree(result);
            copyHelp::delTree(tree);
            cout<<endl;
        }
    }
}
