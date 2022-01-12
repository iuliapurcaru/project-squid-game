#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h> 
#include <algorithm>

#define n_contestants 99	// number of remaining contestants; always stays the same
#define n_guards 9	//number of guards; always stays the same

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

	virtual void printData() {}
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
	//int prize;
	
public:
	string mask;
	int prize;

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

	int calculatePrize(Contestant contestants[], int winner_number);
	void calculateTeamPrize(int *team_prize, string mask_check);

	int getGroup(int j)
	{
		return this->group[j];
	}

	void setPrize(int p)
	{
		prize = p;
	}
	
	int getPrize()
	{
		return this->prize;
	}

	void printData()
	{
		cout << mask << " " << name << "\t" << surname << "\t" << city << "\t$" << debt << endl;
	}

};

int Guard::calculatePrize(Contestant contestants[], int winner_number)
{
	int j;

	prize = debt * (-1);

	for (j = 0; j < n_contestants / n_guards; j++)
	{
		if (getGroup(j) == winner_number)
		{
			prize += contestants[winner_number - 1].debt * 10;
		}
		else prize += contestants[getGroup(j) - 1].debt;
	}

	return prize;

}

void Guard::calculateTeamPrize(int *team_prize, string mask_check)
{
	if (mask == mask_check)
	{
		(*team_prize) += prize;
	}
}

class TugOfWar
{
public:

	int members[15];
	int total_weight;

	TugOfWar() {}
	~TugOfWar() {}

};

class Marbles
{
public:

	int marbles;
	int index;

	Marbles();
	~Marbles() {}

};

Marbles::Marbles()
{
	marbles = rand() % 10 + 1;
}

class Genken
{
public:

	void genkenGame(int a, int b)
	{
		if (a == 1 && b == 2)
		{

		}
		else if (a == 1 && b == 3)
		{

		}
		else if (a == 2 && b == 3)
		{

		}
	}
};

void eliminate_contestants(Contestant remaining_contestants[], int* n_remaining, int i)
{
	int j;

	for (j = i; j < *n_remaining - 1; j++)
	{
		remaining_contestants[j] = remaining_contestants[j + 1];
	}
	(*n_remaining)--;
}

int maxNum(int a, int b)
{
	if (a > b)
		return a;
	else return b;
}

template <typename X>
void swap(X* a, X* b)
{
	X aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

template <typename X>
void selectionSort(X arr[], int n)
{
	int i, j, idx;

	for (i = 0; i < n - 1; i++)
	{
		idx = i;
		for (j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[idx])
			{
				idx = j;
			}
		}
		swap<int>(&arr[i], &arr[idx]);
	}
}

template <>
void selectionSort(Guard arr[], int n)
{
	int i, j, idx;
	Guard aux;

	for (i = 0; i < n - 1; i++)
	{
		idx = i;
		for (j = i + 1; j < n; j++)
		{
			if (arr[j].getPrize() > arr[idx].getPrize())
			{
				idx = j;
			}
		}
		swap<Guard>(&arr[i], &arr[idx]);

	}
}

int main()
{
	int i, j, aux;

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

	int n_remaining;	// number of remaining contestants; will be modified 
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

	// remaining contestants

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
	cout << "The contestants will be divided into 4 groups." << endl << endl;
	cout << "Press enter to continue . . .";
	cin.get();

	cout << endl;

	TugOfWar* group_tow = new TugOfWar[4];
	int remaining_index[50];

	for (i = 0; i < n_remaining; i++)
	{
		remaining_index[i] = i;
	}

	random_shuffle(begin(remaining_index), end(remaining_index));

	j = 0;
	for (i = 0; i < n_remaining / 4; i++)
	{
		group_tow[0].members[i] = remaining_index[j];
		group_tow[1].members[i] = remaining_index[j + 1];
		group_tow[2].members[i] = remaining_index[j + 2];
		group_tow[3].members[i] = remaining_index[j + 3];

		j += 4;
	}

	for (i = 0; i < 4; i++)
	{
		group_tow[i].total_weight = 0;
		cout << "Team " << i + 1 << ": ";
		for (j = 0; j < n_remaining / 4; j++)
		{
			cout << remaining_contestants[group_tow[i].members[j]].number << " ";
			group_tow[i].total_weight += remaining_contestants[group_tow[i].members[j]].weight;
		}
		cout << "- total weight: " << group_tow[i].total_weight << endl;

		cout << endl;
	}

	int max1, max2, final_max;

	max1 = maxNum(group_tow[0].total_weight, group_tow[1].total_weight);
	max2 = maxNum(group_tow[2].total_weight, group_tow[3].total_weight);
	final_max = maxNum(max1, max2);

	int* eliminate_numbers = new int[40];
	int l;

	l = 0;
	for (i = 0; i < 4; i++)
	{
		if (final_max != group_tow[i].total_weight)
		{
			for (j = 0; j < 12; j++)
			{
				eliminate_numbers[l] = remaining_contestants[group_tow[i].members[j]].number;
				l++;
			}
		}
	}

	selectionSort<int>(eliminate_numbers, (n_remaining / 4) * 3);

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

	cout << "--------------------------------------------" << endl << endl;

	cout << "Press enter to continue . . .";
	cin.get();

	cout << "--------------------------------------------" << endl << endl;

	delete[] group_tow;
	delete[] eliminate_numbers;

	// 3. MARBLES

	cout << "The third game is MARBLES." << endl;
	cout << "The contestants will be split into pairs." << endl << endl;
	cout << "Press enter to continue . . .";
	cin.get();

	cout << endl;

	for (i = 0; i < n_remaining; i++)
	{
		remaining_index[i] = i;
	}

	Marbles* marbles = new Marbles[20];
	int m1, m2;

	l = 0;
	for (i = 0; i < n_remaining; i++)
	{
		m1 = marbles[remaining_index[i]].marbles;
		m2 = marbles[remaining_index[i + 1]].marbles;

		cout << remaining_contestants[remaining_index[i]].number << " -> " << m1 << " marbles - ";
		cout << remaining_contestants[remaining_index[i + 1]].number << " -> " << m2 << " marbles" << " ----- ";

		if (m1 > m2)
		{
			cout << remaining_contestants[i].number << " eliminated" << endl;
			eliminate_contestants(remaining_contestants, &n_remaining, i);
		}
		else
		{
			cout << remaining_contestants[i + 1].number << " eliminated" << endl;
			eliminate_contestants(remaining_contestants, &n_remaining, i + 1);
		}
	}

	delete[]marbles;

	cout << endl;

	cout << "\t --REMAINING CONTESTANTS--" << endl;
	for (i = 0; i < n_remaining; i++)
	{
		remaining_contestants[i].printData();
	}

	cout << "--------------------------------------------" << endl << endl;

	cout << "Press enter to continue . . .";
	cin.get();

	cout << "--------------------------------------------" << endl << endl;

	// 4. GENKEN

	cout << "The final game is GENKEN." << endl;
	cout << "The contestants will duel until only one remains." << endl << endl;
	cout << "Press enter to continue . . .";
	cin.get();

	cout << endl;

	int c1, c2, i1, i2;

	while (n_remaining != 1)
	{
		for (i = n_remaining - 1; i >= 0; i -= 2)
		{
			c1 = rand() % 3 + 1; // i
			c2 = rand() % 3 + 1; // i - 1

			while (c1 == c2)
			{
				c1 = rand() % 3 + 1;
				c2 = rand() % 3 + 1;
			}

			i1 = i;
			if (i == 0)
			{
				i2 = n_remaining - 1;
			}
			else i2 = i - 1;

			cout << remaining_contestants[i1].number << " -> " << c1 << " - ";
			cout << remaining_contestants[i2].number << " -> " << c2 << " ----- ";

			if ((c1 == 1 && c2 == 2) || (c1 == 2 && c2 == 3) || (c1 == 3 && c2 == 1))
			{
				cout << remaining_contestants[i1].number << " eliminated" << endl;
				eliminate_contestants(remaining_contestants, &n_remaining, i1);
			}
			else if ((c1 == 2 && c2 == 1) || (c1 == 3 && c2 == 2) || (c1 == 1 && c2 == 3))
			{
				cout << remaining_contestants[i2].number << " eliminated" << endl;
				eliminate_contestants(remaining_contestants, &n_remaining, i2);
			}
		}
	}

	cout << endl;

	cout << "WINNER:\t";
	remaining_contestants[0].printData();

	cout << "--------------------------------------------" << endl << endl;

	cout << "Press enter to continue . . .";
	cin.get();

	cout << "--------------------------------------------" << endl << endl;


	// calculating the prizes

	int winner_prize = remaining_contestants[0].debt * (-1);
	int prize_circle = 0, prize_triangle = 0, prize_square = 0;
	int max_prize;

	for (i = 0; i < n_contestants; i++)
	{
		winner_prize += contestants[i].debt;
	}

	cout << "The big prize: $" << winner_prize << endl << endl;

	for (i = 0; i < n_guards; i++)
	{
		guards[i].setPrize(guards[i].calculatePrize(contestants, remaining_contestants[0].number));
	}

	selectionSort<Guard>(guards, n_guards);

	for (i = 0; i < n_guards; i++)
	{
		cout << guards[i].mask << " ";
		cout << guards[i].name << "\t";
		cout << guards[i].surname << " - $";
		cout << guards[i].getPrize() << endl;

		guards[i].calculateTeamPrize(&prize_circle, "circle");
		guards[i].calculateTeamPrize(&prize_triangle, "triangle");
		guards[i].calculateTeamPrize(&prize_square, "square");
		
	}

	cout << endl;

	max_prize = maxNum(maxNum(prize_circle, prize_square), prize_triangle);

	cout << "Team circle - $" << prize_circle << endl;
	cout << "Team triangle - $" << prize_triangle << endl;
	cout << "Team square - $" << prize_square << endl;
	cout << endl;

	cout << "The team of guards who won the most money: ";
	
	if (prize_circle == max_prize)
	{
		cout << "circle";
	}
	else if (prize_triangle == max_prize)
	{
		cout << "triangle";
	}
	else if (prize_square == max_prize)
	{
		cout << "square";
	}

	cout << endl;

}