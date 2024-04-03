//
// Created by Misha on 15.03.2024.
//

#ifndef OOP_3_CALCULATORERRORS_H
#define OOP_3_CALCULATORERRORS_H
#include <stdexcept>
#include <utility>


class IdentError : public std::runtime_error {
public:
    explicit IdentError(std::string identName) : std::runtime_error(""), m_name(std::move(identName)) {}

    [[nodiscard]] std::string getName() const { return m_name; }

private:
    std::string m_name;
};

class NoIdentError: public IdentError {
public:
    explicit NoIdentError(std::string identName) : IdentError(std::move(identName)) {}
};


class IdentAlreadyExistsError: public IdentError {
public:
    explicit IdentAlreadyExistsError(std::string identName) : IdentError(std::move(identName)) {}
};

#endif //OOP_3_CALCULATORERRORS_H
