#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h> 
#include <algorithm>
#include <iterator>
#include <conio.h>

using namespace std;

// names and cities for random generator
string random_names[15] = { "Julia", "Sam", "James", "Robert", "Sarah", "Oliver", "Emily", "Kevin", "Sophie", "Anna", "Noah", "Emma", "George", "Chloe", "Lewis" };
string random_surnames[15] = { "Hill", "Smith", "Johnson", "William", "Brown", "Jones", "Russell", "Davis", "Wilson", "Watson", "Taylor", "Moore", "Jackson", "Miller", "Clark" };
string random_cities[10] = { "Berlin", "Rome", "Athens", "Paris", "Vienna", "London", "Dublin", "Madrid", "Oslo", "Prague" };

// numbers for random generator
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

	void printData() {}
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
	int group[11];

public:
	string mask;

	Guard() {}
	~Guard() {}

	void setGroup(int j)
	{
		int i = 0;
		int jmax = j + 11;

		for (; j < jmax; j++)
		{
			this->group[i] = random_numbers[j];
			i++;
		}
	}

	int getGroup(int j)
	{
		return this->group[j];
	}

	void printData()
	{
		cout << mask << " " << name << "\t" << surname << "\t" << city << "\t$" << debt << endl;
	}

};

class TugOfWar
{
public:

	TugOfWar() {}
	~TugOfWar() {}

	int members[15];
	int total_weight;

};

void eliminate_contestants(Contestant remaining_contestants[], int *n_remaining, int i)
{
	int j;

	for (j = i; j < *n_remaining - 1; j++)
	{
		remaining_contestants[j] = remaining_contestants[j + 1];
	}
	(*n_remaining)--;
}

template <typename X>
X maxNum(X a, X b)
{
	if (a > b)
		return a;
	else return b;
}

void bubbleSort(int arr[], int n)
{
	int i, j, aux;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
			{
				aux = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = aux;
			}
}

int main()
{
	int i, j, k, aux;

	int n_contestants = 99;	// number of remaining contestants; always stays the same
	int n_guards = 9;	//number of guards; always stays the same
	int n_remaining = 0;	// number of remaining contestants; will be modified 

	srand((unsigned int)time(NULL));


	// GETTING READY

	// setting data for contestants

	Contestant contestants[99]; // contestants array will NOT be modified

	cout << "\t\t--CONTESTANTS--" << endl;
	cout << "Number\tName\tSurname\tCity\tDebt\tWeight" << endl;
	cout << "--------------------------------------------" << endl;

	for (i = 0; i < n_contestants; i++)
	{
		contestants[i].setNumber(i + 1);
		contestants[i].Participant::setData();
		contestants[i].printData();
	}

	// creating array for remaining contestants (copying the contestants array into a separate one)

	Contestant remaining_contestants[99];	// remaining_contestants array will be modified when contestants are eliminated
											// the last member of this array will be the winner
	for (i = 0; i < n_contestants; i++)
	{
		remaining_contestants[i] = contestants[i];
	}

	n_remaining = n_contestants;

	cout << "--------------------------------------------" << endl << endl;


	// setting data for guards

	Guard guards[9];

	cout << "\t\t--GUARDS--" << endl;
	cout << "Mask\tName\tSurname\tCity\tDebt" << endl;
	cout << "--------------------------------------------" << endl;

	string random_masks[9] = { "square", "square", "square", "circle", "circle", "circle", "triangle", "triangle", "triangle" };
	random_shuffle(begin(random_masks), end(random_masks));

	for (i = 0; i < n_guards; i++)
	{
		guards[i].mask = random_masks[i];
		guards[i].Participant::setData();
		guards[i].printData();
	}

	cout << "--------------------------------------------" << endl << endl;


	// splitting contestants into groups - each guard will have 11 contestants

	cout << "--Guards and the contestants they will supervise--\n";

	random_shuffle(begin(random_numbers), end(random_numbers)); // random number generator

	j = 0;
	for (i = 0; i < 9; i++)
	{
		guards[i].setGroup(j);
		j += 11;
	}

	for (i = 0; i < 9; i++)
	{
		cout << "Guard " << i + 1 << ": ";
		for (j = 0; j < 11; j++)
		{
			cout << guards[i].getGroup(j) << " ";
		}
		cout << endl;
	}

	cout << "--------------------------------------------" << endl << endl;

	cout << "Press enter to continue . . .";
	cin.get();

	cout << "--------------------------------------------" << endl << endl;

	// Let the games begin!
	// 
	// 1. RED LIGHT GREEN LIGHT

	cout << "The first game is RED LIGHT GREEN LIGHT." << endl << endl;
	cout << "Press enter to continue . . .";
	cin.get();

	// eliminating contestants

	aux = 0;
	for (i = 0; i < n_remaining; i++)
	{
		if (remaining_contestants[i].number % 2 == 0)
		{
			eliminate_contestants(remaining_contestants, &n_remaining, i);
		}
	}

	cout << "\t --REMAINING CONTESTANTS--" << endl;
	for (i = 0; i < n_remaining; i++)
	{
		remaining_contestants[i].printData();
	}

	cout << "--------------------------------------------" << endl << endl;

	cout << "Press enter to continue . . .";
	cin.get();

	cout << "--------------------------------------------" << endl << endl;


	// 2. TUG OF WAR

	cout << "The second game is TUG OF WAR." << endl;
	cout << "The contestants will be split into 4 groups." << endl << endl;
	cout << "Press enter to continue . . .";
	cin.get();

	cout << endl;

	int remaining_index[50];

	for (i = 0; i < n_remaining; i++)
	{
		remaining_index[i] = i;
	}

	random_shuffle(begin(remaining_index), end(remaining_index));

	TugOfWar team[4];

	j = 0;
	for (i = 0; i < n_remaining / 4; i++)
	{
		team[0].members[i] = remaining_index[j];
		team[1].members[i] = remaining_index[j + 1];
		team[2].members[i] = remaining_index[j + 2];
		team[3].members[i] = remaining_index[j + 3];

		j += 4;
	}

	for (i = 0; i < 4; i++)
	{
		team[i].total_weight = 0;
		cout << "Team " << i + 1 << ": ";
		for (j = 0; j < n_remaining / 4; j++)
		{
			cout << remaining_contestants[team[i].members[j]].number << " ";
			team[i].total_weight += remaining_contestants[team[i].members[j]].weight;
		}
		cout << "- total weight: " << team[i].total_weight << endl;

		cout << endl;
	}

	int max1, max2, final_max;

	max1 = maxNum<int>(team[0].total_weight, team[1].total_weight);
	max2 = maxNum<int>(team[2].total_weight, team[3].total_weight);
	final_max = maxNum<int>(max1, max2);

	int eliminate_numbers[40], l;

	l = 0;
	for (i = 0; i < 4; i++)
	{
		if (final_max != team[i].total_weight)
		{
			for (j = 0; j < 12; j++)
			{
				eliminate_numbers[l] = remaining_contestants[team[i].members[j]].number;
				l++;
			}
		}
	}

	bubbleSort(eliminate_numbers, (n_remaining/4)*3);

	l = 0;
	for (i = 0; i < n_remaining; i++)
	{
		if (remaining_contestants[i].number == eliminate_numbers[l])
		{
			eliminate_contestants(remaining_contestants, &n_remaining, i);
			i--;
			l++;
		}
	}

	cout << "\t --REMAINING CONTESTANTS--" << endl;
	for (i = 0; i < n_remaining; i++)
	{
		remaining_contestants[i].printData();
	}

}