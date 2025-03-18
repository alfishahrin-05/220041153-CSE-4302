#include <iostream>
#include <string>
using namespace std;

class Temperature 
{
private:
    double value;
    string unit;

public:
    Temperature(double v = 0, string u = "Celsius") 
    {
        assign(v, u);
    }
    void assign(double v, string u) {
        if (u != "Celsius" && u != "Fahrenheit" && u != "Kelvin") {
            cout<<"Invalid Unit"<<endl;
        }
        if ((u == "Celsius" && v < -273.15) ||
            (u == "Fahrenheit" && v < -459.67) ||
            (u == "Kelvin" && v < 0)) {
            cout<<"Temperature value cannot be lower than absolute zero temperature"<<endl;
        }
        value = v;
        unit = u;
    }
    double convert(string targetUnit) {
        if (targetUnit == unit) {
            return value;  
        }

        double tempInCelsius;
        if (unit == "Celsius") { //jekono temperature theke celsius
            tempInCelsius = value;
        } else if (unit == "Fahrenheit") {
            tempInCelsius = (value - 32) * 5 / 9;
        } else if (unit == "Kelvin") {
            tempInCelsius = value - 273.15;
        }
        if (targetUnit == "Celsius") { //celsius theke jekono temperature
            return tempInCelsius;
        } else if (targetUnit == "Fahrenheit") {
            return (tempInCelsius * 9 / 5) + 32;
        } else if (targetUnit == "Kelvin") {
            return tempInCelsius + 273.15;
        } else {
            cout<<"Invalid target"<<endl;
        }
    }
    void print() {
        cout << "The temperature is " << value << " " << unit << "." << endl;
    }
};

int main() {
    {
        Temperature temp(100, "Celsius");
        temp.print();

        double convertedToFahrenheit = temp.convert("Fahrenheit");
        cout << "Converted to Fahrenheit: " << convertedToFahrenheit << endl;

        double convertedToKelvin = temp.convert("Kelvin");
        cout << "Converted to Kelvin: " << convertedToKelvin << endl;
        temp.assign(32, "Fahrenheit");
        temp.print();
    } 
    return 0;
}
