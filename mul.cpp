#include <iostream>
#include <cmath>
using namespace std;

bool isNumerical(string str)
{
    int e = -1;
    for (int i = 0; i < str.length(); i++)
        if (str[i] == 'e' && e == -1 && i != str.length() - 1)
            e = i;
        else if ((str[i] == 'e' && e != -1) || (str[i] == 'e' && i == str.length() - 1))
            return 0;
        else if ((str[i] - 48 < 0 || str[i] - 48 > 9) && str[i] != '.' && str[i] != '-')
            return 0;
    if (e != -1)
    {
        string a = str.substr(0, e);
        string b = str.substr(e + 1);
        for (int i = 0; i < b.length(); i++)
            if (b[i] == '-')
            {
                if (i != 0)
                    return 0;
            }
            else if (b[i] == '.')
                return 0;
        for (int i = 0; i < a.length(); i++)
            if (a[i] == '-')
            {
                if (i != 0)
                    return 0;
            }
            else if (a[i] == '.')
                if (i == a.length() - 1 || i == 0)
                    return 0;
    }
    else
    {
        int dot = -1;
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == '.' && dot == -1)
                dot = i;
            else if (str[i] == '.' && dot != -1)
                return 0;
            else if (str[i] == '-')
                if (i != 0)
                    return 0;
        }
    }
    return 1;
}

float *getNumber(string str)
{
    float *s = new float[2];
    int e = -1;
    for (int i = 0; i < str.length(); i++)
        if (str[i] == 'e')
            e = i;
    if (e != -1)
    {
        string a = str.substr(0, e);
        string b = str.substr(e + 1);
        s[0] = stof(a);
        s[1] = stof(b);
    }
    else
    {
        bool isNegative = 0;
        int dot = -1;
        float c = 1;
        for (int i = 0; i < str.length(); i++)
            if (str[i] == '.')
                dot = i;
            else if (str[i] == '-')
            {
                isNegative = 1;
                str = str.substr(1);
            }
            else
            {
                s[0] += (str[i] - 48) * c;
                c = c / 10;
            }
        if (isNegative)
            s[0] = s[0] * -1;
        if (dot == -1)
            s[1] = str.length() - 1;
        else
            s[1] = dot - 1;
    }
    return s;
}

string standardNum(float a, float b)
{
    string s1 = to_string(a);
    string s2 = to_string(b);
    float a_ = a;
    while (a_ >= 10)
    {
        a_ = a_ / 10;
        b += 1;
    }
    if (b <= 8 && b >= 0)
    {
        a = a * pow(10, b);
        return to_string(a);
    }
    else
    {
        return to_string(a_) + "e" + to_string(b);
    }
}

// int main(int argc, char *argv[])
// {
//     string a_in = argv[1];
//     string b_in = argv[2];
//     if (!isNumerical(a_in) || !isNumerical(b_in))
//         cout << "The input cannot be interpret as numbers!" << endl;
//     else
//     {
//         float *a = getNumber(a_in);
//         float *b = getNumber(b_in);
//         cout.precision(6);
//         // cout << a_in << " * " << b_in << " = " << a[0] * b[0] << "e" << a[1] + b[1] << endl;
//         cout << a_in << " * " << b_in << " = " << standardNum(*(a + 0) * b[0], *(a + 1) + b[1]) << endl;
//     }
//     return 0;
// }

int main()
{
    string str;
    getline(cin, str);
    cout << str << endl;
}