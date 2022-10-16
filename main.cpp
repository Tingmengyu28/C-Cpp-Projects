#include <iostream>
#include <stack>
#include "functions.h"

using namespace std;

int main()
{
    string str;
    getline(cin, str);
    if (typeOfExpression(str) == 0)
        cout << Arithmetic_bigNumber(str) << endl;
    else if (typeOfExpression(str) == 1)
    {
        string out = varDefinedMethod(str);
        cout << Arithmetic_bigNumber(out) << endl;
    }
    else
    {
        cout << specialFunctions(str) << endl;
    }
    system("PAUSE");
    return 0;
}