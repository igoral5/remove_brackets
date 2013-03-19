/*
 * remove_brackets.cpp
 *
 *  Created on: 13.06.2012
 *      Author: igor
 */

#include "remove_brackets.h"

std::string Remove_brackets::Remove()
{
    while (get_token() != END)
    {
        switch (cur_token)
        {
        case ADD:
        case SUB:
        case MUL:
        case DIV:
            while (!oper.empty() && priority(cur_token) <= priority(oper.top()))
            {
                evalute(oper.top());
                oper.pop();
            }
            oper.push(cur_token);
            break;
        case LP:
            oper.push(cur_token);
            break;
        case RP:
            while (!oper.empty() && oper.top() != LP)
            {
                evalute(oper.top());
                oper.pop();
            }
            if (oper.empty())
            {
                throw bad_expression("Не найдена открывающая скобка");
            }
            else
            {
                oper.pop();
            }
            break;
        case PRIMARY:
            expression.push(expr(operand));
            break;
        default:
            throw bad_expression("Неверное выражение");
            break;
        }
    }
    while (!oper.empty())
    {
        if (oper.top() == LP)
        {
            throw bad_expression("Не найдена закрывающая скобка");
        }
        else
        {
            evalute(oper.top());
        }
        oper.pop();
    }
    if (expression.empty())
    {
        throw bad_expression("Неверное выражение");
    }
    std::string result = expression.top().prim;
    expression.pop();
    if (!expression.empty())
    {
        throw bad_expression("Неверное выражение");
    }
    return result;
}

OPER Remove_brackets::get_token()
{
    for (;ind < cur_str.length();)
    {
        if (isspace(cur_str[ind]))
        {
            ++ind;
            continue;
        }
        else if (cur_str[ind] == '(')
        {
            ++ind;
            return cur_token = LP;
        }
        else if (cur_str[ind] == ')')
        {
            ++ind;
            return cur_token = RP;
        }
        else if (cur_str[ind] == '*')
        {
            ++ind;
            return cur_token = MUL;
        }
        else if (cur_str[ind] == '/')
        {
            ++ind;
            return cur_token = DIV;
        }
        else if (cur_str[ind] == '+')
        {
            ++ind;
            return cur_token = ADD;
        }
        else if (cur_str[ind] == '-')
        {
            ++ind;
            return cur_token = SUB;
        }
        else
        {
            for (operand = cur_str[ind];;)
            {
                ++ind;
                if (ind == cur_str.length() || isspace(cur_str[ind]) || cur_str[ind] == '*' || cur_str[ind] == '/' || cur_str[ind] == '(' || cur_str[ind] == ')' || cur_str[ind] == '+' || cur_str[ind] == '-')
                    return cur_token = PRIMARY;
                operand = operand + cur_str[ind];
            }
        }
    }
    return cur_token = END;
}

void Remove_brackets::evalute(OPER op)
{
    if (expression.empty())
    {
        throw bad_expression("Не хватает операндов");
    }
    std::string second_operand = expression.top().prim;
    if (priority(expression.top().last_oper) < priority(op))
    {
        second_operand = std::string("(") + second_operand + ")";
    }
    expression.pop();
    if (expression.empty())
    {
        throw bad_expression("Не хватает операндов");
    }
    std::string first_operand = expression.top().prim;
    if (priority(expression.top().last_oper) < priority(op))
    {
        first_operand = std::string("(") + first_operand + ")";
    }
    expression.pop();
    std::string result = first_operand + static_cast<char>(op) + second_operand;
    expression.push(expr(result, op));
}

int Remove_brackets::priority(OPER op) {
    switch (op)
    {
    case LP:
        return 0;
    case RP:
        return 1;
    case ADD:
    case SUB:
        return 2;
    case MUL:
    case DIV:
        return 3;
    default:
        return 5;
    }
}



