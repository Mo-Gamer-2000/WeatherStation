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
    CurrentConditionDisplay(WeatherData *weatherData) : weatherData(weatherData)
    {
        weatherData->registerObserver(this);
    }

    void update(double temperature, double humidity, double pressure) override
    {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        display();
    }

    void display() override
    {
        cout << "Current conditions: " << temperature << "F degrees, " << humidity << "% humidity, " << pressure << "hPa pressure" << endl;
    }

private:
    WeatherData *weatherData;
    double temperature;
    double humidity;
    double pressure;
};

class ForecastDisplay : public Observer, public Display
{
public:
    ForecastDisplay(WeatherData *weatherData) : weatherData(weatherData)
    {
        weatherData->registerObserver(this);
    }

    void update(double temperature, double humidity, double pressure) override
    {
        if (pressure < 1000)
        {
            forecast = "Rainy";
        }
        else if (pressure < 1020)
        {
            forecast = "Cloudy";
        }
        else
        {
            forecast = "Sunny";
        }
        display();
    }

    void display() override
    {
        cout << "Forecast" << forecast << endl;
    }

private:
    WeatherData *weatherData;
    string forecast = "Stable";
};

class WeatherStation
{
public:
    void main()
    {
        WeatherData weatherData;
        CurrentConditionDisplay currentDisplay(&weatherData);
        ForecastDisplay ForecastDisplay(&weatherData);

        weatherData.setMeasurements(80, 65, 1020);
        weatherData.setMeasurements(82, 70, 1015);
        weatherData.setMeasurements(78, 90, 1005);

        weatherData.removeObserver(&currentDisplay);

        weatherData.setMeasurements(75, 50, 1012);
    }
};

int main()
{
    WeatherStation weatherStation;
    weatherStation.main();
    return 0;
};