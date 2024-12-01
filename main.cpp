#include <iostream>
using namespace std;
//class Value{};
//class Operation{};

enum Type { INT,OP,CP,PLUS,MULT };
class Token{
public:
    Token(long _value) : value(_value), type(INT), prior(0) {}
    Token(Type _type, int _prior) : type(_type), prior(_prior), value(0) {}
    Token(Token &t) : type(t.type), value(t.value), prior(t.prior) {} //copy ctor

    long getValue() {
        return value;
    }
    int getPrior() {
        return prior;
    }
    Type getType() {
        return type;
    }
    friend ostream& operator<<(ostream &os, Token &t);
private:
    
    Type type;
    int prior;
    long value;
};

ostream& operator<<(ostream& os, Token &t){
    switch(t.type){ 
        case INT:
            os << t.value; break;
        case OP:
            os << "("; break;
        case CP:
            os << ")"; break;
        case PLUS:
            os << "+"; break;
        case MULT:
            os << "*"; break;
        default:
            throw logic_error(string("not implemented print for " + t.type));
    }
    return os;
}
class Processor{
public:
    void add(Token token){
        cout << token;
    }
};

class Parser {
public:
    void Parse(string s, Processor &p){
        int i=0;
        while(i<s.size()){
            char c = s[i];
            if(isdigit(c)){
                long v = c - '0';
                ++i;
                while(i<s.size() && isdigit(s[i])){
                    v *= 10;
                    v += (s[i] - '0');
                    ++i;
                }
                p.add(Token(v));
                --i;
            } else if(c == '(') {
                p.add(Token(OP,0));
            } else if(c == ')') {
                p.add(Token(CP,0));
            } else if(c == '+') {
                p.add(Token(PLUS, 1));
            } else if(c == '*') {
                p.add(Token(MULT, 2));
            } else if (!isspace(c)){
                throw logic_error(string("invalid char ") + c);
            }
            ++i;
        }
        
    }
};

int main(){
    string input = "55+21*(23+335)+44";
    Parser parser;
    Processor proc;
    parser.Parse(input,proc);
    cout << endl;
    return 0;
}