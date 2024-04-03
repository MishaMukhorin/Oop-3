//
// Created by Misha on 13.03.2024.
//

#ifndef OOP_3_CALCULATOR_H
#define OOP_3_CALCULATOR_H

#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>
#include <memory>
#include <algorithm>
#include <optional>

#include "Variable.h"
#include "Function.h"
#include "CalculatorErrors.h"

const int PRECISION = 2;

class Calculator
{
public:

    Calculator() = default;

    explicit Calculator(int reservation)
    :m_units(reservation) {}

    void LetExec(const std::string& name, double value);
    void LetExec(const std::string& name, const std::string& operandName);
    void VarExec(const std::string& name);

    void FnExec(const std::string& name, const std::string& operand);
    void FnExec(const std::string& name, const std::string& operand1, Operator op, const std::string& operand2);

    // cделать константными
    double GetValueExec(const std::string &name);
    // callback функция не возвращать и добавить map функций и переменных
    std::vector<std::pair<std::string, double>> GetVarsExec();
    std::vector<std::pair<std::string, double>> GetFnsExec();

    void ClearCalculator() { m_units.clear(); }

private:
    // безопасно обрабатывать исключения
    std::unordered_map<std::string, std::unique_ptr<Unit>> m_units;
    // gsl::finally почитать

    static double GetUnit(Unit* unit);

    static void CalculateCache(Unit *currFn, const Operator &currOp, double op1, double op2);

    static void EvalFn(Unit* func);

    static void ClearCache(Unit* var);

    void CheckOperandInContext(const std::string &operand) const;

    static std::optional<double> ProcessOperand(Unit *operand);
};


#endif //OOP_3_CALCULATOR_H
