#include <iostream>
#include <stack>
#include <cmath>
#include "functions.h"

using namespace std;

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
    bool toNegative = 0;
    bool isNumber = 0;
    for (int i = 0; i < str.length(); i++)
    {
        char c = str[i];
        if (c == ',')
        {
            if (isNumber)
            {
                if (!toNegative)
                    stk.push(num);
                else
                {
                    stk.push(-num);
                    toNegative = 0;
                }
                num = 0.0f;
                isNumber = 0;
            }
        }
        else if (c >= '0' && c <= '9')
        {
            isNumber = 1;
            num = 10 * num + c - 48;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
            if (c == '-' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
            {
                toNegative = 1;
                continue;
            }
            else
                stk = getValue(stk, c);
    }
    float result = stk.top();
    return result;
}

stack<string> getValue_bigNumber(stack<string> stk, char ch)
{
    string num1 = stk.top();
    stk.pop();
    string num2 = stk.top();
    stk.pop();
    if (ch == '+')
    {
        string res;
        if (num1[0] != '-' && num2[0] != '-')
        {
            res = getCountAdd(num2, num1);
            stk.push(res);
        }
        else if (num1[0] == '-' && num2[0] != '-')
        {
            num1 = num1.substr(1);
            res = getCountMinus(num2, num1);
            stk.push(res);
        }
        else if (num1[0] != '-' && num2[0] == '-')
        {
            num2 = num2.substr(1);
            res = getCountMinus(num1, num2);
            stk.push(res);
        }
        else
        {
            num1 = num1.substr(1);
            num2 = num2.substr(1);
            res = getCountAdd(num2, num1);
            stk.push("-" + res);
        }
    }
    else if (ch == '-')
    {
        string res;
        if (num1[0] != '-' && num2[0] != '-')
        {
            res = getCountMinus(num2, num1);
            stk.push(res);
        }
        else if (num1[0] == '-' && num2[0] != '-')
        {
            num1 = num1.substr(1);
            res = getCountAdd(num2, num1);
            stk.push(res);
        }
        else if (num1[0] != '-' && num2[0] == '-')
        {
            num2 = num2.substr(1);
            res = getCountAdd(num1, num2);
            stk.push("-" + res);
        }
        else
        {
            num1 = num1.substr(1);
            num2 = num2.substr(1);
            res = getCountAdd(num1, num2);
            stk.push(res);
        }
    }
    else if (ch == '*')
    {
        string res;
        if (num1[0] != '-' && num2[0] != '-')
        {
            res = getCountMultiple(num2, num1);
            stk.push(res);
        }
        else if (num1[0] == '-' && num2[0] != '-')
        {
            num1 = num1.substr(1);
            res = getCountMultiple(num2, num1);
            stk.push("-" + res);
        }
        else if (num1[0] != '-' && num2[0] == '-')
        {
            num2 = num2.substr(1);
            res = getCountMultiple(num2, num1);
            stk.push("-" + res);
        }
        else
        {
            num1 = num1.substr(1);
            num2 = num2.substr(1);
            res = getCountMultiple(num2, num1);
            stk.push(res);
        }
    }
    else if (ch == '/')
    {
        string res;
        if (num1[0] != '-' && num2[0] != '-')
        {
            res = getCountDivide(num2, num1);
            stk.push(res);
        }
        else if (num1[0] == '-' && num2[0] != '-')
        {
            num1 = num1.substr(1);
            res = getCountDivide(num2, num1);
            stk.push("-" + res);
        }
        else if (num1[0] != '-' && num2[0] == '-')
        {
            num2 = num2.substr(1);
            res = getCountDivide(num2, num1);
            stk.push("-" + res);
        }
        else
        {
            num1 = num1.substr(1);
            num2 = num2.substr(1);
            res = getCountDivide(num2, num1);
            stk.push(res);
        }
    }
    return stk;
}

string calculator_bigNumber(string str)
{
    stack<string> stk;
    string num = "";
    bool toNegative = 0;
    bool isNumber = 0;
    for (int i = 0; i < str.length(); i++)
    {
        char c = str[i];
        if (c == ',')
        {
            if (isNumber)
            {
                if (!toNegative)
                    stk.push(num);
                else
                {
                    string negnum = "-" + num;
                    stk.push(negnum);
                    toNegative = 0;
                }
                num = "";
                isNumber = 0;
            }
        }
        else if ((c >= '0' && c <= '9') || c == '.')
        {
            isNumber = 1;
            num += c;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
            if (c == '-' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
            {
                toNegative = 1;
                continue;
            }
            else
                stk = getValue_bigNumber(stk, c);
    }
    string result = stk.top();
    return result;
}

float Arithmetic(string str)
{
    string s = transformer(str);
    return calculator(s);
}

string Arithmetic_bigNumber(string str)
{
    string s = transformer(str);
    string result = calculator_bigNumber(s);
    return result;
}

string varDefinedMethod(string str)
{
    string dict[26];
    string out = "";
    while (true)
    {
        if (str == "")
            getline(cin, str);
        if (str[1] == '=')
        {
            dict[str[0] - 'a'] = str.substr(2);
            str = "";
        }
        else
            break;
    }
    for (int i = 0; i < str.length(); i++)
        if (str[i] >= 'a' && str[i] <= 'z')
            out += dict[str[i] - 'a'];
        else
            out += str[i];
    return out;
}

string transformer(string str)
{
    stack<char> stk;
    string out = "";
    if (str[0] == '-')
    {
        str = str.substr(1);
        stk.push('-');
        out += "0,";
    }
    for (int i = 0; i < str.length(); i++)
    {
        char c = str[i];
        if ((c >= '0' && c <= '9') || c == '.')
        {
            out += c;
            if (!((str[i + 1] >= '0' && str[i + 1] <= '9') || str[i + 1] == '.'))
                out += ",";
        }
        else if (c == '(')
            stk.push(c);
        else if (c == '*' || c == '/')
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
        else if (c == '+' || (c == '-' && str[i - 1] != '('))
        {
            if (!stk.empty())
            {
                char top_element = stk.top();
                if (top_element == '*' || top_element == '/' || top_element == '+' || top_element == '-')
                {
                    while (!stk.empty())
                    {
                        top_element = stk.top();
                        if (top_element == '*' || top_element == '/' || top_element == '+' || top_element == '-')
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
        else if (c == '-' && str[i - 1] == '(')
            out += c;
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

float specialFunctions(string str)
{
    string funcName = "";
    for (int i = 0; i < str.length(); i++)
    {
        char c = str[i];
        if (c >= 'a' && c <= 'z')
            funcName += c;
        else
            break;
    }
    float num = 0.0f;
    float result;
    for (int i = 0; i < str.length(); i++)
        if (str[i] >= '0' && str[i] <= '9')
            num = 10 * num + str[i] - '0';
    if (funcName == "sqrt")
        result = sqrt(num);
    else if (funcName == "log")
        result = sqrt(num);
    else if (funcName == "abs")
        result = abs(num);
    else if (funcName == "cos")
        result = cos(num);
    else if (funcName == "sin")
        result = sin(num);
    else if (funcName == "exp")
        result = exp(num);
    else if (funcName == "tan")
        result = tan(num);
    return result;
}