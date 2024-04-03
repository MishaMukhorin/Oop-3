//
// Created by Misha on 17.03.2024.
//

#ifndef OOP_3_UNIT_H
#define OOP_3_UNIT_H

#include <string>
#include <deque>
#include <optional>
#include <limits>


enum class Operator {
    ADD, SUB, MUL, DIV, NOTANOPERATOR
};

enum class UnitType {
    Function, Variable
};

class Unit {
public:                                                 // done почищено
    virtual ~Unit() = default;

    explicit Unit(std::string  name) : m_name(std::move(name)) {}

    [[nodiscard]] virtual Operator GetOperator() const = 0;
    [[nodiscard]] virtual bool CheckOperator() const = 0;
    [[nodiscard]] virtual std::pair<Unit*, Unit*> GetOperands() const = 0;

    [[nodiscard]] const std::string& GetName() const { return m_name; };
    void AddDependency(Unit* dep) { m_dependencies.push_back(dep); };
    const std::deque<Unit*>& GetDependencies() { return m_dependencies; };

    [[nodiscard]] virtual double GetValue() const = 0;
    virtual void SetValue(double v) = 0;

    virtual void ClearCache() = 0;
    virtual bool CheckCache() = 0;

    virtual UnitType GetType() = 0;

private:
    std::string m_name;
    std::deque<Unit*> m_dependencies;       //перевести на deque и на указатели
};

#endif //OOP_3_UNIT_H
