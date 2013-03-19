/*
 * remove_brackets.h
 *
 *  Created on: 13.06.2012
 *      Author: igor
 */

#ifndef REMOVE_BRACKETS_H_
#define REMOVE_BRACKETS_H_

#include <stack>
#include <stdexcept>
#include <cstdlib>
#include <string>


enum OPER { END, PRIMARY, UNKNOWN, MUL = '*', DIV = '/', ADD = '+', SUB = '-', LP = '(', RP = ')'};

class bad_expression : public std::runtime_error
{
public:
    bad_expression(const std::string& str) : runtime_error(str) {}
};

struct expr
{
    expr() : last_oper(UNKNOWN) {}
    expr(const std::string& p, OPER o = UNKNOWN): prim(p), last_oper(o) {}
    std::string prim;
    OPER last_oper;
};

class Remove_brackets
{
public:
    Remove_brackets(const std::string& s): cur_str(s), ind(0) {}
    std::string Remove();
private:
    OPER get_token();
    int priority(OPER);
    void evalute(OPER);
    std::string cur_str;
    size_t ind;
    std::string operand;
    OPER cur_token;
    std::stack<OPER> oper;
    std::stack<expr> expression;
};

#endif /* REMOVE_BRACKETS_H_ */
