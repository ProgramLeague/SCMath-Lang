#pragma once
#include "help.h"

class lab
{
private:
    static float avg(vectorNode v)
    {
        float sum=0;
        for(unsigned int i=0;i<v.getl();i++)
            sum+=v.v[i];
        return sum/v.getl();
    }

    static float err(vectorNode v, float avg=-1)
    {
        if(avg==-1)
        {
            avg=lab::avg(v);
        }
        float sum=0;
        for(unsigned int i=0;i<v.getl();i++)
        {
            float num=v.v[i]-avg;
            sum+=num*num;
        }
        return sum;
    }

public:
    static float avg(vector<string>com)
    {
        //vectorNode v(com.size()-1);
        vectorNode v=help::toVectorNode(com);
        return avg(v);
    }

    static float var(vector<string>com)
    {
        auto v=help::toVectorNode(com);
        return err(v)/v.getl();
    }

    static float r(vectorNode &x, vectorNode &y)
    {
        float avgx=avg(x);
        float avgy=avg(y);
        float lxx=err(x,avgx);
        float lyy=err(y,avgy);

        float lxy=0;
        for(unsigned int i=0;i<x.getl();i++)
        {
            float num1=x.v[i]-avgx;
            float num2=y.v[i]-avgy;
            lxy+=abs(num1*num2);
        }

        return lxy/(sqrt(lxx*lyy));
    }

    static tuple<double,double> LeastSquare(vectorNode &x, vectorNode &y)
    {
        double t1=0, t2=0, t3=0, t4=0;
        for(unsigned int i=0; i<x.getl(); ++i)
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
