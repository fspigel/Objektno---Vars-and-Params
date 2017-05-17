#include "ClassLib.h"
#include <sstream>
#include <iostream>

using namespace std;

/// Lexicon

void Lexicon::setStandardTokens(){
    Token("+");
    Token("-");
    Token("*");
    Token("/");
    Token("^");
    Token("~");
    Token("(");
    Token(")");
    Token("=");
}

/// Token

Lexicon Token::mSymbolTable = Lexicon();

vector<int> Token::mParameters = vector<int>();

Token::Token(string str){
    for(vector<TokenRecord>::iterator it = mSymbolTable.tokens.begin(); it!= mSymbolTable.tokens.end(); ++it){\
        if(!str.compare(it->name)) {
            mCode=it-mSymbolTable.tokens.begin();
            return;
        }
    }
    mCode=mSymbolTable.tokens.size();

    TokenRecord tr;

    switch(str[0]){
        case '~':
            tr.priority = 3;
            tr.type = unaryOp;
            break;
        case '(':
            tr.type = leftParen;
            tr.priority = 4;
            break;
        case ')':
            tr.type = rightParen;
            tr.priority = 4;
            break;
        case '=':
            tr.type = endToken;
            break;
        case '^':
            tr.priority=3;
            tr.type = binaryOp;
            break;
        case '*':
            tr.priority = 2;
            tr.type = binaryOp;
            break;
        case '/':
            tr.priority = 2;
            tr.type = binaryOp;
            break;
        case '+':
            tr.priority = 1;
            tr.type = binaryOp;
            break;
        case '-':
            tr.priority = 1;
            tr.type = binaryOp;
            break;
        default:{
            if(isdigit(str[0])){
                istringstream convert(str);
                if (!(convert >> tr.value)) tr.value = 0;
            }
            else{
                tr.priority = -1;
                mParameters.push_back(mSymbolTable.tokens.size());
            }
            tr.type = operand;
            break;
        }
    }
    tr.name = str;

    mSymbolTable.tokens.push_back(tr);
}

