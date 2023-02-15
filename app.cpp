#include <iostream>
#include <list>

class Observer
{
public:
};

class Display
{
public:
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