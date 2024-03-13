#include <cmath>

class Variable {
public:
    explicit Variable(double value) : value_(value) {}
    Variable() : value_(NAN) {}

    [[nodiscard]] double GetValue() const { return value_; }
    void SetValue(double value) { value_ = value; }

private:
    double value_;
};