//
// Created by tomer on 12/18/18.
//



// CPP program to evaluate a given
// expression where tokens are
// separated by space.
#include "Dijkstra.h"

// Function to find precedence of
// operators.
int Dijkstra::precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Function to perform arithmetic operations.
Expression *Dijkstra::applyOp(double a, double b, char op) {
    switch (op) {
        case '+':
            return new PlusExpression(new Num(a), new Num(b));
        case '-':
            return new MinusExpression(new Num(a), new Num(b));
        case '*':
            return new MultiplyExpression(new Num(a), new Num(b));
        case '/':
            return new DivideExpression(new Num(a), new Num(b));
    }
}

// Function that returns value of
// expression after evaluation.
double Dijkstra::evaluate(string tokens) {
    bool first_op= false;
    int i;
    // stack to store integer values.
    stack<double> values;

    // stack to store operators.
    stack<char> ops;

    // negative number can be in 2 ways-> a. in the begining. b. after operator


    for (i = 0; i < tokens.length(); i++) {
        bool afterPoint = false;
        double float_num = 10;
        // Current token is a whitespace,
        // skip it.
        if (tokens[i] == ' ')
            continue;

            // Current token is an opening
            // brace, push it to 'ops'
        else if (tokens[i] == '(') {
            ops.push(tokens[i]);
        }

            // Current token is a number, push
            // it to stack for numbers.
        else if (isdigit(tokens[i])) {
            double val = 0;

            // There may be more than one
            // digits in number.
            while (i < tokens.length() && isdigit(tokens[i])
                   || tokens[i] == '.') {
                if (tokens[i] == '.') {
                    afterPoint = true;
                } else {
                    if (!afterPoint)
                        val = (val * 10) + (tokens[i] - '0');
                    else {
                        val += (tokens[i] - '0') / float_num;
                        float_num *= 10;
                    }
                }
                i++;
            }

            values.push(val);
        }

            // Closing brace encountered, solve
            // entire brace.
        else if (tokens[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double val2 = values.top();
                values.pop();

//                double val1 = values.top();
//                values.pop();

                double val1;
                // check for neg number
                if (values.empty()) {
                    val1 = 0; // 0 - num = -num
                } else {
                    val1 = values.top();
                    values.pop();
                }
                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op)->calculate());
            }

            // pop opening brace.
            ops.pop();
        }

            // Current token is an operator.
        else {
            // While top of 'ops' has same or greater
            // precedence to current token, which
            // is an operator. Apply operator on top
            // of 'ops' to top two elements in values stack.
            first_op = true;
            while (!ops.empty() && precedence(ops.top())
                                   >= precedence(tokens[i])) {
                double val2 = values.top();
                values.pop();

                double val1;
                // check for neg number
                if (values.empty()) {
                    val1 = 0; // 0 - num = -num
                } else {
                    val1 = values.top();
                    values.pop();
                }

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op)->calculate());
            }

            // Push current token to 'ops'.
            ops.push(tokens[i]);
        }
    }

    // Entire expression has been parsed at this
    // point, apply remaining ops to remaining
    // values.
    while (!ops.empty()) {
        double val2 = values.top();
        values.pop();

//        double val1 = values.top();
//        values.pop();

        double val1;
        // check for neg number
        if (values.empty()) {
            val1 = 0; // 0 - num = -num
        } else {
            val1 = values.top();
            values.pop();
        }

        char op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op)->calculate());
    }

    // Top of 'values' contains result, return it.
    return values.top();
}


double Dijkstra::operator()(char *str) {
    string string1 = (string) str;
    double result = evaluate(string1);
    return result;
}

double Dijkstra::operator()(string str) {
    double result = evaluate(str);
    return result;
}