#include <iostream>
#include <map>
#include <cmath>
#include <stack>

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

string transformer(string str)
{
    stack<char> stk;
    string out = "";
    for (int i = 0; i < str.length(); i++)
    {
        char c = str[i];
        if (c >= '0' && c <= '9')
        {
            out += c;
            if (!(str[i + 1] >= '0' && str[i + 1] <= '9'))
                out += ",";
        }
        else if (c == '(')
            stk.push(c);
        else if (c == '*' || c == '/')
            stk.push(c);
        else if (c == '+' || c == '-')
        {
            if (!stk.empty())
            {
                char top_element = stk.top();
                if (top_element == '*' || top_element == '/')
                {
                    while (!stk.empty())
                    {
                        top_element = stk.top();
                        if (top_element == '*' || top_element == '/')
                        {
                            stk.pop();
                            out += top_element;
                            out += ",";
                        }
                        else
                            break;
                    }
                    stk.push(c);
                }
                else
                    stk.push(c);
            }
            else
                stk.push(c);
        }
        else if (c == ')')
            if (stk.empty())
                return "Please input correct expression";
            else
            {
                char now_element = stk.top();
                while (!stk.empty())
                {
                    now_element = stk.top();
                    stk.pop();
                    if (now_element != '(')
                    {
                        out += now_element;
                        out += ",";
                    }
                    else
                        break;
                }
            }
        else
            return "Please input correct expression";
    }
    while (stk.size() > 0)
    {
        char ch = stk.top();
        out += ch;
        out += ",";
        stk.pop();
    }
    out = out.substr(0, out.length() - 1);
    return out;
}

stack<float> getValue(stack<float> stk, char ch)
{
    float num1 = stk.top();
    stk.pop();
    float num2 = stk.top();
    stk.pop();
    if (ch == '+')
        stk.push(num2 + num1);
    else if (ch == '-')
        stk.push(num2 - num1);
    else if (ch == '*')
        stk.push(num2 * num1);
    else if (ch == '/')
        stk.push(num2 / num1);
    return stk;
}

float calculator(string str)
{
    stack<float> stk;
    float num = 0.0f;
    for (int i = 0; i < str.length(); i++)
    {
        char c = str[i];
        if (c == ',')
        {
            if (num != 0)
            {
                stk.push(num);
                num = 0.0f;
            }
        }
        else if (c >= '0' && c <= '9')
            num = 10 * num + c - 48;
        else if (c == '+' || c == '-' || c == '*' || c == '/')
            stk = getValue(stk, c);
    }
    float result = stk.top();
    return stk.top();
}

int typeOfExpression(string str)
{
    bool no_alphabet = 1;
    for (int i = 0; i < str.length(); i++)
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
            no_alphabet = 0;
    if (no_alphabet)
        return 0;
    else if (str[1] == '=')
        return 1;
    else
        return 2;
}

int main()
{
    string str;
    getline(cin, str);
    if (typeOfExpression(str) == 0)
    {
        string out = transformer(str);
        cout << calculator(out) << endl;
    }
    else if (typeOfExpression(str) == 1)
    {
        map<char, float> dict;
        while (str != "")
        {
            getline(cin, str);
            char key = str[0];
            float value = 0.0f;
            for (int j = 2; j < str.length(); j++)
                value = value * 10 + str[j] - 48;
            dict[key] = value;
        }
    }

    // string out = transformer(str);
    // cout << out << endl;
    return 0;
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