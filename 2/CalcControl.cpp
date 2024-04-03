//
// Created by Misha on 20.03.2024.
//

#include "CalcHeaders/Calculator.h"
#include <ostream>
#include <regex>
#include <chrono>

using namespace std;

Operator GetOperator(char ch)
{
    switch(ch)
    {
        case '+':
            return Operator::ADD;
        case '-':
            return Operator::SUB;
        case '*':
            return Operator::MUL;
        case '/':
            return Operator::DIV;
        default:
            return Operator::NOTANOPERATOR;
    }
}

void LineProcessor(Calculator& calc, const string& line)
{
    //vector pair regex
    //array
    vector<pair<regex, function<void(const smatch& match)>>> commandMap
            {
                    {regex(R"(var\s+([a-zA-Z_][a-zA-Z0-9_]*))"), [&calc](const smatch& match)
                                                                 {   calc.VarExec(match[1]); }},
                    {regex(R"(let\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*(-?\d+\.?\d*))"), [&calc](const smatch& match)
                                                                 {   calc.LetExec(match[1], stod(match[2])); }},
                    {regex(R"(let\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z_][a-zA-Z0-9_]*))"), [&calc](const smatch& match)
                                                                 {   calc.LetExec(match[1], match[2]); }},
                    {regex(R"(fn\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z_][a-zA-Z0-9_]*))"), [&calc](const smatch& match)
                                                                 {   calc.FnExec(match[1], match[2]); }},
                    {regex(R"(fn\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*([+\-*/])\s*([a-zA-Z_][a-zA-Z0-9_]*))"),
                            [&calc](const smatch& match)
                                                                 {   calc.FnExec(match[1], match[2], GetOperator(match[3].str()[0]), match[4]); }},
                    {regex(R"(print\s+([a-zA-Z_][a-zA-Z0-9_]*))"), [&calc](const smatch& match)
                                                                 {

                                                                     ostringstream s;
                                                                     s << fixed << setprecision(PRECISION) << calc.GetValueExec(match[1]);
                                                                     cout << match[1] << ": " << s.str() << endl;
                                                                 }},
                    {regex(R"(printvars)"), [&calc](const smatch& match)
                                                                 {
                                                                     for (const auto& unit: calc.GetVarsExec())
                                                                     {
                                                                         ostringstream s;
                                                                         s << fixed << setprecision(PRECISION) << unit.second;
                                                                         cout << unit.first << ": " << s.str() << endl;
                                                                     }
                                                                 }},
                    {regex(R"(printfns)"), [&calc](const smatch& match)
                                                                 {
                                                                     for (const auto& unit: calc.GetFnsExec())
                                                                     {
                                                                         ostringstream s;
                                                                         s << fixed << setprecision(PRECISION) << unit.second;
                                                                         cout << unit.first << ": " << s.str() << endl;
                                                                     }
                                                                 }}
            };

    try {
        for (const auto& cmd : commandMap)
        {
            smatch match;
            if (regex_match(line, match, cmd.first))
            {
                cmd.second(match);
                return;
            }
        }
        cout << "error: invalid command!" << endl;
    }
    catch(NoIdentError& e)
    {
        cout << "error: id " << e.getName() << " does not exists!" << endl;
    }
    catch(IdentAlreadyExistsError& e)
    {
        cout << "error: id " << e.getName() << " already exists!" << endl;
    }
}

void SplitStream(Calculator &calc)
{
    string line;
    while (getline(cin,line))
    {
        LineProcessor(calc, line);
    }
}

int main()
{
    Calculator calc{}; // создаем объект класса Calc
    SplitStream(calc);
    return 0;
}
