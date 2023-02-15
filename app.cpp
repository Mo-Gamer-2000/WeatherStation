#include <iostream>
#include <list>

class Observer
{
public:
    virtual void update(double temp, double humidity, double pressure) = 0;
};

class Display
{
public:
    virtual void display() = 0;
};

class WeatherData
{
public:
private:
};

class CurrentConditionDisplay : public Observer, public Display
{
public:
private:
};

class DorecastDisplay : public Observer, public Display
{
public:
private:
};

class WeatherStation
{
public:
};

int main()
{
    std::cout << "WeatherStation" << std::endl;
    return 0;
};