#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class FunctionPart {
public:
    FunctionPart(char new_operation, double new_value) {
        operation = new_operation;
        value = new_value;
    }
    double Apply(double source_value) const {
        if (operation == '+') {
            return source_value + value;
        } else if (operation == '-') {
            return source_value - value;
        } else if (operation == '*') {
            return source_value * value;
        } else {
            return source_value / value;
        }
    }
    void Invert() {
        if (operation == '+') {
            operation = '-';
        } else if (operation == '-') {
            operation = '+';
        } else if (operation == '*') {
            operation = '/';
        } else {
            operation = '*';
        }
    }
private:
    char operation;
    double value;
};

class Function {
public:
    void AddPart(char operation, double x) {
        parts.push_back({operation, x});
    }
    double Apply(double x) const {
        for (const FunctionPart& part : parts) {
            x = part.Apply(x);
        }
        return x;
    }
    void Invert() {
        for (FunctionPart& part : parts) {
            part.Invert();
        }
        reverse(parts.begin(), parts.end());
    }
private:
    vector<FunctionPart> parts;
};
