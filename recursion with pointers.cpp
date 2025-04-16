//recursion with pointers
#include<iostream>
using namespace std;

void rec(int* a)
{
    if (*a == 0) return;
    cout << *a << endl;
    (*a)--;
    rec(a);
}

int main()
{
    int num;
    cin >> num;
    rec(&num);
    return 0;
}
