#include <iostream>
#include <string>

using namespace std;

class Number
{
public:
    Number(string str)
    {
        input = str;
        znak = '+';
        zn_por = '+';
        if (str[0] == '+' || str[0] == '-')
            znak = str[0];
        string mant = "";
        string poryd = "";
        int tochka = 0;
        int flag = 0;
        for (int i = 0; i <= str.length(); i++)
        {
            int j = 0;
            if (flag == 0)
            {
                if (str[i] >= '0' && str[i] <= '9')
                    mant += str[i];
                else if (str[i] == '.')
                    flag = 1;
                else if (str[i] == 'e' || str[i] == 'E')
                    flag = 2;
            }
            else if (flag == 1)
            {
                if (str[i] >= '0' && str[i] <= '9')
                {
                    mant += str[i];
                    tochka++;
                }
                else
                    input_error = true;
            }
            else if (flag == 2)
            {
                if (str[i] == '+' || str[i] == '-')
                    zn_por = str[i];
                else if (str[i] >= '0' && str[i] <= '9')
                    poryd += str[i];
                flag = 3;
            }
            else if (flag == 3)
            {
                if (str[i] >= '0' && str[i] <= '9')
                    poryd += str[i];
            }
        }
        if (flag == 1)
        {
            zn_por = '-';
            while (tochka > 0)
            {
                poryd += 48+(tochka % 10);
                tochka /= 10;
            }
            for (int i = 0; i <= poryd.length() / 2; i++)
            {
                swap(poryd[i], poryd[poryd.length() - i - 1]);
            }
        }
        int j = 29;
        for (int i = mant.length(); i >= 0; i--)
        {
            mantisa[j] = mant[i];
            j--;
        }
        j = 4;
        for (int i = 0; i <= poryd.length(); i++)
        {
            porydok[j] = poryd[i];
            j--;
        }
        cout << znak << mant << zn_por << poryd << endl;
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
