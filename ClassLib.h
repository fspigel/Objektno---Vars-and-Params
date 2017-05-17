#ifndef MISC_CLASSES_H_INCLUDED
#define MISC_CLASSES_H_INCLUDED

#include<vector>
#include<string>

enum TokenType {
    operand, unaryOp, binaryOp, leftParen, rightParen, endToken
};

struct TokenRecord{
    using Value = int;
    TokenType   type;
    std::string name;
    Value       value;
    int         priority;
};

class Lexicon{

public:
    // Stavi standardne tokene u tabelu. Na taj način su njihove pozicije fiksirane.
    // Tu možemo postaviti i varijablu "x".
    void setStandardTokens();
    // Tabela simbola (tokena)
    std::vector<TokenRecord> tokens;
};

class Token{
public:
    // Formiraj token iz imena. Ako token ne postoji dodaj ga u tabelu
    // simbola, a ako postoji uzmi njegov kod. Ako je token parametar
    // dodaj ga u tabelu parametara.
    Token(std::string name);

    TokenType          type()     const { return mSymbolTable.tokens[mCode].type;     }
    std::string        symbol()   const { return mSymbolTable.tokens[mCode].name;     }
    TokenRecord::Value value()    const { return mSymbolTable.tokens[mCode].value;    }
    int                priority() const { return mSymbolTable.tokens[mCode].priority; }

    void setValue(TokenRecord::Value v) {
        mSymbolTable.tokens[mCode].value = v;
        mSymbolTable.tokens[mCode].priority=0;
    }

    // Inicijaliziraj tabelu simbola standardnim tokenima. Obriši
    // prethodne tokene ako postoje.
    static void initSymbolTable() {
        mSymbolTable.tokens.clear();
        mSymbolTable.setStandardTokens();
        mParameters.clear();
    }
    // Broj parametara u tabeli
    static int noParams() { return mParameters.size(); }
    // Postavi varijablu "x" na vrijednost x.
    static void setVariable(TokenRecord::Value x);
    static void printSymbolTable(std::ostream & out);
private:
    // Indeks tokena u tabeli simbola
    int mCode;
    // Tabela simbola. Svi tokeni referiraju na istu tablelu
    // koja je privatna kako bi se spriječila korupcija tabele.
    static Lexicon mSymbolTable;
    // Lista indeksa parametara u tabeli simbola. Svi tokeni referiraju
    // na istu listu parametara.
    static std::vector<int> mParameters;
};

#endif // MISC_CLASSES_H_INCLUDED
