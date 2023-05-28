#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Operator {
    char op;
    int priority;
};

int getPriority(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

double applyOperation(double a, double b, char op) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        return 0;
    }
}


double calculateExpression(const string& expression) {
    stack<double> operandStack;
    stack<Operator> operatorStack;

    for (char c : expression) {
        if (c == ' ')
            continue;

        if (isdigit(c)) {
            double operand = 0;
            while (isdigit(c)) {
                operand = operand * 10 + (c - '0');
                c = expression[++i];
            }
            operandStack.push(operand);
        }
        else if (c == '(') {
            Operator newOperator;
            newOperator.op = c;
            newOperator.priority = 0;
            operatorStack.push(newOperator);
        }
        else if (c == ')') {
            while (!operatorStack.empty() && operatorStack.top().op != '(') {
                char op = operatorStack.top().op;
                double b = operandStack.top();
                operandStack.pop();
                double a = operandStack.top();
                operandStack.pop();
                operandStack.push(applyOperation(a, b, op));
                operatorStack.pop();
            }
            operatorStack.pop();
        }
        else {
            Operator newOperator;
            newOperator.op = c;
            newOperator.priority = getPriority(c);

            while (!operatorStack.empty() && newOperator.priority <= operatorStack.top().priority) {
                char op = operatorStack.top().op;
                double b = operandStack.top();
                operandStack.pop();
                double a = operandStack.top();
                operandStack.pop();
                operandStack.push(applyOperation(a, b, op));
                operatorStack.pop();
            }

            operatorStack.push(newOperator);
        }
    }

    while (!operatorStack.empty()) {
        char op = operatorStack.top().op;
        double b = operandStack.top();
        operandStack.pop();
        double a = operandStack.top();
        operandStack.pop();
        operandStack.push(applyOperation(a, b, op));
        operatorStack.pop();
    }

    return operandStack.top();
}

void calculator() {
    string expression;
    cout << "Введите арифметическое выражение: ";
    getline(cin, expression);

    double result = calculateExpression(expression);
    cout << "Результат: " << result << endl;

   
}