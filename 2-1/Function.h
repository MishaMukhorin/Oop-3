#include <string>
#include <cmath>
#include <stdexcept>
#include <map>
#include <utility>
#include "Variable.h"

class Function {
public:
    enum class Operation { ADD, SUBTRACT, MULTIPLY, DIVIDE, DEFAULT };

    Function();

    Function(std::string  operand1, Operation operation, std::string  operand2);

    double operator()(const std::map<std::string, Variable>& variables) const;

    [[nodiscard]] static double GetVariableValue(const std::map<std::string, Variable>& variables, const std::string& identifier) ;

    static Operation DetermineOperation(const std::string& operationStr);

private:
    std::string m_arg1_;
    std::string m_arg2_;
    Operation m_op_;



};
