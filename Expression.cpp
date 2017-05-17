#include "Expression.h"
#include <string>
#include <stack>
#include <vector>
#include <math.h>
#include <stdexcept>
#include <iostream>

using namespace std;

bool IsOperator(char c){
    if(c == '+') return true;
    if(c == '-') return true;
    if(c == '*') return true;
    if(c == '/') return true;
    if(c == '^') return true;
    if(c == '~') return true;
    if(c == '(') return true;
    if(c == ')') return true;
    if(c == '=') return true;
    return false;
}

Expression::Expression(string str){
    init(str);
}

void Expression::init(string str){
    mText=str;
    mDelayOps = stack<Token>();
    mInput = vector<Token>();
    mOutput = vector<Token>();
    mOperands = stack<TokenRecord::Value>();

    read();

    transform();
}

TokenRecord::Value Expression::evaluate(TokenRecord::Value x){
    for(vector<Token>::iterator t = mOutput.begin(); t != mOutput.end(); ++t){
        if(!(t->symbol().compare("x"))){
            t->setValue(x);
            break;
        }
    }

    for(vector<Token>::iterator t = mOutput.begin(); t != mOutput.end(); ++t){
        switch(t->type()){
            case operand:
                mOperands.push(t->value());
                break;
            case unaryOp:{
                int op1 = mOperands.top();
                mOperands.pop();
                mOperands.push(-op1);
                break;
            }
            case binaryOp:{
                int op1 = mOperands.top();
                mOperands.pop();
                int op2 = mOperands.top();
                mOperands.pop();
                switch(t->symbol()[0]){
                    case '+':
                        mOperands.push(op1+op2);
                        break;
                    case '-':
                        mOperands.push(op2-op1);
                        break;
                    case '*':
                        mOperands.push(op1*op2);
                        break;
                    case '/':
                        mOperands.push(op2/op1);
                        break;
                    default:
                        mOperands.push(pow(op2, op1));
                        break;
                }
            }
            default:
                break;
        }
    }
    if(mOperands.size()!=1){
        throw std::runtime_error("Final stack size does not equal 1");
    }
    else {
        TokenRecord::Value result = mOperands.top();
        mOperands.pop();
        return result;
    };
}

void Expression::setParameters(){
    for(vector<Token>::iterator t = mOutput.begin(); t != mOutput.end(); ++t){
        if(t->priority() == -1 && t->symbol().compare("x")){
            TokenRecord::Value v;
            cout << t->symbol() << ": ";
            cin >> v;
            t->setValue(v);
        }
    }
}

void Expression::read(){
    //rtrim
    while(mText[mText.size()-1] == ' ') mText = mText.substr(0, mText.size()-1);

    string c;

    while(!mText.empty()){
        //Parse next token string

        //ltrim
        while(mText[0] == ' ') mText = mText.substr(1, mText.size());

        if(mText.empty()) break;

        c = "";

        if(IsOperator(mText[0])){
            c = mText.substr(0, 1);
            mText=mText.substr(1, mText.size());
        }

        else if(isdigit(mText[0])){
            unsigned int i = 0;
            while(i<mText.size() && isdigit(mText[i])) ++i;
            c = mText.substr(0, i);
            if(i==mText.size()) mText="";
            else mText=mText.substr(i, mText.size());
        }

        else {
            unsigned int i = 0;
            while(i<mText.size()
                  && !isdigit(mText[i])
                  && !IsOperator(mText[i])
                  && mText[i]!= ' ') {
                        ++i;
            }
            c = mText.substr(0, i);
            if(i == mText.size()) mText="";
            else mText=mText.substr(i, mText.size());
        }
        //Generate and save token
        mInput.push_back(Token(c));
    }
}

void Expression::transform(){
    for(vector<Token>::iterator t = mInput.begin(); t != mInput.end(); ++t){
        if (t->type()==operand){
            mOutput.push_back(*t);
        }
        else if(t->type()==rightParen){
            while(!mDelayOps.empty() && mDelayOps.top().type()!=leftParen){
                mOutput.push_back(mDelayOps.top());
                mDelayOps.pop();
            }
            mDelayOps.pop();
        }
        else if(t->type()==leftParen){
            mDelayOps.push(*t);
        }
        else if(t->priority()<3){
            while(mDelayOps.size()!=0){
                if(mDelayOps.top().priority()>=t->priority() && mDelayOps.top().type()!=leftParen){
                mOutput.push_back(mDelayOps.top());
                mDelayOps.pop();
                }
                else break;
            }
            mDelayOps.push(*t);
        }
        else if(t->priority()==3){
            mDelayOps.push(*t);
        }
    }
    while(!mDelayOps.empty()){
        mOutput.push_back(mDelayOps.top());
        mDelayOps.pop();
    }
}

void Expression::print_infix(ostream & o){
    o << "INFIX: ";
    for(vector<Token>::iterator t = mInput.begin(); t != mInput.end(); ++t){
        if(t->priority() == -1 || !(t->type() == operand)) o << t->symbol() << " ";
        else o << t->value() << " ";
    }
    o << endl;
}

void Expression::print_postfix(ostream & o){
    o << "POSTFIX: ";
    for(vector<Token>::iterator t = mOutput.begin(); t != mOutput.end(); ++t){
        if(t->priority() == -1 || !(t->type() == operand)) o << t->symbol() << " ";
        else o << t->value() << " ";
    }
    o << endl;
}
