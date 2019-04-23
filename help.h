#pragma once
#include <vector>
#include <string>
#include "scmath/matrix.hpp"
using namespace std;

class help
{
public:
    static vector<string> split(const string &s, const string &seperator)
    {
        vector<string> result;
        typedef string::size_type string_size;
        string_size i = 0;

        while(i != s.size()){
          //找到字符串中首个不等于分隔符的字母；
          int flag = 0;
          while(i != s.size() && flag == 0){
            flag = 1;
            for(string_size x = 0; x < seperator.size(); ++x)
            if(s[i] == seperator[x]){
              ++i;
              flag = 0;
              break;
            }
          }

          //找到又一个分隔符，将两个分隔符之间的字符串取出；
          flag = 0;
          string_size j = i;
          while(j != s.size() && flag == 0){
            for(string_size x = 0; x < seperator.size(); ++x)
            if(s[j] == seperator[x]){
              flag = 1;
              break;
            }
            if(flag == 0)
            ++j;
          }
          if(i != j){
            result.push_back(s.substr(i, j-i));
            i = j;
          }
        }
        return result;
    }

    static int toint(string str)
    {
        return atoi(str.c_str());
    }

    static float tofloat(string str)
    {
        return atof(str.c_str());
    }

    static void t()
    {
        printf("\t");
    }

    static void getmatrix(matrixNode &A)
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

    static void getvector(vectorNode &B)
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

    static vectorNode toVectorNode(vector<string>com)
    {
        vectorNode v(com.size()-1);
        for(unsigned int i=1;i<com.size();i++)
            v.v[i-1]=help::tofloat(com[i]);
        return v;
    }

};
