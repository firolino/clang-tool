#include <iostream>
using namespace std;

int bad_global = -1;

void print()
{
    cout << "hallo" << endl;
    int variable = 0;
}

int main()
{
    print ();
    print();
    {
        int a = 0, b = 1;
        b = a;
    }
}
