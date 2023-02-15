#include <iostream>
#include <list>

using namespace std;

// Declare forward reference for the WeatherData class.
class WeatherData;

// Observer interface defines the update method that will be called by the subject.
class Observer
{
public:
    virtual void update(double temp, double humidity, double pressure) = 0;
};

// Display interface defines the display method that will be called by the observers.
class Display
{
public:
    virtual void display() = 0;
};

// WeatherData class represents the subject that the observers will be registered with.
class WeatherData
{
public:
    // Method for registering an observer with the subject.
    void registerObserver(Observer *o)
    {
        observers.push_back(o);
    }

    // Method for removing an observer from the subject.
    void removeObserver(Observer *o)
    {
        observers.remove(o);
    }

    // Method for notifying all registered observers of a change in the weather measurements.
    void notifyObservers()
    {
        for (auto o : observers)
        {
            o->update(temperature, humidity, pressure);
        }
    }

    // Method for setting the weather measurements and notifying the observers.
    void setMeasurements(double temperature, double humidity, double pressure)
    {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        notifyObservers();
    }

private:
    // List of registered observers.
    list<Observer *> observers;
    // Current weather measurements.
    double temperature;
    double humidity;
    double pressure;
};

// CurrentConditionsDisplay class is an observer that displays the current weather conditions.
class CurrentConditionsDisplay : public Observer, public Display
{
public:
    // Constructor that registers this observer with the given subject.
    CurrentConditionsDisplay(WeatherData *weatherData) : weatherData(weatherData)
    {
        weatherData->registerObserver(this);
    }

    // Update method called by the subject to update the weather conditions.
    void update(double temperature, double humidity, double pressure) override
    {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        display();
    }

    // Display method called to display the current weather conditions.
    void display() override
    {
        cout << "Current conditions: " << temperature << " F degrees, " << humidity << "% humidity, " << pressure << " hPa pressure" << endl;
    }

private:
    // Subject that this observer is registered with.
    WeatherData *weatherData;
    // Current weather conditions.
    double temperature;
    double humidity;
    double pressure;
};

// ForecastDisplay class is an observer that displays the weather forecast.
class ForecastDisplay : public Observer, public Display
{
public:
    // Constructor that registers this observer with the given subject.
    ForecastDisplay(WeatherData *weatherData) : weatherData(weatherData)
    {
        weatherData->registerObserver(this);
    }

    // Update method called by the subject to update the weather forecast.
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

    // Display method called to display the weather forecast.
    void display() override
    {
        cout << "Forecast: " << forecast << endl;
    }

private:
    // Subject that this observer is registered with.
    WeatherData *weatherData;
    // Current weather forecast.
    string forecast = "Stable";
};

// A class to demonstrate the WeatherData, CurrentConditionsDisplay and ForecastDisplay classes.
class WeatherStation
{
public:
    // The main function that runs the weather station simulation.
    void main()
    {
        // Create a new WeatherData object.
        WeatherData weatherData;

        // Create a new CurrentConditionsDisplay object and register it as an observer of the WeatherData object.
        CurrentConditionsDisplay currentDisplay(&weatherData);

        // Create a new ForecastDisplay object and register it as an observer of the WeatherData object.
        ForecastDisplay forecastDisplay(&weatherData);

        // simulate new weather measurements and notify observers.
        weatherData.setMeasurements(80, 65, 1020);
        weatherData.setMeasurements(82, 70, 1015);
        weatherData.setMeasurements(78, 90, 1005);

        // Remove the CurrentConditionsDisplay object as an observer of the WeatherData object.
        weatherData.removeObserver(&currentDisplay);

        // Simulate new weather measurements and notify observers (minus the CurrentConditionsDisplay observer).
        weatherData.setMeasurements(75, 50, 1012);
    }
};

// The main function that runs the weather station application.
int main()
{
    // Print a message to indicate the start of the application.
    cout << "WeatherStation App" << endl;

    // Create a new WeatherStation object and run the main function.
    WeatherStation weatherStation;
    weatherStation.main();

    // Indicate successful completion of the application.
    return 0;
}
