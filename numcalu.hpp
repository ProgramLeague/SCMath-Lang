#pragma once
#include "scmath.h"

class numcalu
{
public:
    static double solve(double a, double b, BasicNode* f, int n=1000)
    {
        double c;
        for (int i = 0; i < n; i++)
        {
            c = (a + b) / 2;
            if (scmath::caluExp(f,"x",c) == 0)
                return c;
            else if (scmath::caluExp(f,"x",c)*scmath::caluExp(f,"x",a) > 0) //选择异号的一边
                a = c;
            else
                b = c;
        }
        return c;
    }

    static double integ(double lower, double upper, BasicNode* f, double accuracy = 0.1)
    {
        double result = 0;

        for (; lower <= upper; lower += accuracy)
        {
            result += scmath::caluExp(f,"x",lower)*accuracy;
        }

        return result;
    }
};
