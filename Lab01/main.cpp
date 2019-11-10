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
		int do_tochki = 0;
		int posle_tochki = 0;
		int flag = 0;
        for (int i = 0; i <= str.length(); i++)
        {
            int j = 0;

			if (flag == 0)
			{
				if (str[i] >= '1' && str[i] <= '9')
					flag = 1;
				else if (str[i] == '.')
					flag = 2;
				else if(str[i] == 'e' || str[i] == 'E')
					flag = 4;
			}

			switch (flag)
			{
			case 1:
				if (str[i] >= '0' && str[i] <= '9')
				{
					mant += str[i];
					do_tochki++;
				}
				else if (str[i] == '.')
					flag = 3;
				else if (str[i] == 'e' || str[i] == 'E')
					flag = 4;
				break;
			case 2:
				if (str[i] == '0')
					posle_tochki++;
				if (str[i] >= '1' && str[i] <= '9')
				{
					mant += str[i];
					flag = 3;
				}
				break;
			case 3:
				if (str[i] >= '0' && str[i] <= '9')
				{
					mant += str[i];
				}
				else
					input_error = true;
				break;
			case 4:
				if (str[i] == '+' || str[i] == '-')
					zn_por = str[i];
				else if (str[i] >= '0' && str[i] <= '9')
					poryd += str[i];
				flag = 5;
				break;
			case 5:
				if (str[i] >= '0' && str[i] <= '9')
					poryd += str[i];
				break;
			}
        }

		int j = 29;
		for (int i = mant.length() - 1; i >= 0; i--)
		{
			mantisa[j] = mant[i];
			j--;
		}

		if (flag == 3)
        {
			if (do_tochki - posle_tochki < 0)
				zn_por = '-';
			else
				zn_por = '+';

			int tmp_por = abs(do_tochki - posle_tochki);
			while (tmp_por > 0)
			{
				poryd += 48+(tmp_por % 10);
				tmp_por /= 10;
            }
			if (poryd.length() == 2)
				swap(poryd[0], poryd[1]);
			/*for (int i = 0; i < poryd.length() / 2; i++)
			{
                swap(poryd[i], poryd[poryd.length() - i - 1]);
			}*/
		}
		if (flag == 5)
		{
			int tmp_por = 0;
			j = 1;
			for (int i = poryd.length() - 1; i >= 0; i--)
			{
				tmp_por += (poryd[i] - 48) * j;
				j *= 10;
			}
			if (zn_por == '+')
				tmp_por += do_tochki;
			else
				tmp_por = do_tochki - tmp_por;
			//cout << tmp_por << endl;
			poryd = "";
			if (tmp_por < 0)
				zn_por = '-';
			else
				zn_por = '+';
			tmp_por = abs(tmp_por);

			while (tmp_por > 0)
			{
				poryd += 48+(tmp_por % 10);
				tmp_por /= 10;
			}
			for (int i = 0; i < poryd.length() / 2; i++)
			{
				swap(poryd[i], poryd[poryd.length() - i - 1]);
			}
		}

		if (poryd == "")
			poryd = "0";

		j = 4;
        for (int i = 0; i <= poryd.length(); i++)
        {
            porydok[j] = poryd[i];
            j--;
        }
		cout << znak << "0." << mant << "E" << zn_por << poryd << '.' << endl;
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
