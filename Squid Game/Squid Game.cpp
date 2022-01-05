#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h> 

using namespace std;

string random_names[15] = {"Julia", "Michael", "James", "Robert", "Sarah", "Oliver", "Emily", "Kevin", "Sophie", "Anna", "Noah", "Emma", "George", "Chloe", "Lewis"};
string random_surnames[15] = { "Hill", "Smith", "Johnson", "William", "Brown", "Jones", "Russell", "Davis", "Wilson", "Watson", "Taylor", "Moore", "Jackson", "Miller", "Clark" };
string random_cities[10] = { "Berlin", "Rome", "Athens", "Paris", "Vienna", "London", "Dublin", "Madrid", "Oslo", "Prague" };

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
    int i;
    int random;

    int n_part = 108;
    int n_cont = 99;
    int n_work = 9;

    Contestant contestants[99];
    
    srand(time(NULL));
    for (i = 0; i < 99; i++)
    {
        contestants[i].number = i + 1;

        random = rand() % 15;
        contestants[i].name = random_names[random];

        random = rand() % 15;
        contestants[i].surname = random_surnames[random];

        random = rand() % 10;
        contestants[i].city = random_cities[random];

        contestants[i].debt = rand() % 100000 + 10000;
        contestants[i].weight = rand() % 50 + 50;
    }

    cout << "\t\t--CONTESTANTS--" << endl;
    cout << "Number\tName\tSurname\tCity\tDebt\tWeight" << endl;

    for (i = 0; i < 99; i++)
    {
        cout << contestants[i].number << "\t" << contestants[i].name << "\t" << contestants[i].surname << "\t" << contestants[i].city << "\t$" << contestants[i].debt << "\t" << contestants[i].weight << "kg " << endl;
    }

    cout << "--------------------------------------------" << endl;

}
