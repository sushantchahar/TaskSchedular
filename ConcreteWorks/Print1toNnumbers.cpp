#include <iostream>
#include "Print1toNnumbers.h"
using namespace std;

void Print1toNnumbers::Execute()
{
    cout << "Print number from 1 to n" << "\n";
    int n = 12;
    for (int i = 1; i <= n; ++i)
    {
        cout << i << " ";
    }

    cout << "\n";
}
