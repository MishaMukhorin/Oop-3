#include <unordered_map>
#include <map>
#include <cmath>
#include "iostream"
#include "Function.h"


class Calculator {
public:
    void DeclareVariable(const std::string& identifier);
    void DeclareFunction(const std::string& identifier, const std::string& operand1, const std::string& operation, const std::string& operand2 = "");
    void AssignVariable(const std::string& identifier1, const std::string& identifier2);
    void AssignVariable(const std::string& identifier, double value);
    void PrintFunctions() const;
    double Evaluate(const std::string& expression) const;

private:
    std::unordered_map<std::string, Variable> variables_;
    std::map<std::string, Function> functions_;

    bool IsValidVariableName(const std::string& identifier);
    bool VariableExists(const std::string& identifier) { return variables_.find(identifier) != variables_.end(); }
    double GetVariableValue(const std::string& identifier);
    void SetVariableValue(const std::string& identifier, double value);



};

