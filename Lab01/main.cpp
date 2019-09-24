#include <iostream>
#include <string>

using namespace std;

class Number
{
public:
    Number(string str)
    {
        input = str;
        int flag = 0;
        cout << str.length() << '\n';
        for (int i = 0; i <= str.length(); i++)
        {
            int j = 0;
            int tochka = 0;
            if (flag == 0)
            {
                if (str[i] == '+' || str[i] == '-')
                {
                    znak = str[i];
                    flag++;
                }
            }
            else if (flag == 1)
            {
                if (str[i] >= '0' && str[i] <= '9' || str[i] == '.')
                {
                    if (str[i] == '.')
                        tochka++;
                    if (tochka <= 1)
                        mantisa[j] = str[i];
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
