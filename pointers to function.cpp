#include<iostream>
int add(int x, int y)
{
    return x+y;
}

int sub(int x, int y)
{
    return x-y;
}

int main()
{
    int (*call)(int, int);
    
    int choice;
    std::cin >> choice;
    if (choice == 1)
        call = add;
    if (choice == 2)
        call = sub;
    std::cout << call(5,2);
    return 0;
}
