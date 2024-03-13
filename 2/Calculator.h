#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Calculator {
public:
    void addFunction(string name, string expression) {
        functions[name] = expression;
    }

    void removeFunction(string name) {
        functions.erase(name);
    }

    void setVariable(string name, double value) {
        variables[name] = value;
    }

    double getVariable(string name) {
        return variables[name];
    }

    double evaluate(string expression) {

    }

    void printFunctions() {
        cout << "Functions:" << endl;
        for (auto& pair : functions) {
            cout << pair.first << " = " << pair.second << endl;
        }
    }

    void printVariables() {
        cout << "Variables:" << endl;
        for (auto& pair : variables) {
            cout << pair.first << " = " << pair.second << endl;
        }
    }

private:
    map<string, string> functions;
    map<string, double> variables;
};