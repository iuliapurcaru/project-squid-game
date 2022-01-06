#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h> 
#include <algorithm>
#include <iterator>

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
    int shuffle[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

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

    Worker workers[9];

    string random_masks[9] = { "square", "square", "square", "cirlce", "cirlce", "cirlce", "triangle", "triangle", "triangle" };
    random_shuffle(begin(random_masks), end(random_masks));

    for (i = 0; i < 9; i++)
    {
        workers[i].mask = random_masks[i];

        random = rand() % 15;
        workers[i].name = random_names[random];

        random = rand() % 15;
        workers[i].surname = random_surnames[random];

        random = rand() % 10;
        workers[i].city = random_cities[random];

        workers[i].debt = rand() % 100000 + 10000;
        workers[i].weight = rand() % 50 + 50;
    }

    cout << "\t\t--WORKERS--" << endl;
    cout << "Mask\tName\tSurname\tCity\tDebt\tWeight" << endl;

    for (i = 0; i < 9; i++)
    {
        cout << workers[i].mask << " " << workers[i].name << "\t" << workers[i].surname << "\t" << workers[i].city << "\t$" << workers[i].debt << "\t" << workers[i].weight << "kg " << endl;
    }

    cout << "--------------------------------------------" << endl;

}
