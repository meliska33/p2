#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <future>
#include <thread>

class stos {
private:
    std::stack<double> bagaznik;
    int capacity;
    double occupied;
public:

    stos() {
        occupied = 0.0;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> cap(5, 16);
        capacity = cap(gen);
        std::cout << "New car added" << std::endl << std::endl;
    }

    bool addElement(double element) {
        if (occupied + element > capacity) {
            return false;
        }
        bagaznik.push(element);
        occupied += element;
        return true;
    }

    int getCapacity() {
        return capacity;
    }
    double getOccupied() {
        return occupied;
    }
};



double randomWeight() {
    double package = 0.0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weight1(1, 7);

    package += weight1(gen);

    std::uniform_int_distribution<> weight2(0, 9);

    package += (weight2(gen) / 10.);

    return package;

}


void generateBelt(std::promise<std::queue<double>> belt, int amount) {

    std::queue<double> tasmociag;
    for (int i = 0; i < amount; i++) {
        double weight = randomWeight();
        tasmociag.push(weight);
    }

    belt.set_value(std::move(tasmociag));
}

int main()
{
    int amount;
    std::cout << "Insert amount of packages: "; std::cin >> amount;
    std::cout << std::endl;

    std::promise<std::queue<double>> promise;
    std::future<std::queue<double>> future = promise.get_future();



    std::async(std::launch::async, generateBelt, std::move(promise), amount);
    std::cout << "Generating conveyor belt..." << std::endl;

    std::queue<double> packages = future.get();

    std::cout << "Conveyor belt generated. Packing can be started." << std::endl;

    std::vector<stos> parking;
    stos car;
    parking.push_back(car);

    for (int i = 0; i < amount; i++) {

        double liczba = packages.front();

        bool success = false;

        std::cout << "Weight of the new package: " << liczba << " " << std::endl;

        for (stos& j : parking) {
            if (j.addElement(liczba)) { //dodanie elementu zakończone true
                std::cout << "The capacity of the car: " << j.getCapacity() << std::endl;
                std::cout << "How much space is already occupied: " << j.getOccupied() << std::endl;
                std::cout << std::endl;
                success = true;
                break;
            }
            else { //dodanie elementu zakończone false
                continue;
            }
        }

        if (!success) {
            stos newCar;
            newCar.addElement(liczba);
            parking.push_back(newCar);
            std::cout << "The capacity of the car: " << newCar.getCapacity() << std::endl;
            std::cout << "How much space is already occupied: " << newCar.getOccupied() << std::endl;
        }

        packages.pop();
    }

    return 0;
}
