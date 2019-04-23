#include <iostream>
#include <string>
#include "scmath/ast.h"
#include "scmath/output.h"
#include "scmath/matrix.hpp"
#include "scmath.h"
#include <stdio.h>
#include "help.h"
#include "lab.h"

using namespace std;

void getXY(vectorNode &v1,vectorNode &v2)
{
    cout<<"vector x="<<endl;
    help::getvector(v1);
    cout<<"vector y="<<endl;
    help::getvector(v2);
}

int main()
{
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
            if(com[0]=="mat")
            {
                isCommand=true;
                matrixNode* m=new matrixNode(help::toint(com[2]),help::toint(com[3]));
                Variable *v=record::globalScope.addVariable(com[1]);
                v->setVal(m);
                Variable* pv=record::globalScope.addVariable("ptr"+com[1]);
                pv->setBorrowVal(v);
                help::getmatrix(*m);
            }
            if(com[0]=="vec")
            {
                isCommand=true;
                vectorNode* vec=new vectorNode(help::toint(com[2]));
                Variable *v=record::globalScope.addVariable(com[1]);
                v->setVal(vec);
                Variable* pv=record::globalScope.addVariable("ptr"+com[1]);
                pv->setBorrowVal(v);
                help::getvector(*vec);
            }
            if(com[0]=="del") //都使用指针赋值的话这个命令就没什么用了
            {
                isCommand=true;
                Variable* v=record::globalScope.findVariable(com[1]);
                if(v!=nullptr)
                    v->clearVal();
                else
                {
                    help::t();
                    cout<<"Error: "+com[1]+" is not variable"<<endl;
                }
            }
            if(com[0]=="avg")
            {
                isCommand=true;
                help::t();
                cout<<lab::avg(com)<<endl;
            }
            if(com[0]=="var")
            {
                isCommand=true;
                help::t();
                cout<<lab::var(com)<<endl;
            }
            if(com[0]=="linerFit")
            {
                isCommand=true;
                vectorNode v1(help::toint(com[1]));
                vectorNode v2(help::toint(com[1]));
                getXY(v1,v2);
                double k,b;
                tie(k,b)=lab::LeastSquare(v1,v2);
                help::t();
                cout<<"k:"<<k<<" b:"<<b<<endl;
            }
            if(com[0]=="r")
            {
                isCommand=true;
                vectorNode v1(help::toint(com[1]));
                vectorNode v2(help::toint(com[1]));
                getXY(v1,v2);
                help::t();
                cout<<"r:"<<lab::r(v1,v2)<<endl;
            }
        }
        if(isCommand==false)
        {
            try
            {
                BasicNode* tree=scmath::toAST(input);
                BasicNode* result=tree->eval();
                help::t();
                scmath::output(result);
                //如果局部求值这个会出错，因为字面量会delete两次
                copyHelp::delTree(result);
                copyHelp::delTree(tree);    
            }
            catch(Excep e)
            {
                cout<<"Error: "<<e.getInform();
            }
            cout<<endl;
        }
    }
}
