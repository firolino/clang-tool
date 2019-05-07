#include <iostream>
using namespace std;

struct _x
{
    struct _x  *x;
    int        y;
};

int getXXY(struct _x *p)
{
    p->x->y;
    p->x;
    return( p->x->x->y);
}

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
