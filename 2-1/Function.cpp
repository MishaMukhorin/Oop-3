#include "Function.h"

#include <utility>

double Function::GetVariableValue(const std::map<std::string, Variable>& variables, const std::string& identifier) {
    auto it = variables.find(identifier);
    if (it == variables.end()) {
        throw std::runtime_error("Unknown variable in function " + identifier);
    }
    return it->second.GetValue();
}

Function::Operation Function::DetermineOperation(const std::string& operationStr) {
    if (operationStr == "+") {
        return Operation::ADD;
    } else if (operationStr == "-") {
        return Operation::SUBTRACT;
    } else if (operationStr == "/" || operationStr == ":") {
        return Operation::DIVIDE;
    } else if (operationStr == "*") {
        return Operation::MULTIPLY;
    } else {
        return Operation::DEFAULT;
    }
}


double Function::operator()(const std::map<std::string, Variable>& variables) const  {
    double m_arg1_value, m_arg2_value;

    try {
        m_arg1_value = GetVariableValue(variables, m_arg1_);
    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }

    if (m_op_ != Operation::ADD && m_op_ != Operation::SUBTRACT && m_op_ != Operation::MULTIPLY && m_op_ != Operation::DIVIDE) {
        throw std::runtime_error("Invalid operation in function");
    }

    if (m_arg2_.empty()) {
        switch (m_op_) {
            case Operation::ADD:
                return m_arg1_value;
            case Operation::SUBTRACT:
                return -m_arg1_value;
            default:
                throw std::runtime_error("Invalid operation in function");
        }
    }

    try {
        m_arg2_value = GetVariableValue(variables, m_arg2_);
    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }

    switch (m_op_) {
        case Operation::ADD:
            return m_arg1_value + m_arg2_value;
        case Operation::SUBTRACT:
            return m_arg1_value - m_arg2_value;
        case Operation::MULTIPLY:
            return m_arg1_value * m_arg2_value;
        case Operation::DIVIDE:
            if (std::fabs(m_arg2_value) < 1e-9) {
                throw std::runtime_error("Error evaluating function: division by zero");
            }
            return m_arg1_value / m_arg2_value;
        case Operation::DEFAULT:
            break;
    }
}

Function::Function(std::string operand1, const Function::Operation operation, std::string operand2)
        : m_arg1_(std::move(operand1)), m_op_(operation), m_arg2_(std::move(operand2)) {}

Function::Function()
        : m_op_(Function::Operation::DEFAULT) {}
