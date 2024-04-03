//
// Created by Misha on 21.03.2024.
//

#include <gtest/gtest.h>
#include <cmath>
#include "../CalcHeaders/Calculator.h"


TEST(CalcTest, testDivByZero)
{
    Calculator calc{};
    calc.LetExec("x", 5);
    calc.LetExec("y", 0);
    calc.FnExec("z", "x", Operator::DIV, "y");
    ASSERT_DOUBLE_EQ(calc.GetValueExec("z"), std::numeric_limits<double>::infinity());
}

TEST(CalcTest, testDivByNan)
{
    Calculator calc{};
    calc.LetExec("x", 5);
    calc.VarExec("y");
    calc.FnExec("z", "x", Operator::DIV, "y");
    ASSERT_TRUE(_isnan(calc.GetValueExec("z")));
}


TEST(CalcTest, testVar)
{
    Calculator calc{};
    calc.VarExec("x");
    ASSERT_TRUE(_isnan(calc.GetValueExec("x")));
    ASSERT_THROW(calc.VarExec("x"), IdentAlreadyExistsError);
}

TEST(CalcTest, testLetId)
{
    Calculator calc{};
    ASSERT_THROW(calc.LetExec("z", "x"), NoIdentError);
    calc.LetExec("h", 8);
    calc.FnExec("y", "h");
    calc.LetExec("z", "y");
    ASSERT_DOUBLE_EQ(calc.GetValueExec("h"), 8);
    ASSERT_DOUBLE_EQ(calc.GetValueExec("z"), 8);
    calc.LetExec("z", 1);
    calc.LetExec("x", "z");
    calc.GetVarsExec();
    ASSERT_THROW(calc.LetExec("y", "x"), IdentAlreadyExistsError);

}

TEST(CalcTest, testLetDouble)
{
    Calculator calc{};
    calc.LetExec("x", 8);
    ASSERT_DOUBLE_EQ(calc.GetValueExec("x"), 8);
    calc.LetExec("y", 9);
    calc.LetExec("x", "y");
    ASSERT_DOUBLE_EQ(calc.GetValueExec("x"), 9);
    calc.FnExec("z", "x");
    ASSERT_THROW(calc.LetExec("z", 11), IdentAlreadyExistsError);

}

TEST(CalcTest, testFn)
{
    Calculator calc{};
    calc.LetExec("y", 9);
    calc.FnExec("x", "y");
    ASSERT_DOUBLE_EQ(calc.GetValueExec("x"), 9);
    calc.FnExec("a1", "x", Operator::ADD, "y");
    calc.FnExec("a2", "x", Operator::MUL, "y");
    calc.FnExec("a3", "x", Operator::DIV, "y");
    calc.FnExec("a4", "x", Operator::SUB, "y");
    calc.FnExec("z", "x");
    std::vector<std::pair<std::string, double>> checkVec;
    checkVec.emplace_back("a1", 18);
    checkVec.emplace_back("a2", 81);
    checkVec.emplace_back("a3", 1);
    checkVec.emplace_back("a4", 0);
    checkVec.emplace_back("x", 9);
    checkVec.emplace_back("z", 9);

    ASSERT_EQ(calc.GetFnsExec(), checkVec);
    ASSERT_THROW(calc.FnExec("a1", "y", Operator::DIV, "x"), IdentAlreadyExistsError);
    ASSERT_THROW(calc.FnExec("a2", "y"), IdentAlreadyExistsError);
    ASSERT_THROW(calc.FnExec("a", "e"), NoIdentError);
}

TEST(CalcTest, XPlusY)
{
    Calculator calc{};
    calc.VarExec("x");
    calc.VarExec("y");
    calc.FnExec("XPlusY", "x", Operator::ADD, "y");
    ASSERT_TRUE(_isnan(calc.GetValueExec("XPlusY")));
    calc.LetExec("x", 3);
    calc.LetExec("y", 4);
    ASSERT_DOUBLE_EQ(calc.GetValueExec("XPlusY"), 7);
    calc.LetExec("x", 10);
    ASSERT_DOUBLE_EQ(calc.GetValueExec("XPlusY"), 14);
    calc.LetExec("z", 3.5);
    calc.FnExec("XPlusYDivZ", "XPlusY", Operator::DIV, "z");
    std::vector<std::pair<std::string, double>> checkVec;
    checkVec.emplace_back("XPlusY", 14);
    checkVec.emplace_back("XPlusYDivZ", 4);
    ASSERT_EQ(calc.GetFnsExec(), checkVec);

}

TEST(CalcTest, CheckFib) {
    Calculator calc{};
    calc.LetExec("a0", 1);
    calc.LetExec("a1", 1);
    for (int i = 2; i < 100; ++i) {
        calc.FnExec("a" + std::to_string(i), "a" + std::to_string(i - 1), Operator::ADD, "a" + std::to_string(i - 2));
    }
    ASSERT_DOUBLE_EQ(calc.GetValueExec("a99"), 354224848179261997056.0);
    ASSERT_THROW(calc.GetValueExec("a100"), NoIdentError);
    calc.LetExec("a0", 2);

    ASSERT_DOUBLE_EQ(calc.GetValueExec("a99"), 489526700523968593920.0);

}

TEST(CalcTest, CheckFibNan) {
    Calculator calc{};
    calc.VarExec("a");
    calc.LetExec("a0", 1);
    calc.LetExec("a1", 1);
    for (int i = 2; i < 100; ++i) {
        calc.FnExec("a" + std::to_string(i), "a" + std::to_string(i - 1), Operator::ADD, "a" + std::to_string(i - 2));
    }
    ASSERT_DOUBLE_EQ(calc.GetValueExec("a99"), 354224848179261997056.0);
    ASSERT_THROW(calc.GetValueExec("a100"), NoIdentError);
    calc.LetExec("a0", "a");

    ASSERT_TRUE(_isnan(calc.GetValueExec("a99")));
}

TEST(CalcTest, CheckMilIncrement)
{
    Calculator calc(1000000);
    calc.LetExec("a0", 1);
    for (int i = 1; i < 1000000; ++i) {
        calc.FnExec("a" + std::to_string(i), "a" + std::to_string(i - 1), Operator::ADD, "a0");
    }
    ASSERT_DOUBLE_EQ(calc.GetValueExec("a999999"), 1000000);
    ASSERT_THROW(calc.GetValueExec("a1000000"), NoIdentError);
}

TEST(CalcTest, CheckMilIncrement1)
{
    auto start = std::chrono::high_resolution_clock::now();

    Calculator calc(1500000);
    calc.LetExec("a0", 1);
    for (int i = 1; i < 1000000; ++i)
    {
        calc.FnExec("a" + std::to_string(i), "a" + std::to_string(i - 1), Operator::ADD, "a0");
    }
    ASSERT_DOUBLE_EQ(calc.GetValueExec("a999999"), 1000000);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    ASSERT_EQ(duration.count() - 1, duration.count());
}


GTEST_API_ int main (int argc, char **argv)
{
    std::cout << "Running tests \n";
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}