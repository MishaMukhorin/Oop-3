#include <gtest/gtest.h>
#include "../Car.h"


TEST(CarTest, CanSetGearOneAfterTurnOn)
{
    CCar car{};
    ASSERT_TRUE(car.TurnOnEngine());
    ASSERT_TRUE(car.IsTurnedOn());
    EXPECT_NO_THROW(car.SetGear(1));
}

TEST(CarTest, CannotTurnOffEngineIfCarIsMoving)
{
    CCar car{};
    car.TurnOnEngine();
    car.SetGear(1);
    car.SetSpeed(20);
    ASSERT_FALSE(car.TurnOffEngine());
}

TEST(CarTest, CanTurnOffEngine)
{
    CCar car{};
    car.TurnOnEngine();
    ASSERT_TRUE(car.TurnOffEngine());
    ASSERT_FALSE(car.IsTurnedOn());
}

TEST(CarTest, CantSetGearEngintTOff)
{
    CCar car{};
    EXPECT_THROW(car.SetGear(1), EngineOffError);
}

TEST(CarTest, CantSetSpeedInNeutral)
{
    CCar car{};
    car.TurnOnEngine();
    EXPECT_THROW(car.SetSpeed(20), IncreaseSpeedError);
}

TEST(CarTest, CantSetNegativeSpeed)
{
    CCar car{};
    car.TurnOnEngine();
    EXPECT_THROW(car.SetSpeed(-20), NegativeSpeedError);
}

TEST(CarTest, CannotSetInvalidGear)
{
    CCar car{};
    car.TurnOnEngine();
    EXPECT_THROW(car.SetGear(-2), GearRangeError);
    EXPECT_THROW(car.SetGear(6), GearRangeError);
    EXPECT_NO_THROW(car.SetGear(0));
    EXPECT_NO_THROW(car.SetGear(1));
}

TEST(CarTest, CannotSetInvalidSpeed)
{
    CCar car{};
    car.TurnOnEngine();
    car.SetGear(1);
    EXPECT_THROW(car.SetSpeed(31), MaxSpeedError);
    EXPECT_NO_THROW(car.SetSpeed(0));
    EXPECT_NO_THROW(car.SetSpeed(30));
}

TEST(CarTest, CanReverseIfSpeedIsZero)
{
    CCar car{};
    car.TurnOnEngine();
    car.SetGear(-1);
    EXPECT_NO_THROW(car.SetGear(1));
}

TEST(CarTest, CannotReverseIfSpeedIsNotZero)
{
    CCar car{};
    car.TurnOnEngine();
    car.SetGear(-1);
    car.SetSpeed(10);
    EXPECT_THROW(car.SetGear(1), ReverseToForwardError);
}

TEST(CarTest, CanOrNotChangeGear)
{
    CCar car{};
    car.TurnOnEngine();
    EXPECT_NO_THROW(car.SetGear(1));
    EXPECT_NO_THROW(car.SetGear(0));
    EXPECT_NO_THROW(car.SetGear(-1));
    EXPECT_THROW(car.SetGear(2), GearSpeedRangeError);
    EXPECT_THROW(car.SetGear(3), GearSpeedRangeError);
    EXPECT_THROW(car.SetGear(4), GearSpeedRangeError);
    EXPECT_THROW(car.SetGear(5), GearSpeedRangeError);
}

TEST(CarTest, CannotChangeGearIfDirectionDoesNotAllow)
{
    CCar car{};
    car.TurnOnEngine();
    EXPECT_NO_THROW(car.SetGear(-1));
    car.SetSpeed(20);
    EXPECT_NO_THROW(car.SetGear(0));
    EXPECT_THROW(car.SetGear(1), ReverseToForwardError);
}

TEST(CarTest, CannotGoBackIfNeutralAndSpeedNotZero)
{
    CCar car{};
    car.TurnOnEngine();
    EXPECT_NO_THROW(car.SetGear(1));
    car.SetSpeed(20);
    EXPECT_NO_THROW(car.SetGear(0));
    EXPECT_THROW(car.SetGear(-1), ReverseSpeedError);
}

TEST(CarTest, CanBreakOnNeutral)
{
    CCar car{};
    car.TurnOnEngine();
    EXPECT_NO_THROW(car.SetGear(1));
    car.SetSpeed(20);
    EXPECT_NO_THROW(car.SetGear(0));
    EXPECT_NO_THROW(car.SetSpeed(0));
}

TEST(CarTest, CanReverseOnZeroSpeed)
{
    CCar car{};
    car.TurnOnEngine();
    EXPECT_NO_THROW(car.SetGear(-1));
    car.SetSpeed(20);
    EXPECT_NO_THROW(car.SetGear(0));
    EXPECT_NO_THROW(car.SetSpeed(0));
    EXPECT_NO_THROW(car.SetGear(1));
}

TEST(CarTest, CarBreakChangeDirecionCheck)
{
    CCar car{};
    car.TurnOnEngine();
    car.SetGear(-1);
    car.SetSpeed(20);                              //// !!!!!!!!!!!!!!!!!!!!!!!!!
    car.SetGear(0);                                //// !!!!!!!!!!!!!!!!!!!!!!!!!
    car.SetSpeed(10);                              //// !!!!!!!!!!!!!!!!!!!!!!!!!
    EXPECT_EQ(car.GetDirection(), -1);
}

GTEST_API_ int main (int argc, char **argv)
{
    std::cout << "Running tests \n";
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}