//
// Created by Misha on 13.03.2024.
//

#ifndef OOP_3_FUNCTION_H
#define OOP_3_FUNCTION_H

#include <optional>
#include <string>
#include <utility>
#include <vector>
#include "Unit.h"


class Function: public Unit
{
public:

    Function(const std::string& name,
             Unit* operand1,
             Operator op,
             Unit* operand2 ):
             Unit(name),
             m_operand1(operand1),
             m_operator(op),
             m_operand2(operand2) {}

    Function(const std::string& name,
             Unit* operand1):
             Unit(name),
             m_operand1(operand1),
             m_operator(Operator::NOTANOPERATOR),
             m_operand2(nullptr) {}

    [[nodiscard]] Operator GetOperator() const override { return m_operator; }
    [[nodiscard]] bool CheckOperator() const override { return m_operator != Operator::NOTANOPERATOR; }

    [[nodiscard]] std::pair<Unit*, Unit*> GetOperands() const override { return {m_operand1, m_operand2}; }

    bool CheckCache() override { return m_value.has_value(); }
    void ClearCache() override { m_value = std::nullopt; }

    [[nodiscard]] double GetValue() const override { return m_value.value(); }
    void SetValue(double v) override { m_value.emplace(v); }

     UnitType GetType() override { return UnitType::Function; }

private:
    Unit* m_operand1;
    Unit* m_operand2;
    Operator m_operator;
    std::optional<double> m_value;
};

#endif //OOP_3_FUNCTION_H
