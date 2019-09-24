#include <iostream>
#include <string>

using namespace std;

class Number
{
public:
    Number(string str)
    {
        input = str;
        cout << str;
    }
    string input;
};

void input()
{
    cout << "Enter first number: ";
    string input;
    cin >> input;
    Number n1(input);
    return;
}

int main()
{
    input();
    return 0;
}
