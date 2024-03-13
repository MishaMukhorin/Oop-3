
class EngineOffError : public std::logic_error {
public:
    EngineOffError() : std::logic_error("") {}
};

//// speed errors

class IncreaseSpeedError : public std::logic_error {
public:
    IncreaseSpeedError() : std::logic_error("") {}
};

class MaxSpeedError : public std::invalid_argument {
public:
    MaxSpeedError() : std::invalid_argument("") {}
};

class NegativeSpeedError : public std::invalid_argument {
public:
    NegativeSpeedError() : std::invalid_argument("") {}
};

//// gear errors

class GearRangeError : public std::invalid_argument {
public:
    GearRangeError() : std::invalid_argument("") {}
};

class GearSpeedRangeError : public std::invalid_argument {
public:
    GearSpeedRangeError() : std::invalid_argument("") {}
};

class ReverseToForwardError : public std::logic_error {
public:
    ReverseToForwardError() : std::logic_error("") {}
};

class ReverseSpeedError : public std::logic_error {
public:
    ReverseSpeedError() : std::logic_error("") {}
};
