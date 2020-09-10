#include <iostream>
#include <string>

#define bolshe 1
#define ravno 0
#define menshe -1

using namespace std;

struct Number
{
    bool input_error = false;
    char znak;
    char mantisa[30];
    string mant;
    char zn_por;
    string poryd;
    int mantisa_len;
    int por;
};

void make_number(Number *num, string str)
{
    num->znak = '+';
    num->zn_por = '+';
    int tmp_i = 0;
    if (str[0] == '+' || str[0] == '-')
    {
        num->znak = str[0];
        tmp_i++;
    }
    for (int i = 0; i < 30; i++)
        num->mantisa[i] = '0';
    num->mant = "";
    num->poryd = "";
    int do_tochki = 0;
    int posle_tochki = 0;
    int flag = 0;
    for (int i = 0 + tmp_i; i < str.length(); i++)
    {
        int j = 0;

        if (flag == 0)
        {
            if (str[i] >= '1' && str[i] <= '9')
                flag = 1;
            else if (str[i] == '.')
                flag = 2;
            else if (str[i] != '0')
            {
                num->input_error = true;
                break;
            }
        }

        switch (flag)
        {
        case 1:
            if (str[i] >= '0' && str[i] <= '9')
            {
                num->mant += str[i];
                do_tochki++;
            }
            else if (str[i] == '.')
                flag = 3;
            else if (str[i] == 'e' || str[i] == 'E')
                flag = 4;
            else
                num->input_error = true;
            break;
        case 2:
            if (str[i] == '0')
                posle_tochki++;
            else if (str[i] >= '1' && str[i] <= '9')
            {
                num->mant += str[i];
                flag = 3;
            }
            else if (str[i] != '.')
                num->input_error = true;
            break;
        case 3:
            if (str[i] >= '0' && str[i] <= '9')
            {
                num->mant += str[i];
            }
            else if (str[i] == 'e' || str[i] == 'E')
            {
                flag = 4;
            }
            else
                num->input_error = true;
            break;
        case 4:
            if (str[i] == '+' || str[i] == '-')
                num->zn_por = str[i];
            else if (str[i] >= '0' && str[i] <= '9')
                num->poryd += str[i];
            else
                num->input_error = true;
            flag = 5;
            break;
        case 5:
            if (str[i] >= '0' && str[i] <= '9')
                num->poryd += str[i];
            else
                num->input_error = true;
            break;
        }
        if (do_tochki > 30)
            num->input_error = true;
    }

    num->mantisa_len = num->mant.length();
    int j = 29;
    for (int i = num->mantisa_len - 1; i >= 0; i--)
    {
        num->mantisa[j] = num->mant[i];
        j--;
    }
    if (num->mant == "")
        num->mant = "0";

    if (flag == 1 || flag == 3)
    {
        if (do_tochki - posle_tochki < 0) //|| flag == 1)
            num->zn_por = '-';
        else
            num->zn_por = '+';

        int tmp_por = abs(do_tochki - posle_tochki);
        num->por = do_tochki - posle_tochki;
        while (tmp_por > 0)
        {
            num->poryd += 48+(tmp_por % 10);
            tmp_por /= 10;
        }
        if (num->poryd.length() == 2)
            swap(num->poryd[0], num->poryd[1]);
        /*for (int i = 0; i < poryd.length() / 2; i++)
        {
            swap(poryd[i], poryd[poryd.length() - i - 1]);
        }*/
    }
    if (flag == 5)
    {
        int tmp_por = 0;
        j = 1;
        for (int i = num->poryd.length() - 1; i >= 0; i--)
        {
            tmp_por += (num->poryd[i] - 48) * j;
            j *= 10;
        }
        if (num->zn_por == '+')
            tmp_por += do_tochki;
        else
            tmp_por = do_tochki - tmp_por;
        num->por = tmp_por;
        //cout << tmp_por << endl;
        num->poryd = "";
        if (tmp_por < 0)
            num->zn_por = '-';
        else
            num->zn_por = '+';
        tmp_por = abs(tmp_por);

        while (tmp_por > 0)
        {
            num->poryd += 48+(tmp_por % 10);
            tmp_por /= 10;
        }
        for (int i = 0; i < num->poryd.length() / 2; i++)
        {
            swap(num->poryd[i], num->poryd[num->poryd.length() - i - 1]);
        }
    }

    if  (num->poryd.length() > 5)
        num->input_error = true;

    if (num->poryd == "")
        num->poryd = "0";

    /*j = 4;
    for (int i = 0; i < poryd.length(); i++)
    {
        porydok[j] = poryd[i];
        j--;
    }*/
    //cout << por << endl;

    //cout << mantisa_len << endl;
    /*for (int i = 0; i < 30; i++)
        cout << mantisa[i];
    cout << endl;*/
    //cout << znak << "0." << mant << "E" << zn_por << poryd << '.' << endl;
    //print();
}

void print(Number number)
{
    cout << number.znak << "0." << number.mant << "E" << number.zn_por << number.poryd << '.' << endl;
}

void summa (int rez[30], int n1[30], int n2[30])
{
    int tmp = 0;

    for (int i = 29; i >= 0; i--)
        rez[i] = 0;

    for (int i = 29; i >= 0; i--)
    {
        rez[i] = n1[i] + n2[i] + tmp;
        tmp = 0;

        if (rez[i] >= 10)
        {
            rez[i] -=10;
            tmp++;
        }
    }

    return;
}

//Функция разночти двух чисел по разрядам
void raznost (int rez[30], int n1[30], int n2[30])
{
    int tmp = 0;

    for (int i = 29; i >= 0; i--)
        rez[i] = 0;

    for (int i = 29; i >= 0; i--)
    {
        rez[i] = n1[i] - n2[i] - tmp;
        tmp = 0;

        if (rez[i] < 0)
        {
            rez[i] +=10;
            tmp++;
        }
    }

    return;
}

//Функция сравнения двух чисел хранящихся в массивах по разрядам
int sravnenie (int n1[30], int n2[30])
{
    int rez = 0;
    for (int i = 0; i < 30; i++)
    {
        if (n1[i] < n2[i])
        {
            rez = -1;
            break;
        }
        else if (n1[i] > n2[i])
        {
            rez = 1;
            break;
        }
    }
    return rez;
}

//Функция получения определённой части числа хранящегося в массиве по разрядам
void get (int rez[30], int input[30], int n)
{
    int j = 0;
    while (input[j] == 0)
    {
        j++;
    }
    for (int i = 0; i < 30; i++)
    {
        if (i < 30 - n || j >= 30)
            rez[i] = 0;
        else
        {
            rez[i] = input[j];
            j++;
        }
    }
}

//Функция добавления в конец числа новой цифры
void plus_razryad (int rez[30], int n)
{
    for (int i = 0; i < 29; i++)
    {
        rez[i] = rez[i + 1];
    }
    rez[29] = n;
}

//Функция присваивания для чисел хранящихся в массивах по разрядам
void prirovnyat (int rez[30], int input[30])
{
    for (int i = 0; i < 30; i++)
    {
        rez[i] = input[i];
    }
}


Number delenie (Number n1,  Number n2)
{
    string rez = "";

    if ((n1.znak == '-') != (n2.znak == '-'))
        rez += "-";
    else
        rez += "+";

    bool is_zero1 = true;
    int delimoe_mantisa[30];
    for (int i = 0; i < 30; i++)
    {
        delimoe_mantisa[i] = n1.mantisa[i] - 48;
        if (n1.mantisa[i] != '0')
            is_zero1 = false;
    }

    bool is_zero2 = true;
    int delitel_mantisa[30];
    for (int i = 0; i < 30; i++)
    {
        delitel_mantisa[i] = n2.mantisa[i] - 48;
        if (n2.mantisa[i] != '0')
            is_zero2 = false;
    }
    if (is_zero2)
    {
        rez = "error";
        Number chastnoe;
        make_number(&chastnoe, rez);
        return chastnoe;
    }
    else if (is_zero1)
    {
        rez += "0";
        Number chastnoe;
        make_number(&chastnoe, rez);
        return chastnoe;
    }

    int j = 0;
    if (sravnenie(delimoe_mantisa, delitel_mantisa) == ravno)
    {
        rez += "100000000000000000000000000000";
        j = 30;
    }

    int tmp1_mantisa[30];
    get(tmp1_mantisa, delimoe_mantisa, n2.mantisa_len);
    int tmp2_mantisa[30];
    prirovnyat(tmp2_mantisa, delitel_mantisa);
    int tmp3_mantisa[30];

    int raznica_por = n1.mantisa_len - n2.mantisa_len;

    if (sravnenie(tmp1_mantisa, tmp2_mantisa) == menshe)
    {
        //cout << delimoe_mantisa[30 - n1.mantisa_len + n2.mantisa_len] << endl;
        if (tmp1_mantisa[0] != 0)
        {
            Number chastnoe;
            make_number(&chastnoe, rez);
            return chastnoe;
        }
        if (30 - n1.mantisa_len + n2.mantisa_len < 30)
        {
            plus_razryad(tmp1_mantisa, delimoe_mantisa[30 - n1.mantisa_len + n2.mantisa_len]);
        }
        else
        {
            plus_razryad(tmp1_mantisa, 0);
        }

        raznica_por--;
    }


    int k = 0;
    int stepen = 0;
    while (j < 30)
    {
        prirovnyat(tmp2_mantisa, delitel_mantisa);
        while (sravnenie(tmp1_mantisa, tmp2_mantisa) != menshe)
        {
            summa(tmp3_mantisa, tmp2_mantisa, delitel_mantisa);
            prirovnyat(tmp2_mantisa, tmp3_mantisa);
            k++;
            /*cout << j << ":" << endl;
            for (int i = 0; i < 30; i++)
                {
                    cout << tmp1_mantisa[i] << " ";
                }
                cout << endl;
            for (int i = 0; i < 30; i++)
                    {
                        cout << tmp2_mantisa[i] << " ";
                    }
                        cout << endl;*/
        }

        //k--;
        rez += 48 + k;
        //cout << rez << endl;
        k = 0;

        raznost(tmp3_mantisa, tmp2_mantisa, delitel_mantisa);
        prirovnyat(tmp2_mantisa, tmp3_mantisa);

        raznost(tmp3_mantisa, tmp1_mantisa, tmp2_mantisa);
        prirovnyat(tmp1_mantisa, tmp3_mantisa);

        j++;

        if (29 - raznica_por + j < 30)
        {
            stepen++;
            plus_razryad(tmp1_mantisa, delimoe_mantisa[29 - raznica_por + j]);
        }
        else
        {
            plus_razryad(tmp1_mantisa, 0);
        }

        if (j == 30)
        {
            j--;
            break;
        }
    }
    if (j == 29)
    {
        prirovnyat(tmp2_mantisa, delitel_mantisa);
        while (sravnenie(tmp1_mantisa, tmp2_mantisa) != menshe)
        {
            summa(tmp3_mantisa, tmp2_mantisa, delitel_mantisa);
            prirovnyat(tmp2_mantisa, tmp3_mantisa);
            k++;
        }
        if (k >= 5)
        {
            for (int i = rez.length(); i > 0; i--)
            {
                if (rez[i] >= '0' && rez[i] <= '9')
                {
                    rez[i] += 1;
                    if (rez[i - 1] >= '0' && rez[i - 1] <= '9' && rez[i] > '9')
                    {
                        rez[i] -= 10;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
    if (j > 29)
        j = 29;
    if (rez.find(".") == -1)
    {
        rez += "E";
        string poryd = "";
        int por = n1.por - n2.por - j;
        if (raznica_por != n1.mantisa_len - n2.mantisa_len)
            por--;
        //cout << por << endl;

        if (por < 0)
            rez += '-';
        else
            rez += '+';
        int tmp_por = abs(por);

        while (tmp_por > 0)
        {
            poryd += 48+(tmp_por % 10);
            tmp_por /= 10;
        }
        for (int i = 0; i < poryd.length() / 2; i++)
        {
            swap(poryd[i], poryd[poryd.length() - i - 1]);
        }

        rez += poryd;
    }

    //cout << rez << endl;
    Number chastnoe;
    make_number(&chastnoe, rez);
    return chastnoe;
}

int main()
{
    cout << "Enter first number: ";
    string input;
    cin >> input;
    Number n1;
    make_number(&n1, input);
    if (n1.input_error)
        cout << "This number is not correct" << endl;
    else
        print(n1);

    cout << "Enter first number: ";
    cin >> input;
    Number n2;
    make_number(&n2, input);
    if (n2.input_error)
        cout << "This number is not correct" << endl;
    else
        print(n2);


    Number rez = delenie(n1, n2);
    if (!rez.input_error)
    {
        cout << "Result: ";
        print(rez);
    }
    else
        cout << "Result is not valid" << endl;

    return 0;
}
