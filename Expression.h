#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include "IPExpression.h"

/**  Klasa se incijalizira izrazom u infix formi koji automatski konvertira u
 *   postfix formu i nudi metodu evaluate() te print_postfix().
 */
class Expression{
public:
    // Konstrukcija praznog izraza
    Expression();
    // Konstrukcija izraza iz stringa.
    // text mora sadržavati aritmetički izraz u infix notaciji
    Expression(std::string text);
    // Inicijalizacija iz stringa.
    // text mora sadržavati aritmetički izraz u infix notaciji
    void init(std::string text);

    // Izračunaj vrijednost izraza za danu vrijednost varijable
    TokenRecord::Value evaluate(TokenRecord::Value x);
    // Ispiši postfix verziju izraza
    void print_postfix(std::ostream & );
    // Ispiši infix verziju izraza
    void print_infix(std::ostream & );
    // Inicijaliziraj parametre. Korisnik treba redom inicijalizirati sve parametre.
    void setParameters();
private:
    // Ulazni string sa infix izrazom
    std::string mText;
    // Stog odgođenih operacija
    std::stack<Token> mDelayOps;
    // Lista tokena u infix formi
    std::vector<Token> mInput;
    // Lista tokena u postfix formi (inverzna poljska notacija)
    std::vector<Token> mOutput;
    // Stog za izračunavanje izraza
    std::stack<TokenRecord::Value> mOperands;

    // Pročitaj ulazni string i formiraj listu tokena u infiks notaciji
    void read();
    // Rutina koja čini transformaciju iz infix u prefix formu
    void transform();
};

#endif // EXPRESSION_H_INCLUDED
