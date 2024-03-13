#include "Calculator.h"



bool Calculator::IsValidVariableName(const std::string &identifier) {
    if (identifier.empty() || std::isdigit(identifier[0])) {
        return false;
    }
    for (char c: identifier)
    {
        if (c == ' ')
            return false;
    }
    return true;
}


double Calculator::GetVariableValue(const std::string &identifier) {
    if (VariableExists(identifier)) {
        return variables_[identifier].GetValue();
    }
    else {
        return NAN;
    }
}

void Calculator::SetVariableValue(const std::string& identifier, double value) {
    // проверяем, что переменная с таким идентификатором существует
    if (!VariableExists(identifier)) {
        std::cout << "Error: Variable " << identifier << " has not been declared." << std::endl;
        return;
    }

    // устанавливаем новое значение переменной
    variables_[identifier].SetValue(value);
}

void Calculator::DeclareVariable(const std::string &identifier) {

    if (variables_.count(identifier)) {
        std::cout << "Error: variable " << identifier << " already declared\n";
        return;
    }

    variables_[identifier] = *new Variable();
}

void Calculator::AssignVariable(const std::string& identifier1, const std::string& identifier2)
{
    // Проверяем, что идентификатор1 является допустимым именем переменной
    if (!IsValidVariableName(identifier1)) {
        std::cout << "Invalid variable name: " << identifier1 << std::endl;
        return;
    }
    // Проверяем, что идентификатор2 является допустимым именем переменной или числом
    if (!IsValidVariableName(identifier2)) {
        std::cout << "Invalid variable name: " << identifier2 << std::endl;
        return;
    }

    // Если идентификатор1 еще не был объявлен, создаем новую переменную
    if (!VariableExists(identifier1)) {
        Calculator::DeclareVariable(identifier1);
    }

    // Присваиваем значение переменной
    variables_[identifier1].SetValue(variables_[identifier2].GetValue());
}

void Calculator::AssignVariable(const std::string& identifier, double value) {
    // Проверяем, что идентификатор является допустимым именем переменной
    if (!IsValidVariableName(identifier)) {
        std::cout << "Error: Invalid variable name." << std::endl;
        return;
    }

    // Проверяем, что переменная с таким идентификатором существует
    if (!VariableExists(identifier)) {
        // Если переменная не существует, объявляем ее со значением value
        DeclareVariable(identifier);
        SetVariableValue(identifier, value);
    } else {
        // Если переменная существует, присваиваем ей значение value
        SetVariableValue(identifier, value);
    }
}

void Calculator::DeclareFunction(const std::string& identifier, const std::string& operand1, const std::string& operationStr, const std::string& operand2) {
    // Check if the function identifier has already been declared
    if (variables_.count(identifier) || functions_.count(identifier)) {
        std::cout << "Error: Identifier '" << identifier << "' has already been declared as a variable or function.\n";
        return;
    }

    Function::Operation operation = Function::DetermineOperation(operationStr);

    // Check if the operands are valid identifiers
    if (!IsValidVariableName(operand1) || (!operand2.empty() && !IsValidVariableName(operand2))) {
        std::cout << "Error: Invalid operand(s).\n";
        return;
    }

    // Check if the operation is valid
    if (operation == Function::Operation::DEFAULT) {
        std::cout << "Error: Invalid operation.\n";
        return;
    }

    // Add the function to the map of functions
    functions_[identifier] = *new Function(operand1, operation, operand2);

}

void Calculator::PrintFunctions() const {
    // Проверяем, есть ли функции в нашем словаре
    if (functions_.empty()) {
        std::cout << "No user-defined functions found." << std::endl;
        return;
    }

    // Итерируемся по всем парам ключ-значение в словаре functions
    std::cout << "User-defined functions:" << std::endl;
    for (const auto& function : functions_) {
        std::cout << function.first << " = ";

        // Если у функции нет аргументов, выводим только ее значение
        if (function.second.) {
            std::cout << function.second.GetVariableValue() << std::endl;
        }
            // Если у функции есть аргументы, выводим ее определение
        else {
            std::cout << function.second.arg1 << " ";
            std::cout << function.second.operation << " ";
            std::cout << function.second.arg2 << std::endl;
        }
    }

}














