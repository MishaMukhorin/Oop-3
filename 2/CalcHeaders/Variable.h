//
// Created by Misha on 13.03.2024.
//

#ifndef OOP_3_VARIABLE_H
#define OOP_3_VARIABLE_H

#include <optional>
#include <string>
#include <utility>
#include <vector>
#include "Unit.h"

class Variable: public Unit
{
public:
    explicit Variable(std::string name) : Unit(std::move(name))
    {
        m_value = std::numeric_limits<double>::quiet_NaN();
    }
    Variable(std::string  name, const double& value) : Unit(std::move(name)), m_value(value) {}

    [[nodiscard]] Operator GetOperator() const override {return Operator::NOTANOPERATOR; };
    [[nodiscard]] bool CheckOperator() const override { return false; };
    [[nodiscard]] std::pair<Unit*, Unit*> GetOperands() const override { return {nullptr, nullptr}; };

    bool CheckCache() override { return true; }
    void ClearCache() override {}

    [[nodiscard]] double GetValue() const override { return m_value; };
    void SetValue(const double v) override { m_value = v; }

    UnitType GetType() override { return UnitType::Variable; }

private:
    double m_value;
};


#endif //OOP_3_VARIABLE_H
