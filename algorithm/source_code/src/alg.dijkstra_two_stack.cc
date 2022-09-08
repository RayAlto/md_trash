#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <utility>

#include <cmath>

#include "alg.h"

double evaluate(const std::string& expression) {
    /**
     * 尊重原书，这里假设用户输入的每一个部分都用空格隔开了，比如：
     *     "( 1 + ( ( 2 + 3 ) * ( 4 * 5 ) ) )"
     * 而不是像这样：
     *     "(1+((2+3)*(4*5)))"
     */
    std::stack<std::string> ops;
    std::stack<double> vals;
    std::istringstream iss(expression);
    std::string s;
    while (iss >> s) {
        if (s == "(") {
            continue;
        }
        if (s == "+") {
            ops.push(s);
        }
        else if (s == "-") {
            ops.push(s);
        }
        else if (s == "*") {
            ops.push(s);
        }
        else if (s == "/") {
            ops.push(s);
        }
        else if (s == "sqrt") {
            ops.push(s);
        }
        else if (s == ")") {
            std::string op = std::move(ops.top());
            ops.pop();
            double rv = vals.top();
            vals.pop();
            if (op == "+") {
                double lv = vals.top();
                vals.pop();
                rv += lv;
            }
            else if (op == "-") {
                double lv = vals.top();
                vals.pop();
                rv -= lv;
            }
            else if (op == "*") {
                double lv = vals.top();
                vals.pop();
                rv *= lv;
            }
            else if (op == "/") {
                double lv = vals.top();
                vals.pop();
                rv /= lv;
            }
            else if (op == "sqrt") {
                rv = std::sqrt(rv);
            }
            vals.push(rv);
        }
        else {
            vals.push(std::stod(s));
        }
    }
    return vals.top();
}

int main(int argc, char const* argv[]) {
    std::string expression = alg::parse_string_arg(argc, argv);
    std::cout << expression << " = " << evaluate(expression) << std::endl;
    return 0;
}
