#include <iostream>
#include <stack>
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

string getNumInteger(string str)
{
    int dot = -1;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '.')
        {
            dot = i;
            break;
        }
    }
    if (dot == -1)
        return str;
    else
    {
        return str.substr(0, dot);
    }
}

string getNumDigital(string str)
{
    int dot = -1;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '.')
        {
            dot = i;
            break;
        }
    }
    if (dot == -1)
        return "00000000";
    else
    {
        string out;
        if (str.length() - dot < 8)
        {
            out = str.substr(dot + 1);
            for (int i = 0; i <= (8 + dot - str.length()); i++)
                out += '0';
        }
        else
            out = str.substr(dot + 1, 8);
        return out;
    }
}

string simplifyDecimal(string str)
{
    string out = getNumInteger(str);
    string decimal = getNumDigital(str);
    return out + decimal;
}

int largerOne(string str1, string str2)
{
    str1 = simplifyDecimal(str1);
    str2 = simplifyDecimal(str2);
    if (str1.length() < str2.length())
        return 2;
    else if (str1.length() > str2.length())
        return 1;
    else
    {
        for (int i = 0; i < str1.length(); i++)
        {
            if (str1[i] > str2[i])
            {
                return 1;
            }
            else if (str2[i] > str1[i])
            {
                return 2;
            }
        }
        return 0;
    }
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

string getCountAdd(string str1, string str2)
{
    str1 = simplifyDecimal(str1);
    str2 = simplifyDecimal(str2);
    string out = "";
    bool bit = 0;
    int index_str1 = str1.length() - 1;
    int index_str2 = str2.length() - 1;
    while (index_str1 != -1 && index_str2 != -1)
    {
        int t1 = str1[index_str1] - '0';
        int t2 = str2[index_str2] - '0';
        if (!bit)
        {
            if (t1 + t2 >= 10)
            {
                int d = t1 + t2 - 10;
                out.insert(0, 1, d + 48);
                bit = 1;
            }
            else
                out.insert(0, 1, t1 + t2 + 48);
        }
        else
        {
            if (t1 + t2 + 1 >= 10)
            {
                int d = t1 + t2 + 1 - 10;
                out.insert(0, 1, d + 48);
                bit = 1;
            }
            else
            {
                out.insert(0, 1, t1 + t2 + 1 + 48);
                bit = 0;
            }
        }
        index_str1--;
        index_str2--;
    }
    while (index_str1 == -1 && index_str2 != -1)
    {
        int t2 = str2[index_str2] - 48;
        if (!bit)
            out.insert(0, 1, str2[index_str2]);
        else
        {
            if (t2 + 1 >= 10)
            {
                int d = (t2 + 1) - 10;
                out.insert(0, 1, d + 48);
                bit = 1;
            }
            else
            {
                out.insert(0, 1, t2 + 1 + 48);
                bit = 0;
            }
        }
        index_str2--;
    }
    while (index_str1 != -1 && index_str2 == -1)
    {
        int t1 = str1[index_str1] - 48;
        if (!bit)
        {
            out.insert(0, 1, str1[index_str1]);
        }
        else
        {
            if (t1 + 1 >= 10)
            {
                int d = (t1 + 1) - 10;
                out.insert(0, 1, d + 48);
                bit = 1;
            }
            else
            {
                out.insert(0, 1, t1 + 1 + 48);
                bit = 0;
            }
        }
        index_str1--;
    }
    if (bit)
    {
        out.insert(0, 1, 1 + 48);
    }
    bit = -1;
    out.insert(out.length() - 8, 1, '.');
    while (out[out.length() - 1] == '0')
        out.pop_back();
    if (out[out.length() - 1] == '.')
        out.pop_back();
    return out;
}

string getCountMinusPositive(string str1, string str2)
{
    bool borrow = 0;
    string out = "";
    int index_str1 = str1.length() - 1;
    int index_str2 = str2.length() - 1;
    while (index_str1 != -1 && index_str2 != -1)
    {
        int t1 = str1[index_str1] - '0';
        int t2 = str2[index_str2] - '0';
        if (!borrow)
        {
            if (t1 - t2 < 0)
            {
                int d = t1 + 10 - t2;
                out.insert(0, 1, d + 48);
                borrow = 1;
            }
            else
            {
                out.insert(0, 1, t1 - t2 + 48);
                borrow = 0;
            }
        }
        else
        {
            if (t1 - t2 - 1 < 0)
            {
                int d = t1 - t2 + 9;
                out.insert(0, 1, d + 48);
                borrow = 1;
            }
            else
            {
                out.insert(0, 1, t1 - t2 - 1 + 48);
                borrow = 0;
            }
        }
        index_str1--;
        index_str2--;
    }
    while (index_str1 == -1 && index_str2 != -1)
    {
        int t2 = str2[index_str2] - 48;
        if (!borrow)
            out.insert(0, 1, str2[index_str2]);
        else
        {
            if (t2 - 1 < 0)
            {
                int d = t2 + 9;
                out.insert(0, 1, d + 48);
                borrow = 1;
            }
            else
            {
                out.insert(0, 1, t2 - 1 + 48);
                borrow = 0;
            }
        }
        index_str2--;
    }
    while (index_str1 != -1 && index_str2 == -1)
    {
        int t1 = str1[index_str1] - 48;
        if (!borrow)
        {
            out.insert(0, 1, str1[index_str1]);
        }
        else
        {
            if (t1 - 1 < 0)
            {
                int d = t1 + 9;
                out.insert(0, 1, d + 48);
                borrow = 1;
            }
            else
            {
                out.insert(0, 1, t1 - 1 + 48);
                borrow = 0;
            }
        }
        index_str1--;
    }
    borrow = 0;
    return out;
}

string getCountMinus(string str1, string str2)
{
    str1 = simplifyDecimal(str1);
    str2 = simplifyDecimal(str2);
    string out, new_out;
    if (str1.length() < str2.length())
    {
        out = "-";
        string res = getCountMinusPositive(str2, str1);
        out += res;
    }
    else if (str1.length() > str2.length())
    {
        out = getCountMinusPositive(str1, str2);
    }
    else
    {
        int larger_one = 0;
        for (int i = 0; i < str1.length(); i++)
        {
            if (str1[i] > str2[i])
            {
                larger_one = 1;
                break;
            }
            else if (str2[i] > str1[i])
            {
                larger_one = 2;
                break;
            }
        }
        if (larger_one == 1)
            out = getCountMinusPositive(str1, str2);
        else if (larger_one == 2)
        {
            out = "-";
            out += getCountMinusPositive(str2, str1);
        }
        else
            return "0.00000000";
    }
    int from = 0;
    for (; from < out.length(); from++)
        if (out[from] != '0')
            break;
    new_out = out.substr(from);
    new_out.insert(new_out.length() - 8, 1, '.');
    while (new_out[new_out.length() - 1] == '0')
        new_out.pop_back();
    if (new_out[new_out.length() - 1] == '.')
        new_out.pop_back();
    return new_out;
}

string multilplication(string str, char c)
{
    int times = c - '0';
    int bit = -1;
    string out;
    for (int i = 0; i < str.length(); i++)
    {
        int t = str[str.length() - i - 1] - '0';
        if (bit == -1)
        {
            if (t * times >= 10)
            {
                int d = (t * times) % 10;
                out.insert(0, 1, d + 48);
                bit = (t * times) / 10;
            }
            else
            {
                out.insert(0, 1, t * times + 48);
                bit = -1;
            }
        }
        else
        {
            if (t * times + bit >= 10)
            {
                int d = (t * times + bit) % 10;
                out.insert(0, 1, d + 48);
                bit = (t * times + bit) / 10;
            }
            else
            {
                out.insert(0, 1, t * times + bit + 48);
                bit = -1;
            }
        }
    }
    if (bit != -1)
            out.insert(0, 1, bit + 48);
    return out;
}

string getCountMultiple(string str1, string str2)
{
    str1 = simplifyDecimal(str1);
    str2 = simplifyDecimal(str2);
    string out = "";
    int larger_one = largerOne(str1, str2);
    string largeStr, smallStr;
    if (larger_one == 1 || larger_one == 0)
    {
        largeStr = str1;
        smallStr = str2;
    }
    else
    {
        largeStr = str2;
        smallStr = str1;
    }
    for (int i = 0; i < smallStr.length(); i++)
    {
        char ch = smallStr[smallStr.length() - i - 1];
        string str = multilplication(largeStr, ch);
        for (int j = 0; j < i; j++)
            str += '0';
        if (out == "")
            out = str;
        else
            out = getCountAdd(out, str);
    }
    out.insert(out.length() - 16, 1, '.');
    while (out[out.length() - 1] == '0')
        out.pop_back();
    if (out[out.length() - 1] == '.')
        out.pop_back();
    return out;
}

string getCountDivide(string str1, string str2)
{
    str1 = simplifyDecimal(str1);
    str2 = simplifyDecimal(str2);
    string out, new_out = "";
    if (largerOne(str1, str2) == 0)
        return "1.00000000";
    string dividendNum = str1.substr(0, str2.length() - 1);
    string s;
    for (int i = str2.length() - 1; i < str1.length(); i++)
    {
        char c = str1[i];
        if (dividendNum == "0")
            dividendNum = c;
        else
            dividendNum += c;
        int num = 0;
        while (largerOne(dividendNum, str2) == 1 || largerOne(dividendNum, str2) == 0)
        {
            dividendNum = getCountMinus(dividendNum, str2);
            num += 1;
        }
        s = "";
        for (int i = 0; i < dividendNum.length(); i++)
            if (dividendNum[i] != '.')
                s += dividendNum[i];
            else
                break;
        dividendNum = s;
        out += (num + 48);
    }
    out += ".";
    for (int i = 0; i < 8; i++)
    {
        if (dividendNum != "0")
            dividendNum += '0';
        int num = 0;
        while (largerOne(dividendNum, str2) == 1 || largerOne(dividendNum, str2) == 0)
        {
            dividendNum = getCountMinus(dividendNum, str2);
            num += 1;
        }
        s = "";
        for (int i = 0; i < dividendNum.length(); i++)
            if (dividendNum[i] != '.')
                s += dividendNum[i];
            else
                break;
        dividendNum = s;
        out += (num + 48);
    }
    int from = 0;
    for (; from < out.length(); from++)
        if (out[from] != '0')
            break;
    new_out = out.substr(from);
    while (new_out[new_out.length() - 1] == '0')
        new_out.pop_back();
    if (new_out[new_out.length() - 1] == '.')
        new_out.pop_back();
    if (new_out[0] == '.')
        new_out.insert(0, 1, '0');
    return new_out;
}