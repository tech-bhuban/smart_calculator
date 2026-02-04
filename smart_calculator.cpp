
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
class SmartCalculator {
private:
    string expression; 
    
public:
    SmartCalculator(const string& expr) : expression(expr) {}
    
    double evaluate() {
        // Remove spaces
        string expr = expression;
        expr. erase(remove(expr.begin(), expr.end(), ' '), expr.end());
        
        // Handle parentheses
        while (expr.find('(') != string::npos) {
            size_t open = expr.find_last_of('(');
            size_t close = expr.find(')', open);
            string subExpr = expr.substr(open + 1, close - open - 1);
            double result = evaluateSimple(subExpr);
            expr.replace(open, close - open + 1, to_string(result));
        }
        
        return evaluateSimple(expr);
    }
    
private:
    double evaluateSimple(const string& expr) {
        vector<double> numbers;
        vector<char> operators;
        string numStr;
        
        for (char c : expr) {
            if (isdigit(c) || c == '.') {
                numStr += c;
            } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                if (!numStr.empty()) {
                    numbers.push_back(stod(numStr));
                    numStr.clear();
                }
                operators.push_back(c);
            }
        }
        
        if (!numStr.empty()) {
            numbers.push_back(stod(numStr));
        }
        
        // Handle exponentiation first
        for (size_t i = 0; i < operators.size(); i++) {
            if (operators[i] == '^') {
                numbers[i] = pow(numbers[i], numbers[i + 1]);
                numbers.erase(numbers.begin() + i + 1);
                operators.erase(operators.begin() + i);
                i--;
            }
        }
        
        // Handle multiplication and division
        for (size_t i = 0; i < operators.size(); i++) {
            if (operators[i] == '*' || operators[i] == '/') {
                if (operators[i] == '*') {
                    numbers[i] *= numbers[i + 1];
                } else {
                    if (numbers[i + 1] != 0) {
                        numbers[i] /= numbers[i + 1];
                    } else {
                        throw runtime_error("Division by zero");
                    }
                }
                numbers.erase(numbers.begin() + i + 1);
                operators.erase(operators.begin() + i);
                i--;
            }
        }
        
        // Handle addition and subtraction
        double result = numbers[0];
        for (size_t i = 0; i < operators.size(); i++) {
            if (operators[i] == '+') {
                result += numbers[i + 1];
            } else if (operators[i] == '-') {
                result -= numbers[i + 1];
            }
        }
        
        return result;
    }
};

int main() {
    cout << "=== Smart Calculator ===\n";
    cout << "Supported operations: + - * / ^ ( )\n";
    cout << "Example: 2 + 3 * (4 - 1) / 2\n\n";
    
    string expr;
    cout << "Enter expression: ";
    getline(cin, expr);
    
    try {
        SmartCalculator calc(expr);
        double result = calc.evaluate();
        cout << "Result: " << result << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    return 0;
}


