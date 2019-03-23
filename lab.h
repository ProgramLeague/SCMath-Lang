#pragma once
#include "help.h"


class lab
{
public:
    static float avg(vector<string>com)
    {
        float sum=0;
        for(unsigned int i=1;i<com.size();i++)
            sum+=help::tofloat(com[i]);
        return sum/(com.size()-1);
    }

    static float dev(vector<string>com)
    {
        float avg=lab::avg(com);
        float sum=0;
        for(unsigned int i=1;i<com.size();i++)
        {
            float num=help::tofloat(com[i])-avg;
            sum+=num*num;
        }
        return sum/(com.size()-2);
    }

    static tuple<double,double> LeastSquare(vectorNode &x, vectorNode &y)
    {
        double t1=0, t2=0, t3=0, t4=0;
        for(int i=0; i<x.getl(); ++i)
        {
            t1 += x.v[i]*x.v[i];
            t2 += x.v[i];
            t3 += x.v[i]*y.v[i];
            t4 += y.v[i];
        }
        double a = (t3*x.getl() - t2*t4) / (t1*x.getl() - t2*t2);
        //b = (t4 - a*t2) / x.size();
        double b = (t1*t4 - t2*t3) / (t1*x.getl() - t2*t2);
        return make_tuple(a,b);
    }
};
