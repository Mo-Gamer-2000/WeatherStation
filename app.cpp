#include <iostream>
#include <list>

using namespace std;

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
    void registerObserver(Observer *o)
    {
        observers.push_back(0);
    }

    void removeObserver(Observer *o)
    {
        observers.remove(o);
    }

    void notifyObservers()
    {
        for (auto o : observers)
        {
            /* code */
            o->update(temperature, humidity, pressure);
        }
    }

    void setMeasurements(double temperature, double humidity, double pressure)
    {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        notifyObservers();
    }

private:
    list<Observer *> observers;
    double temperature;
    double humidity;
    double pressure;
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