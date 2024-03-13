//
// Created by Misha on 13.03.2024.
//

#ifndef OOP_3_VARIABLE_H
#define OOP_3_VARIABLE_H

#include <string>
#include <optional>
#include <string>


class Variable
{
public:
    Variable(const Variable&) = delete;
    Variable& operator=(const Variable&) = delete;
    Variable(const std::string& name) : m_name(name) {}
    Variable(const std::string& name, const std::optional<double>& value) : m_name(name), m_value(value) {}

    const std::string& getName() const { return m_name; }

    const double& getValue() const { return m_value.value(); }
    void setValue(const std::optional<double>& value) { m_value = value; }
    const bool checkValue() { return m_value.has_value(); }

private:
    std::string m_name;
    std::optional<double> m_value;
};


#endif //OOP_3_VARIABLE_H
