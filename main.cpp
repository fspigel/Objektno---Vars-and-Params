#include "Expression.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str;
    TokenRecord::Value x;

    cout << "Input initial expression: ";
    cin >> str;
    Expression expr(str);

    expr.print_infix(cout);
    expr.print_postfix(cout);
     cout << "Input parameters (integers only): " << endl;
    expr.setParameters();

    do{
        cout << "Input variable x: ";
        cin >> str;
        if(!str.compare("end")) return 0;
        cout << "Result: " << expr.evaluate(stoi(str)) << endl;
    }while(1);
}
