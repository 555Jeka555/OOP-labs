#include "commandHandler.h"

const std::string STOP_ENTER = "...";
const std::string INFO_COMMAND = "Info";
const std::string ENGINE_ON_COMMAND = "EngineOn";
const std::string ENGINE_OFF_COMMAND = "EngineOff";
const std::string SET_GEAR_COMMAND = "SetGear";
const std::string SET_SPEED_COMMAND = "SetSpeed";

void HandlerInfo(const Car& car)
{
    std::cout << "INFO" << std::endl;
    std::cout << "Gear: " << car.GetGear() << std::endl;
    std::cout << "Speed: " << car.GetSpeed() << std::endl;
    if (car.IsTurnedOn())
    {
        std::cout << "Turn: On" << std::endl;
    }
    else
    {
        std::cout << "Turn: Off" << std::endl;
    }
    std::cout << "Direction: " << car.GetDirection() << std::endl;
}

void HandlerEngineOn(Car& car)
{
    bool isTurnOnEngine = car.TurnOnEngine();
    if (isTurnOnEngine)
    {
        std::cout << "Turn on engine success" << std::endl;
    }
    else
    {
        std::cerr << "Turn on engine error" << std::endl;
    }
}

void HandlerEngineOff(Car& car)
{
    bool isTurnOffEngine = car.TurnOffEngine();
    if (isTurnOffEngine)
    {
        std::cout << "Turn off engine success" << std::endl;
    }
    else
    {
        std::cerr << "Turn off engine error" << std::endl;
    }
}

void HandlerSetGear(Car& car)
{
    std::string argument;

    std::cout << "Enter gear" << std::endl;
    std::cin >> argument;

    int gear;
    try
    {
        gear = std::stoi(argument);
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Invalid input" << std::endl;
        return;
    }

    bool isSetGear = car.SetGear(gear);
    if (isSetGear)
    {
        std::cout << "Set gear success on " << gear << std::endl;
    }
    else
    {
        std::cerr << "Set gear error" << std::endl;
    }
}

void HandlerSetSpeed(Car& car)
{
    std::string argument;

    std::cout << "Enter speed" << std::endl;
    std::cin >> argument;

    int speed;
    try
    {
        speed = std::stoi(argument);
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Invalid input" << std::endl;
        return;
    }

    bool isSetSpeed = car.SetSpeed(speed);
    if (isSetSpeed)
    {
        std::cout << "Set speed success on " << speed << std::endl;
    }
    else
    {
        std::cerr << "Set speed error" << std::endl;
    }
}

void CommandHandler()
{
    Car car;
    while (true)
    {
        std::string command;
        std::cin >> command;

        if (command == STOP_ENTER)
        {
            std::cout << "Bye" << std::endl;
            break;
        }
        else if (command == INFO_COMMAND)
        {
            HandlerInfo(car);
        }
        else if (command == ENGINE_ON_COMMAND)
        {
            HandlerEngineOn(car);
        }
        else if (command == ENGINE_OFF_COMMAND)
        {
            HandlerEngineOff(car);
        }
        else if (command == SET_GEAR_COMMAND)
        {
            HandlerSetGear(car);
        }
        else if (command == SET_SPEED_COMMAND)
        {
            HandlerSetSpeed(car);
        }
        else
        {
            std::cout << "Unknown command" << std::endl;
        }
    }
}
