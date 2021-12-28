#include <iostream>
#include <string>

using namespace std;

class Participant
{
public:
    string surname;
    string name;
    string city;
    int debt;
    int weight;
};

class Contestant : public Participant
{
public:
    int number;
};

class Worker : public Participant
{
public:
    string mask;
};

int main()
{
    cout << "Hello World!\n";
}
