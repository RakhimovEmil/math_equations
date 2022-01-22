#pragma once
#include <fstream>
#include <string>
#include <unordered_map>

class Context {
public:
    // throws exception if there is no variable
    int64_t getVar(std::string const& name) const;

    // overwrites the variable if it already exists 
    void setVar(std::string const& name, int64_t value);

    // checks if the variable is set in the context of
    bool varIsSet(std::string const& name) const;

private:
    std::unordered_map<std::string, int64_t> dict;
};

class Expression {
public:
    virtual void print(std::ostream& in) const = 0;
    virtual int64_t eval() const = 0;
    virtual int64_t eval(const Context&) const = 0;
    virtual Expression* simplified(const Context&) const = 0;
    Expression& operator=(Expression&) = delete;
    virtual ~Expression() = default;
};

class Val : public Expression {
public:
    Val(int64_t);

    void print(std::ostream& in) const override;
    int64_t eval() const override;
    int64_t eval(const Context&) const override;
    Expression* simplified(const Context&) const override;
private:
    int64_t value = 0;
};

class Add : public Expression {
public:
    Add(Expression*, Expression*);

    void print(std::ostream& in) const override;
    int64_t eval() const override;
    int64_t eval(const Context&) const override;
    Expression* simplified(const Context&) const override;

    ~Add() override;
private:
    Expression *left, *right;
};

class Mul : public Expression {
public:
    Mul(Expression*, Expression*);

    void print(std::ostream& in) const override;
    int64_t eval() const override;
    int64_t eval(const Context&) const override;
    Expression* simplified(const Context&) const override;

    Mul& operator=(Mul&) = delete;

    ~Mul() override;
private:
    Expression *left, *right;
};

class Var : public Expression {
public:
    Var(const std::string&);
    void print(std::ostream& in) const override;
    int64_t eval(const Context&) const override;
    int64_t eval() const override;
    Expression* simplified(const Context&) const override;
private:
    std::string str;
};