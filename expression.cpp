#include "expression.hpp"
#include <stdexcept>

Val::Val(int64_t x) : value(x) {}

void Val::print(std::ostream &in) const { in << this->value; }

int64_t Val::eval()               const { return this->value; }
int64_t Val::eval(const Context&) const { return this->value; }

Expression* Val::simplified(const Context&) const {
    return new Val(this->value);
}

Add::Add(Expression* l, Expression* r) : left(l), right(r) {}

void Add::print(std::ostream &in) const{
    in << "(";
    this->left->print(in);
    in << " + ";
    this->right->print(in);
    in << ")";
}

int64_t Add::eval()                   const { return left->eval() + right->eval(); }
int64_t Add::eval(const Context& cnt) const { return left->eval(cnt) + right->eval(cnt); }

Add::~Add() {
    delete left;
    delete right;
}

Expression* Add::simplified(const Context& cnt) const {
    return new Add(left->simplified(cnt), right->simplified(cnt));
}

Mul::Mul(Expression* l, Expression* r) : left(l), right(r) {}

void Mul::print(std::ostream &in) const {
    this->left->print(in);
    in << " * ";
    this->right->print(in);
}

int64_t Mul::eval()                   const { return left->eval() * right->eval(); }
int64_t Mul::eval(const Context& cnt) const { return left->eval(cnt) * right->eval(cnt); }

Mul::~Mul() {
    delete left;
    delete right;
}

Expression *Mul::simplified(const Context& cnt) const {
    return new Mul(left->simplified(cnt), right->simplified(cnt));
}

Var::Var(const std::string& s) : str(s) {}

void Var::print(std::ostream &in) const { in << str; }

int64_t Var::eval()            const { throw std::runtime_error("you have no power here");}
int64_t Var::eval(Context cnt) const { return cnt.getVar(this->str); }

Expression* Var::simplified(const Context& cnt) const {
    int64_t cur;
    try {
        cur = this->eval(cnt);
        return new Val(cur);
    } catch (std::runtime_error e) {
        return new Var(this->str);
    }
}

int64_t Context::getVar(const std::string &name) const {
    auto srch = dict.find(name);
    if (srch != dict.end()) {
        return srch->second;
    } else {
        throw std::runtime_error("there is no such variable");
    }
}

void Context::setVar(const std::string &name, int64_t value) {
    dict[name] = value;
}

bool Context::varIsSet(const std::string &name) const {
    return dict.find(name) != dict.end();
}
