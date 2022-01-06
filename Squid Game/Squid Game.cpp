#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h> 
#include <algorithm>
#include <iterator>
#include <conio.h>

using namespace std;

string random_names[15] = { "Julia", "Sam", "James", "Robert", "Sarah", "Oliver", "Emily", "Kevin", "Sophie", "Anna", "Noah", "Emma", "George", "Chloe", "Lewis" };
string random_surnames[15] = { "Hill", "Smith", "Johnson", "William", "Brown", "Jones", "Russell", "Davis", "Wilson", "Watson", "Taylor", "Moore", "Jackson", "Miller", "Clark" };
string random_cities[10] = { "Berlin", "Rome", "Athens", "Paris", "Vienna", "London", "Dublin", "Madrid", "Oslo", "Prague" };

int random_contestants[99] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
		11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
		21, 22, 23, 24, 25,26, 27, 28, 29, 30,
		31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
		51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
		61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
		71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
		81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
		91, 92, 93, 94, 95, 96, 97, 98, 99 };

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
private:
	int team[11];

public:
	string mask;

	void setTeam(int j)
	{
		int i = 0;
		int jmax = j + 11;

		for ( ; j < jmax; j++)
		{
			this->team[i] = random_contestants[j];
			i++;
		}
	}

	int getTeam(int j)
	{
		return team[j];
	}

};

int main()
{
	int i, j;
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

	string random_masks[9] = { "square", "square", "square", "circle", "circle", "circle", "triangle", "triangle", "triangle" };
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

	random_shuffle(begin(random_contestants), end(random_contestants));

	cout << "--Workers and their contestants--\n";

	j = 0;
	for (i = 0; i < 9; i++)
	{
		workers[i].setTeam(j);
		j += 11;
	}

	for(i = 0; i < 9; i++)
	{
		cout << "Worker " << i + 1 << ": ";
		for (j = 0; j < 11; j++)
		{
			cout << workers[i].getTeam(j) << " ";
		}
		cout << endl;
	}

	cout << "--------------------------------------------" << endl;

	cout << "Press any key to continue . . .";
	getchar();

	cout << endl;
	cout << "The first game is Red Light, Green Light";

}