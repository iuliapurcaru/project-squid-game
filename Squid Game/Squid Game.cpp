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

int random_numbers[99] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
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

	void setData();

	void printData()
	{}
};

void Participant::setData()
{
	int random;

	random = rand() % 15;
	name = random_names[random];

	random = rand() % 15;
	surname = random_surnames[random];

	random = rand() % 10;
	city = random_cities[random];

	debt = rand() % 100000 + 10000;
	weight = rand() % 50 + 50;
}

class Contestant : public Participant
{
public:
	int number;

	Contestant() {}
	Contestant(const Contestant& c1);
	~Contestant() {}

	void setNumber(int n)
	{
		number = n;
	}

	void printData()
	{
		cout << number << "\t" << name << "\t" << surname << "\t" << city << "\t$" << debt << "\t" << weight << "kg " << endl;
	}
};

Contestant::Contestant(const Contestant& c1)
{
	name = c1.name;
	surname = c1.surname;
	city = c1.city;
	debt = c1.debt;
	weight = c1.weight;
}

//Contestant::~Contestant()
//{
//	delete& name;
//	delete& surname;
//	delete& city;
//	delete& debt;
//	delete& weight;
//}

class Guard : public Participant
{
private:
	int team[11];

public:
	string mask;

	Guard() {}
	~Guard() {}

	void setTeam(int j)
	{
		int i = 0;
		int jmax = j + 11;

		for (; j < jmax; j++)
		{
			this->team[i] = random_numbers[j];
			i++;
		}
	}

	int getTeam(int j)
	{
		return this->team[j];
	}

	void printData()
	{
		cout << mask << " " << name << "\t" << surname << "\t" << city << "\t$" << debt << endl;
	}

};

int main()
{
	int i, j, aux;
	int n_remaining = 0;

	srand((unsigned int)time(NULL));

	Contestant contestants[99];

	cout << "\t\t--CONTESTANTS--" << endl;
	cout << "Number\tName\tSurname\tCity\tDebt\tWeight" << endl;

	for (i = 0; i < 99; i++)
	{
		contestants[i].setNumber(i + 1);
		contestants[i].Participant::setData();
		contestants[i].printData();
	}

	Contestant remaining_contestants[99];
	for (i = 0; i < 99; i++)
	{
		n_remaining++;
		remaining_contestants[i] = contestants[i];
	}

	cout << "--------------------------------------------" << endl;

	Guard guards[9];

	cout << "\t\t--GUARDS--" << endl;
	cout << "Mask\tName\tSurname\tCity\tDebt" << endl;

	string random_masks[9] = { "square", "square", "square", "circle", "circle", "circle", "triangle", "triangle", "triangle" };
	random_shuffle(begin(random_masks), end(random_masks));

	for (i = 0; i < 9; i++)
	{
		guards[i].mask = random_masks[i];
		guards[i].Participant::setData();
		guards[i].printData();
	}

	cout << "--------------------------------------------" << endl;

	random_shuffle(begin(random_numbers), end(random_numbers));

	cout << "--Guards and the contestants they supervise--\n";

	j = 0;
	for (i = 0; i < 9; i++)
	{
		guards[i].setTeam(j);
		j += 11;
	}

	for (i = 0; i < 9; i++)
	{
		cout << "Guard " << i + 1 << ": ";
		for (j = 0; j < 11; j++)
		{
			cout << guards[i].getTeam(j) << " ";
		}
		cout << endl;
	}

	cout << "--------------------------------------------" << endl;

	cout << "Press enter to continue . . .";
	cin.get();

	//RED LIGHT GREEN LIGHT

	cout << endl;
	cout << "The first game is Red Light, Green Light" << endl;
	cin.get();

	aux = 0;
	for (i = 0; i < n_remaining; i++)
	{
		if (remaining_contestants[i].number % 2)
		{
			aux++;
			remaining_contestants[i].printData();
		}
	}

	n_remaining = aux;

}