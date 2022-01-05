#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h> 

using namespace std;

string random_names[12] = { "James", "Robert", "Sarah", "Oliver", "Emily", "Kevin", "Stephanie", "Anna", "Sebastian", "Emma", "George", "Chloe"};
string random_surnames[14] = { "Smith", "Johnson", "Williams", "Brown", "Jones", "Russell", "Davis", "Wilson", "Anderson", "Taylor", "Moore", "Jackson", "Thompson", "Clark" };

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
    int i, rand1, rand2;

    int n_part = 108;
    int n_cont = 99;
    int n_work = 9;

    Contestant contestants[99];
    
    srand(time(NULL));
    for (i = 0; i < 99; i++)
    {
        rand1 = rand() % 12;
        contestants[i].name = random_names[rand1];
        rand2 = rand() % 14;
        contestants[i].surname = random_surnames[rand2];
        contestants[i].number = i + 1;
    }



    for (i = 0; i < 99; i++)
    {
        cout << contestants[i].name << " " << contestants[i].surname << " " << contestants[i].number << endl;
    }

}
