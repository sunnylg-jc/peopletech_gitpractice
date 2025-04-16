//passing function as argument to another function
#include <iostream>
using namespace std;

int add(int x, int y) { return x + y; }
int sub(int x, int y) { return x - y; }
int mul(int x, int y) { return x * y; }
int divi(int x, int y) { return x / y; }
int mod(int x, int y) { return x % y; }

int op(int x, int y, int (*fun)(int, int)) {
    return fun(x, y);
}

int main() {
    int x, y, choice;
    cout << "Enter two numbers: ";
    cin >> x >> y;

    cout << "Choose operation:\n";
    cout << "0: Add\n1: Subtract\n2: Multiply\n3: Divide\n4: Modulus\n";
    cin >> choice;

    // Function pointer declaration
    int (*selectedFunc)(int, int);

    // Select function based on user input
    if (choice == 0) selectedFunc = add;
    else if (choice == 1) selectedFunc = sub;
    else if (choice == 2) selectedFunc = mul;
    else if (choice == 3) selectedFunc = divi;
    else if (choice == 4) selectedFunc = mod;
    else {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    int result = op(x, y, selectedFunc);
    cout << "Result: " << result << endl;

    return 0;
}
