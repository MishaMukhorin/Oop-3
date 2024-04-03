//
// Created by Misha on 13.03.2024.
//

#include "CalcHeaders/Calculator.h"

using namespace std;

void Calculator::LetExec(const string& name, double value)
{
    if (!m_units.contains(name))
    {
        m_units.insert({name, make_unique<Variable>(name, value)});
    }
    else
    {
        Unit* var = m_units.at(name).get();
        if (var->GetType() == UnitType::Variable)
        {
            var->SetValue(value);
            ClearCache(var);
        }
        else
        {
            throw IdentAlreadyExistsError(name);
        }
    }
}

void Calculator::ClearCache(Unit* var)
{
    queue<Unit*> clearCacheQ;
    clearCacheQ.push(var);
    while (!clearCacheQ.empty())
    {
        Unit* currDep = clearCacheQ.front();
        clearCacheQ.pop();
        if (currDep->CheckCache())
        {
            currDep->ClearCache();
            for(const auto& dep: currDep->GetDependencies())
            {
                clearCacheQ.push(dep);
            }
        }
    }
}

void Calculator::LetExec(const string& name, const string& operandName)
{
    CheckOperandInContext(operandName);
    Unit* operandUnit = m_units.at(operandName).get();

    if (!operandUnit->CheckCache())
    {
        EvalFn(operandUnit);
    }
    if (!m_units.contains(name))
    {
        m_units.insert({name, make_unique<Variable>(name, operandUnit->GetValue())});
    }
    else
    {
        Unit* var = m_units.at(name).get();
        if (var->GetType() == UnitType::Variable)
        {
            var->SetValue(operandUnit->GetValue());
            ClearCache(var);
        }
        else
        {
            throw IdentAlreadyExistsError(name);
        }
    }
}

void Calculator::VarExec(const string& name)
{
    if (m_units.contains(name))
    {
        throw IdentAlreadyExistsError(name);
    }
    m_units.insert({name, make_unique<Variable>(name)});
}

void Calculator::FnExec(const string &name, const string &operand)
{
    CheckOperandInContext(operand);
    if (m_units.contains(name))
    {
        throw IdentAlreadyExistsError(name);
    }
    Unit* operandUnit = m_units.at(operand).get();
    m_units.insert({name, make_unique<Function>(name, operandUnit)});

    operandUnit->AddDependency(m_units.at(name).get());
}

void Calculator::FnExec(const string &name, const string &operand1, Operator op, const string &operand2)
{
    CheckOperandInContext(operand1);
    CheckOperandInContext(operand2);
    if (m_units.contains(name))
    {
        throw IdentAlreadyExistsError(name);
    }
    Unit* operandUnit1 = m_units.at(operand1).get();
    Unit* operandUnit2 = m_units.at(operand2).get();

    m_units.insert({name, make_unique<Function>(name, operandUnit1, op, operandUnit2)});
    Unit* func = m_units.at(name).get();

    operandUnit1->AddDependency(func);
    operandUnit2->AddDependency(func);
}

void Calculator::CheckOperandInContext(const string &operand) const
{
    if (!(m_units.contains(operand)))
    {
        throw NoIdentError(operand);
    }
}

double Calculator::GetValueExec(const std::string &name)
{
    CheckOperandInContext(name);
    Unit* unit = m_units.at(name).get();
    if (!unit->CheckCache())
    {
        EvalFn(unit);
    }
    return GetUnit(unit);
}

//принимать ссылку
void Calculator::EvalFn(Unit* func)
{
    stack<Unit*> evalStack;
    evalStack.push(func);
    while (!evalStack.empty())
    {
        Unit* currFn = evalStack.top();
        evalStack.pop();
        pair<Unit*, Unit*> operands = currFn->GetOperands();

        optional<double> operandValue1, operandValue2;
        operandValue1 = ProcessOperand(operands.first);
        if (!operandValue1.has_value())
        {
            evalStack.push(currFn);
            evalStack.push(operands.first);
            continue;
        }
        if (currFn->CheckOperator())// hasOperator
        {
            operandValue2 = ProcessOperand(operands.second);
            if (!operandValue2.has_value())
            {
                evalStack.push(currFn);
                evalStack.push(operands.second);
                continue;
            }
            Operator currOp = currFn->GetOperator();
            CalculateCache(currFn, currOp, operandValue1.value(), operandValue2.value());
        }
        else
        {
            currFn->SetValue(operandValue1.value());
        }
    }
}

optional<double> Calculator::ProcessOperand(Unit* operand)
{
    if (operand->CheckCache())
    {
        return operand->GetValue();
    }
    return nullopt;
}


void Calculator::CalculateCache(Unit* currFn, const Operator &currOp, double op1, double op2)
{
    switch (currOp)
    {
        case Operator::ADD:
            currFn->SetValue(op1 + op2);
            break;
        case Operator::SUB:
            currFn->SetValue(op1 - op2);
            break;
        case Operator::DIV:
            currFn->SetValue(op1 / op2);
            break;
        case Operator::MUL:
            currFn->SetValue(op1 * op2);
            break;
        case Operator::NOTANOPERATOR:
            break;
    }
}

double Calculator::GetUnit(Unit* unit)
{
    return unit->GetValue();
}

vector<pair<string, double>> Calculator::GetVarsExec()
{
    vector<pair<string, double>> result;

    std::vector<std::pair<std::string, Unit*>> unitsVec;
    unitsVec.reserve(m_units.size());

    for (auto& pair : m_units)
    {
        unitsVec.emplace_back(pair.first, pair.second.get());
    }

    std::sort(unitsVec.begin(), unitsVec.end());

    for (const auto& unit: unitsVec)
    {
        if (unit.second->GetType() == UnitType::Variable)
        {
            result.emplace_back(unit.first, GetUnit(unit.second));
        }
    }
    return result;
}

vector<pair<string, double>> Calculator::GetFnsExec()
{
    vector<pair<string, double>> result;

    std::vector<std::pair<std::string, Unit*>> unitsVec;
    unitsVec.reserve(m_units.size());

    for (auto& pair : m_units)
    {
        unitsVec.emplace_back(pair.first, pair.second.get());
    }

    std::sort(unitsVec.begin(), unitsVec.end());

    for (const auto& unit: unitsVec)
    {
        if (unit.second->GetType() == UnitType::Function)
        {
            if (!unit.second->CheckCache())
            {
                EvalFn(unit.second);
            }
            result.emplace_back(unit.first, GetUnit(unit.second));
        }
    }
    return result;
}
