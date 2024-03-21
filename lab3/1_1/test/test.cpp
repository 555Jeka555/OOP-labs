#include <gtest/gtest.h>
#include "../src/Car.h"

TEST (car, turn_on_car_success)
{
    Car car;
    EXPECT_EQ(false, car.IsTurnedOn());
    car.TurnOnEngine();
    EXPECT_EQ(true, car.IsTurnedOn());

    car.TurnOnEngine();
    EXPECT_EQ(true, car.IsTurnedOn());
}

TEST (car, turn_off_car_success)
{
    Car car;
    EXPECT_EQ(false, car.IsTurnedOn());

    car.TurnOnEngine();
    EXPECT_EQ(true, car.IsTurnedOn());

    car.TurnOffEngine();
    EXPECT_EQ(false, car.IsTurnedOn());

    car.TurnOffEngine();
    EXPECT_EQ(false, car.IsTurnedOn());
}

TEST (car, valid_gear_error) {
    Car car;
    car.TurnOnEngine();

    int gear = -2;
    int expectedGear = 0;
    EXPECT_EQ(false, car.SetGear(gear));
    EXPECT_EQ(expectedGear, car.GetGear());

    gear = 6;
    expectedGear = 0;
    EXPECT_EQ(false, car.SetGear(gear));
    EXPECT_EQ(expectedGear, car.GetGear());
}

TEST (car, up_gear_success)
{
    Car car;
    car.TurnOnEngine();

    int gear = -1;
    int speed = 20;
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(gear, car.GetGear());
    EXPECT_EQ(true, car.SetSpeed(speed));

    speed = 0;
    gear = 0;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(gear, car.GetGear());

    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(gear, car.GetGear());

    speed = 20;
    gear = 1;
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(gear, car.GetGear());

    gear = 2;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(gear, car.GetGear());

    speed = 50;
    gear = 3;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(gear, car.GetGear());

    speed = 40;
    gear = 4;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(gear, car.GetGear());

    speed = 90;
    gear = 5;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(gear, car.GetGear());

    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(gear, car.GetGear());
}

TEST (car, up_gear_error)
{
    Car car;

    int gear = 1;
    int expectedGear = 0;
    EXPECT_EQ(false, car.SetGear(gear));
    EXPECT_EQ(expectedGear, car.GetGear());

    car.TurnOnEngine();

    int speed = 10;
    gear = 1;
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(true, car.SetSpeed(speed));
    gear = 2;
    expectedGear = 1;
    EXPECT_EQ(false, car.SetGear(gear));
    EXPECT_EQ(expectedGear, car.GetGear());

}

TEST (car, down_gear_success)
{
    Car car;
    car.TurnOnEngine();

    int gear = 1;
    int speed = 20;
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(true, car.SetSpeed(speed));

    gear = 2;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(true, car.SetGear(gear));

    speed = 50;
    gear = 3;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(true, car.SetGear(gear));

    speed = 40;
    gear = 4;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(true, car.SetGear(gear));

    speed = 90;
    gear = 5;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(true, car.SetGear(gear));

    speed = 90;
    gear = 4;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(gear, car.GetGear());

    speed = 50;
    gear = 3;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(gear, car.GetGear());

    gear = 2;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(gear, car.GetGear());

    speed = 20;
    gear = 1;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(gear, car.GetGear());

    speed = 0;
    gear = 0;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(gear, car.GetGear());

    gear = -1;
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(gear, car.GetGear());
}

TEST (car, down_gear_error)
{
    Car car;
    int gear = -1;
    int expectedGear = 0;
    EXPECT_EQ(false, car.SetGear(gear));
    EXPECT_EQ(expectedGear, car.GetGear());

    car.TurnOnEngine();

    gear = 1;
    int speed = 20;
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(true, car.SetSpeed(speed));

    gear = 2;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(true, car.SetGear(gear));

    speed = 50;
    gear = 1;
    expectedGear = 2;
    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(false, car.SetGear(gear));
    EXPECT_EQ(expectedGear, car.GetGear());
}

TEST (car, up_speed_car_error) {
    Car car;

    int speed = 10;
    int expectedSpeed = 0;
    EXPECT_EQ(false, car.SetSpeed(speed));
    EXPECT_EQ(expectedSpeed, car.GetSpeed());

    car.TurnOnEngine();

    speed = 5;
    expectedSpeed = 0;
    EXPECT_EQ(false, car.SetSpeed(speed));
    EXPECT_EQ(expectedSpeed, car.GetSpeed());

    int gear = 1;
    speed = 31;
    expectedSpeed = 0;
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(false, car.SetSpeed(speed));
    EXPECT_EQ(expectedSpeed, car.GetSpeed());
}

TEST (car, backward_gear_car_error) {
    Car car;
    car.TurnOnEngine();

    int gear = -1;
    int speed = 10;
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(true, car.SetSpeed(speed));
    gear = 0;
    EXPECT_EQ(true, car.SetGear(gear));
    gear = -1;
    int expectedGear = 0;
    EXPECT_EQ(false, car.SetGear(gear));
    EXPECT_EQ(expectedGear, car.GetGear());

    speed = 0;
    EXPECT_EQ(true, car.SetSpeed(speed));
    gear = -1;
    speed = 10;
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(true, car.SetSpeed(speed));
    gear = 1;
    expectedGear = -1;
    EXPECT_EQ(false, car.SetGear(gear));
    EXPECT_EQ(expectedGear, car.GetGear());

    gear = 0;
    speed = 0;
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(true, car.SetSpeed(speed));
    gear = -1;
    speed = 10;
    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(true, car.SetSpeed(speed));
    gear = 0;
    EXPECT_EQ(true, car.SetGear(gear));
    gear = 1;

    expectedGear = 0;
    EXPECT_EQ(false, car.SetGear(gear));
    EXPECT_EQ(expectedGear, car.GetGear());
}

TEST (car, turn_off_car_error)
{
    Car car;
    int gear = 1;
    int speed = 5;
    EXPECT_EQ(false, car.IsTurnedOn());

    car.TurnOnEngine();
    EXPECT_EQ(true, car.IsTurnedOn());

    EXPECT_EQ(true, car.SetGear(gear));
    EXPECT_EQ(gear, car.GetGear());

    EXPECT_EQ(true, car.SetSpeed(speed));
    EXPECT_EQ(speed, car.GetSpeed());

    EXPECT_EQ(false, car.TurnOffEngine());
    EXPECT_EQ(true, car.IsTurnedOn());
}

GTEST_API_ int main (int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}