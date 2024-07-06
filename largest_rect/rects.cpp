#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

/*
 * Complete the 'largestRectangle' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts INTEGER_ARRAY h as parameter.
 */

long largestRectangle(std::vector<int> h)
{
    std::stack<int> pilha;
    long maxArea = 0;
    long area_temp = 0;
    int i=0;

    while(i < h.size())
    {
        if (pilha.empty()) pilha.push(i++);
        else if (h[pilha.top()] <= h[i]) pilha.push(i++);
        else if (h[pilha.top()] > h[i])
        {
            int tp = 0;
            int i_lef = 0;

            tp = pilha.top();
            pilha.pop();

            i_lef = pilha.empty() ? -1 : pilha.top();
            area_temp = h[tp] * (i - (i_lef + 1));

            if(area_temp > maxArea) maxArea = area_temp;
        }
    }

    while(!pilha.empty())
    {
        int tp = 0;
        int i_lef = 0;

        tp = pilha.top();
        pilha.pop();

        i_lef = pilha.empty() ? -1 : pilha.top();
        area_temp = h[tp] * (i - (i_lef + 1));

        if(area_temp > maxArea) maxArea = area_temp;
    }

    return maxArea;
}

int main(){
    int v[] = {999996,999997,999998,999999,1000000};
    std::vector<int> vt;

    vt.assign(v, v+5);
    cout << largestRectangle(vt) << endl;
    return 0;
}