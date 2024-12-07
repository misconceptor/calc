#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;
//class Value{};
//class Operation{};

enum Type { END,INT,OP,CP,PLUS,MULT };
//токен - то, что взято из входного потока
//class Token хранит тип токена, для операнда хранит значение,
// а для операции - ее тип и приоритет
class Token{ 
private:
    Type type;
    int prior;
    long value;
public:
    Token(long _value) : value(_value), type(INT), prior(0) {}
    Token(Type _type, int _prior) : type(_type), prior(_prior), value(0) {}
    Token(const Token &t) : type(t.type), value(t.value), prior(t.prior) {} //copy ctor

    Token& operator=(const Token& rhs){
        this->value = rhs.value;
        this->prior= rhs.prior;
        this->type= rhs.type;
        return *this;
    }

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
};

ostream& operator<<(ostream& os, Token &t){
    switch(t.type){ 
        case END:
            break;
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
        default:{
            throw logic_error(string("not implemented print for ")+to_string(t.type));
        }
    }
    return os;
}
class Processor{
private:
    deque<Token> d; // for rpn
    stack<Token> s; // for operations
public:
    void add(Token t){
        switch(t.getType()){ 
            case END:
                while(!s.empty()){ 
                    d.push_back(s.top());
                    s.pop();
                } 
                for(auto i : d){
                    cout << i << ' ';
                }
                cout << endl;
                break;
            case INT:
                d.push_back(t);
                break;
            case PLUS: case MULT:
                while(!s.empty() && s.top().getPrior() >= t.getPrior()){ //checking the precedence of operations 
                    d.push_back(s.top());
                    s.pop();
                } 
                s.push(t);
                break;
            default:{
                throw logic_error(string("not implemented process for ")+to_string(t.getType()));
            }
        }
    }
private:
    bool isOperation(Type t) {
        return t == PLUS || t == MULT;
    }
};
//Parser разбивает входную строку на токены и добавляет их в Processor
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
        p.add(Token(END,0)); 
    }
};

int main(){
    string input = "5+3+4*5*7+5*3";
    Parser parser;
    Processor proc;
    parser.Parse(input,proc);
    //TODO : OP AND CP
    cout << endl;
    return 0;
}