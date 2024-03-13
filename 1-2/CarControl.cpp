#include <limits>
#include <optional>
#include "Car.h"

enum class Command {
    Info,
    Help,
    EngineOn,
    EngineOff,
    SetGear,
    SetSpeed,
    Default
};
////                                                                        done none command crash
////                                                                        done change direction error

Command StrToCommand(const std::string& str) {
    if (str == "Info") {
        return Command::Info;
    } else if (str == "help") {
        return Command::Help;
    } else if (str == "EngineOn") {
        return Command::EngineOn;
    } else if (str == "EngineOff") {
        return Command::EngineOff;
    } else if (str == "SetGear") {
        return Command::SetGear;
    } else if (str == "SetSpeed") {
        return Command::SetSpeed;
    } else {
        return Command::Default;
    }
}

void PrintInfo(const CCar& car)
{
    std::cout << "Engine: " << (car.IsTurnedOn() ? "on" : "off") << std::endl;
    std::cout << "Direction: " << car.GetDirection() << std::endl;
    std::cout << "Speed: " << car.GetSpeed() << std::endl;
    std::cout << "Gear: " << car.GetGear() << std::endl;
}

void PrintListOfCommands()
{
    std::cout << "Available commands:" << std::endl;
    std::cout << "Info             - display current car state" << std::endl;
    std::cout << "EngineOn         - turn on the engine" << std::endl;
    std::cout << "EngineOff        - turn off the engine" << std::endl;
    std::cout << "SetGear [gear]   - set the gear to the specified value (-1 to 5)" << std::endl;
    std::cout << "SetSpeed [speed] - set the speed to the specified value" << std::endl;
}

std::optional<int> GetInteger()
{
    int num;
    std::cin >> num;
    if (std::cin.fail())
    {
        std::cout << "Invalid input. Please enter integer number in function parameter." << std::endl;
        std::cin.clear(); // clear the error flag on cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any remaining input on the line
        return std::nullopt;
    }
    return num;
}

void CommandSetGear(CCar& car, int gear)
{
    try {
        car.SetGear(gear);
        std::cout << "Gear " << gear << " set successfully." << std::endl;
    }catch (const EngineOffError& e) {
        std::cerr << "Error: Engine is off, cannot change gear." << std::endl;
    } catch (const GearRangeError& e) {
        std::cerr << "Error: Gear is not in the range of -1 to 5." << std::endl;
    } catch (const GearSpeedRangeError& e) {
        std::cerr << "Error: New gear cannot handle current speed." << std::endl;
    } catch (const ReverseToForwardError& e) {
        std::cerr << "Error: Cannot change from reverse to forward while moving backwards." << std::endl;
    } catch (const ReverseSpeedError& e) {
        std::cerr << "Error: Cannot switch to reverse gear while moving" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unknown error " << std::endl;
    }
}

void CommandSetSpeed(CCar& car, int speed)
{
    try {
        car.SetSpeed(speed);
        std::cout << "Speed " << speed << " set successfully." << std::endl;
    } catch (const EngineOffError& e) {
        std::cerr << "Error: Engine is off, cannot change speed" << std::endl;
    } catch (const IncreaseSpeedError& e) {
        std::cerr << "Error: Cannot increase speed while in neutral." << std::endl;
    } catch (const MaxSpeedError& e) {
        std::cerr << "Error: Cannot exceed max speed for current gear." << std::endl;
    } catch (const NegativeSpeedError& e) {
        std::cerr << "Error: Speed cannot be negative." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unknown error " << std::endl;
    }
}

void HandleCommand(CCar& car, const std::string& command) {
    switch (StrToCommand(command)) {
        case Command::Info:
            PrintInfo(car);
            break;
        case Command::Help:
            PrintListOfCommands();
            break;
        case Command::EngineOn:
            if (!car.TurnOnEngine())
                std::cerr << "Failed to turn on engine" << std::endl;
            else
                std::cout << "Engine turned on! Lets ride!" << std::endl;
            break;
        case Command::EngineOff:
            if (!car.TurnOffEngine())
                std::cerr << "Failed to turn off engine" << std::endl;
            else
                std::cout << "Successfully stopped the engine." << std::endl;
            break;
        case Command::SetGear: {
            std::optional<int> gear = GetInteger();
            if (gear.has_value()) CommandSetGear(car, gear.value());
            break;
        }
        case Command::SetSpeed: {
            std::optional<int> speed = GetInteger();
            if (speed.has_value()) CommandSetSpeed(car, speed.value());
            break;
        }
        case Command::Default: {
            std::cout << "Unknown command: " << command << std::endl;
            PrintListOfCommands();
            break;
        }
    }
}

void CommandProcessor(CCar &car)
{
    PrintListOfCommands();
    std::string command;
    while (std::cin >> command)
    {
        HandleCommand(car, command);
    }
}

int main()
{
    CCar car{}; // создаем объект класса Car

    CommandProcessor(car);
    return 0;
}










