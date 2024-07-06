#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include "big_int.hpp"

void BI::separa(int n, int *un, int *dz)
{
    char str[3];

    if (n > 99)
    {
        *un = 0;
        *dz = 0;
        return;
    }

    sprintf(str, "%02d", n);

    *un = str[1] - '0';
    *dz = str[0] - '0';
}

BI::BI(int i)
{
    char temp[30];
    int j=0;
    sprintf(temp,"%d",i);
    j = strlen(temp) - 1;
    while (j >= 0)
    {
        num.push_back(temp[j] - '0');
        j--;
    }
}

BI::BI(const BI &bi)
{
    num = bi.num;
}

BI::BI(BI &&bi)
{
    num = bi.num;
    bi.num.clear();
}

BI::~BI()
{
    num.clear();
}

BI& BI::operator= (const BI& bi)
{
    num = bi.num;
    return (*this);
}

BI& BI::operator= (BI&& bi)
{
    num = bi.num;
    bi.num.clear();
    return (*this);
}

BI BI::operator+ (int i)
{
    BI tmp(i);
    BI r;
    r = (*this) + tmp;
    return r;
}

BI BI::operator* (int i)
{
    BI tmp(i);
    BI r;
    r = (*this) * tmp;
    return r;
}

BI BI::operator+ (const BI& bi)
{
    BI r;
    const BI *mn, *ma;
    if (bi.num.size() < num.size())
    {
        mn = &bi;
        ma = this;
    }
    else
    {
        mn = this;
        ma = &bi;
    }
    int l = mn->num.size();
    int i=0, resto = 0;
    while (i < l)
    {
        int sum = mn->num[i] + ma->num[i] + resto;
        if (sum > 9)
        {
            resto = 1;
            sum = sum - 10;
        }
        else
        {
            resto = 0;
        }
        r.num.push_back(sum);
        i++;
    }

    while (i < ma->num.size())
    {
        int sum = ma->num[i] + resto;
        if (sum > 9)
        {
            resto = 1;
            sum = sum - 10;
        }
        else
        {
            resto = 0;
        }
        r.num.push_back(sum);
        i++;
    }

    if (resto)
    {
        r.num.push_back(1);
    }

    return r;
}

BI BI::operator* (const BI &bi)
{
    BI r,temp(0);
    const BI *mn, *ma;
    int l = 0;
    if (bi.num.size() < num.size())
    {
        mn = &bi;
        ma = this;
    }
    else
    {
        mn = this;
        ma = &bi;
    }
    
    for (int x=0; x < mn->num.size(); x++)
    {
        BI sum1;
        int resto = 0;
        for (int xx=0; xx < x; xx++)
        {
            sum1.num.push_back(0);
        }

        if (mn->num[x] == 0) {
            continue;
        }

        if (mn->num[x] == 1) {
            for (unsigned char uc : ma->num) {
                sum1.num.push_back(uc);
            }
            temp = (temp + sum1);
            continue;
        }

        for (int ma_: ma->num)
        {
            int prd = mn->num[x] * ma_ + resto;
            int prd0, prd1;

            separa(prd, &prd0, &prd1);

            sum1.num.push_back(prd0);
            resto = prd1;
        }

        if (resto)
        {
            sum1.num.push_back(resto);
        }

        temp = (temp + sum1);
    }
    r = temp;
    return r;
}

std::string BI::toStr()
{
    char *str = (char*) malloc(num.size()+1);
    int ind = num.size();
    if(!str) return "ERROR";
    str[ind] = '\0';

    for (int i : num)
    {
        char c = i + '0';
        ind--;
        str[ind] = c;
    }
    std::string ret(str);
    free(str);
    return ret;
}

BI& BI::operator++ ()
{
    *this = *this + 1;
    return *this;
}