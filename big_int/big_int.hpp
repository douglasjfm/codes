#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <string>

class BI {
    private:
    std::vector<unsigned char> num;

    void separa(int n, int *un, int *dz);

    public:
    BI(){};
    BI(int i);
    BI(const BI &bi);
    BI(BI &&bi);
    ~BI();
    
    BI& operator= (const BI&  bi);
    BI& operator= (BI&& bi);
    BI  operator+ (const BI&  bi);
    BI  operator* (const BI&  bi);
    BI  operator+ (int i);
    BI  operator* (int i);
    BI& operator++ ();

    std::string toStr();
};