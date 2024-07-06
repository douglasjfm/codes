#include <big_int.hpp>
#include <time.h>
#include <thread>

void print_output(int x, BI& a, clock_t tm)
{
    tm = clock() - tm;
    std::cout << "FAT "  << x << std::endl;
    std::cout << a.toStr() << std::endl;
    std::cout << "in: " << (float)tm/CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << "output length: " << a.toStr().size() << " digits" << std::endl;
}

void print_fac(int x)
{
    int i = x-1;
    BI a = x;
    clock_t tm = clock();

    if (x < 1)
    {
        return;
    }

    while(i > 0)
    {
        a = a * i;
        i--;
    }

    print_output(x,a,tm);
}

int is_num_only(const char *in) {
    if (!in) return 0;
    for (int i=0; in[i] != '\0'; i++){
        if (in[i] < '0') return 0;
        if (in[i] > '9') return 0;
    }

    return 1;
}

int main(int argc, char **argv)
{
    int fat = 0;
    if (argc > 1)
    {
        if (is_num_only(argv[1])) {
            sscanf(argv[1], "%d", &fat);
        } else {
            std::cout << "Error input '" << argv[1] << "'" << std::endl;
            return 1;
        }
    }
    else
    {
        fat = 10000;
    }

    print_fac(fat);

    return 0;
}