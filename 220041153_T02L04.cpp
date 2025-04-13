#include <iostream>
#include <string>
using namespace std;

class Flight_Information
{
    private:
        int flight_number;
        string destination;
        float distance;
        float max_fuel_capacity;
        double CalFuel()
        {
            if(distance<=100)
            {
                return 500;
            }
            else if(distance>1000 && distance<=2000)
            {
                return 1100;
            }
            else if(distance>2000)
            {
                return 2200;
            }
        }
    public:
        void FeedInfo()
        {
            cout<<"Provide the Flight Number: ";
            cin>>flight_number;
            cout<<"Provide your destination place: ";
            cin>>destination;
            cout<<"Provide the distance: ";
            cin>>distance;
            cout << "Provide the Max Fuel Capacity of the flight: ";
            cin>>max_fuel_capacity;
        }
        void ShowInfo() 
        {
            cout << "\nFlight Number: " << flight_number << endl;
            cout << "Destination: " << destination << endl;
            cout << "Distance: " << distance << " km" << endl;
            cout << "Max Fuel Capacity of the flight: " << max_fuel_capacity << " liters" << endl;

        double requiredFuel = CalFuel();
        cout << "Required Fuel: " << requiredFuel << " liters" << endl;

        if (max_fuel_capacity >= requiredFuel)
            cout << "Fuel capacity is sufficient for travelling this flight distance.\n";
        else
            cout << "Fuel capaciry is not sufficient for travelling this flight distance.\n";
        }
};

int main() 
{
    Flight_Information flight;
    flight.FeedInfo();
    flight.ShowInfo();
    return 0;
}