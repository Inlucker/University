#include <iostream>
#include <string>

using namespace std;

class Number
{
public:
    Number(string str)
    {
        input = str;
        int length = int(str.length());
        znak = '+';
        if (str[0] == '+' || str[0] == '-')
            znak = str[0];
        int flag = 0;
        cout << str.length() << '\n';
        for (int i = 0; i <= length; i++)
        {
            int j = 0;
            int tochka = 0;
            if (flag == 0)
            {
                if (str[1] == '+' || str[1] == '-')
                {
                    znak = str[1];
                    flag++;
                }
            }
            else if (flag == 1)
            {
                if ((str[1] >= '0' && str[1] <= '9') || str[1] == '.')
                {
                    if (str[1] == '.')
                        tochka++;
                    if (tochka <= 1)
                        mantisa[j] = str[1];
                    else
                        input_error = true;
                }
            }
        }
    }
    string input;
    bool input_error;
    char znak;
    char mantisa[30];
    char zn_por;
    char porydok[5];
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
