#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h> 
#include <algorithm>
#include <random>

#define n_contestants 99	// number of total contestants
#define n_guards 9	// number of guards

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

//

class Participant
{
private:
	unsigned int debt;
	int weight;

public:
	string surname;
	string name;
	string city;

	void setData();
	int getDebt();
	int getWeight();
	virtual void printData() = 0;

};

void Participant::setData()
{
	int random;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(10000, 100000);

	random = rand() % 15;
	name = random_names[random];

	random = rand() % 15;
	surname = random_surnames[random];

	random = rand() % 10;
	city = random_cities[random];

	debt = distr(gen);
	weight = rand() % 50 + 50;
}

int Participant::getDebt()
{
	return this->debt;
}

int Participant::getWeight()
{
	return this->weight;
}

//

class Contestant : public Participant
{
public:
	int number;

	Contestant() {};
	~Contestant() {}

	void setNumber(int n);
	void printData();

	friend void eliminateContestants(Contestant remaining_contestants[], int* n_remaining, int i);
};

void Contestant::setNumber(int n)
{
	number = n;
}

void Contestant::printData()
{
	cout << number << "\t"
		<< name << "\t"
		<< surname << "\t"
		<< city << "\t$"
		<< getDebt() << "\t"
		<< getWeight() << "kg " << endl;
}

void eliminateContestants(Contestant remaining_contestants[], int* n_remaining, int i)
{
	int j;

	for (j = i; j < *n_remaining - 1; j++)
	{
		remaining_contestants[j] = remaining_contestants[j + 1];
	}
	(*n_remaining)--;
}

//

class Guard : public Participant
{
private:
	int group[11];
	int prize;

public:
	string mask;

	Guard() {}
	~Guard() {}

	void setGroup(int j);
	int getGroup(int j);
	void setPrize(int p);
	int getPrize();
	void printData();

	int calculatePrize(Contestant contestants[], int winner_number);
	void calculateTeamPrize(int* team_prize, string mask_check);
};

void Guard::setGroup(int j)
{
	int i = 0;
	int jmax = j + 11;

	for (; j < jmax; j++)
	{
		this->group[i] = random_numbers[j];
		i++;
	}
}

int Guard::getGroup(int j)
{
	return this->group[j];
}

void Guard::setPrize(int p)
{
	this->prize = p;
}

int Guard::getPrize()
{
	return this->prize;
}

void Guard::printData()
{
	cout << mask << " "
		<< name << "\t"
		<< surname << "\t"
		<< city << "\t$"
		<< getDebt() << endl;
}

int Guard::calculatePrize(Contestant contestants[], int winner_number)
{
	int j;

	prize = getDebt() * (-1);

	for (j = 0; j < n_contestants / n_guards; j++)
	{
		if (getGroup(j) == winner_number)
		{
			prize += contestants[winner_number - 1].getDebt() * 10;
		}
		else prize += contestants[getGroup(j) - 1].getDebt();
	}

	return prize;
}

void Guard::calculateTeamPrize(int* team_prize, string mask_check)
{
	if (mask == mask_check)
	{
		(*team_prize) += prize;
	}
}

//

class TugOfWar
{
public:

	int members[15];
	int total_weight;

	TugOfWar() {}
	~TugOfWar() {}

	void calculateWeight(Contestant remaining_contestants[], int n_remaining);
	void compareWeight(int max_weight, int i1, int i2, int* imax);

};

void TugOfWar::calculateWeight(Contestant remaining_contestants[], int n_remaining)
{
	int i;

	total_weight = 0;

	for (i = 0; i < n_remaining / 4; i++)
	{
		cout << remaining_contestants[members[i]].number << " ";
		total_weight += remaining_contestants[members[i]].getWeight();
	}
}

void TugOfWar::compareWeight(int max_weight, int i1, int i2, int* imax)
{
	cout << "Team " << i1 + 1 << " vs Team " << i2 + 1 << " ----- ";

	try
	{
		if (max_weight == total_weight)
		{
			*imax = i1;
			throw i2;
		}
		else
		{
			*imax = i2;
			throw i1;
		}
	}
	catch (int x)
	{
		cout << "Team " << x + 1 << " eliminated!" << endl;
	}
}

//

class Marbles
{
public:

	int marbles;

	Marbles();
	~Marbles() {}

};

Marbles::Marbles()
{
	marbles = rand() % 10 + 1;
}

//

class Genken
{
public:
	
	int n_choice;
	string choice;

	Genken();
	~Genken() {}
};

Genken::Genken()
{
	string genken[3] = { "rock", "paper", "scissors" };
	n_choice = rand() % 3 + 1;
	choice = genken[n_choice - 1];
}

//

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
int partition(X array[], int low, int high)	// ascending template
{
	int pivot = array[high];
	int i, j;

	i = low - 1;

	for (j = low; j < high; j++)
	{
		if (array[j] < pivot)
		{
			i++;
			swap<X>(&array[i], &array[j]);
		}
	}
	swap<X>(&array[i + 1], &array[high]);

	return (i + 1);
}

template <>
int partition(Guard array[], int low, int high) // descending template specialization for Guard objects
{
	int pivot = array[high].getPrize();
	int i, j;

	i = low - 1;

	for (j = low; j < high; j++)
	{
		if (array[j].getPrize() > pivot)
		{
			i++;
			swap<Guard>(&array[i], &array[j]);
		}
	}
	swap<Guard>(&array[i + 1], &array[high]);

	return (i + 1);
}

template <typename X>
void quickSort(X array[], int low, int high)
{
	if (low < high)
	{
		int part = partition(array, low, high);

		quickSort<X>(array, low, part - 1);
		quickSort<X>(array, part + 1, high);
	}
}

//

int main()
{
	int i, j, k;
	int i1, i2;

	srand((unsigned int)time(NULL));

	// GETTING READY

	// setting data for contestants

	Contestant* contestants = new Contestant[99]; // contestants array will NOT be modified

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

	Contestant* remaining_contestants = new Contestant[99];	// will be modified when contestants are eliminated
	int n_remaining;	// number of remaining contestants; will be modified 

	for (i = 0; i < n_contestants; i++)
	{
		remaining_contestants[i] = contestants[i];
	}

	n_remaining = n_contestants;

	cout << "--------------------------------------------" << endl << endl;


	// setting data for guards

	Guard* guards = new Guard[9];

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


	// splitting contestants into equal groups so each guard will have 11 contestants

	cout << "Guards and the contestants they will supervise:" << endl;

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
	cout << "Press enter to continue to the game . . .";
	cin.get();

	cout << "--------------------------------------------" << endl << endl;

	// eliminating contestants

	for (i = 0; i < n_remaining; i++)
	{
		if (remaining_contestants[i].number % 2 == 0)
		{
			eliminateContestants(remaining_contestants, &n_remaining, i);
		}
	}

	// remaining contestants

	cout << "\t --REMAINING CONTESTANTS--" << endl;
	cout << "--------------------------------------------" << endl;

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
	cout << "Press enter to continue to the game . . .";
	cin.get();

	cout << "--------------------------------------------" << endl << endl;

	// dividing contestants

	TugOfWar* group_tow = new TugOfWar[4];
	int* index_tow = new int[50];

	for (i = 0; i < n_remaining; i++)	// saving the remaining contestants index to shuffle the array and randomize the teams
	{
		index_tow[i] = i;
	}

	random_shuffle(index_tow, index_tow + n_remaining);

	j = 0;
	for (i = 0; i < n_remaining / 4; i++)
	{
		group_tow[0].members[i] = index_tow[j];
		group_tow[1].members[i] = index_tow[j + 1];
		group_tow[2].members[i] = index_tow[j + 2];
		group_tow[3].members[i] = index_tow[j + 3];

		j += 4;
	}

	cout << "\t\t--Tug of War teams--" << endl;
	for (i = 0; i < 4; i++)
	{
		cout << "Team " << i + 1 << ": ";
		group_tow[i].calculateWeight(remaining_contestants, n_remaining); // calculating the total weight of the team
		cout << "- total weight: " << group_tow[i].total_weight << "kg" << endl;
	}

	cout << endl;

	// the Tug of War game

	int max1, max2, final_max;

	max1 = maxNum(group_tow[0].total_weight, group_tow[1].total_weight); // team 1 vs team 2; i1 is the index for the winner team
	group_tow[0].compareWeight(max1, 0, 1, &i1);

	max2 = maxNum(group_tow[2].total_weight, group_tow[3].total_weight); // team 3 vs team 4; i2 is the index for the winner team
	group_tow[2].compareWeight(max2, 2, 3, &i2);

	final_max = maxNum(max1, max2);
	group_tow[i1].compareWeight(final_max, i1, i2, &i1);

	cout << endl;

	cout << "\t\tTEAM " << i1 + 1 << " WINS!" << endl;

	cout << endl;


	// eliminating contestants

	int* eliminate_tow = new int[40]; // the numbers for the contestants aren't sorted so we will need to sort an array with the numbers that need to be eliminated

	k = 0;
	for (i = 0; i < 4; i++)
	{
		if (final_max != group_tow[i].total_weight)
		{
			for (j = 0; j < 12; j++)
			{
				eliminate_tow[k] = remaining_contestants[group_tow[i].members[j]].number; // copying the numbers that need to be eliminated from the teams that were eliminated
				k++;
			}
		}
	}

	quickSort<int>(eliminate_tow, 0, (n_remaining / 4) * 3 - 1);

	k = 0;
	for (i = 0; i < n_remaining; i++)
	{
		if (remaining_contestants[i].number == eliminate_tow[k])
		{
			eliminateContestants(remaining_contestants, &n_remaining, i);
			i--;
			k++;
		}
	}

	// remaining contestants

	cout << "\t --REMAINING CONTESTANTS--" << endl;
	cout << "--------------------------------------------" << endl;

	for (i = 0; i < n_remaining; i++)
	{
		remaining_contestants[i].printData();
	}

	cout << "--------------------------------------------" << endl << endl;

	cout << "Press enter to continue . . .";
	cin.get();

	cout << "--------------------------------------------" << endl << endl;

	delete[] group_tow;
	delete[] eliminate_tow;
	delete[] index_tow;

	// 3. MARBLES

	cout << "The third game is MARBLES." << endl;
	cout << "The contestants will be split into pairs." << endl << endl;
	cout << "Press enter to continue to the game . . .";
	cin.get();

	cout << "--------------------------------------------" << endl << endl;

	// splitting into pairs

	Marbles* marbles = new Marbles[20];

	int* index_marbles = new int[14];

	for (i = 0; i < n_remaining; i++)
	{
		index_marbles[i] = i; // saving the remaining contestants index to shuffle the array and randomize the pairs
	}

	random_shuffle(index_marbles, index_marbles + n_remaining);

	// the Marbles game

	int m1, m2;
	int* eliminate_marbles = new int[14]; // the numbers for the contestants aren't sorted so we will need to sort an array with the numbers that need to be eliminated

	k = 0;
	for (i = 0; i < n_remaining; i += 2)
	{
		i1 = index_marbles[i];
		i2 = index_marbles[i + 1];

		while (true)
		{
			try
			{
				if (marbles[i1].marbles == marbles[i2].marbles)
				{
					throw 1;
				}
				else break;
			}
			catch (...)
			{
				marbles[i1] = Marbles();
				marbles[i2] = Marbles();
			}
		}

		m1 = marbles[i1].marbles;
		m2 = marbles[i2].marbles;

		cout << remaining_contestants[i1].number << " -> " << m1 << " marbles vs ";
		cout << remaining_contestants[i2].number << " -> " << m2 << " marbles" << " ----- ";

		if (m1 > m2)
		{
			cout << remaining_contestants[i1].number << " eliminated" << endl;
			eliminate_marbles[k] = remaining_contestants[i1].number;
			k++;
		}
		else
		{
			cout << remaining_contestants[i2].number << " eliminated" << endl;
			eliminate_marbles[k] = remaining_contestants[i2].number;
			k++;
		}
	}

	// eliminating cotestants

	quickSort<int>(eliminate_marbles, 0, (n_remaining / 2) - 1);

	k = 0;
	for (i = 0; i < n_remaining; i++)
	{
		if (remaining_contestants[i].number == eliminate_marbles[k])
		{
			eliminateContestants(remaining_contestants, &n_remaining, i);
			i--;
			k++;
		}
	}

	cout << endl;

	// remaining contestants

	cout << "\t --REMAINING CONTESTANTS--" << endl;
	cout << "--------------------------------------------" << endl;

	for (i = 0; i < n_remaining; i++)
	{
		remaining_contestants[i].printData();
	}

	cout << "--------------------------------------------" << endl << endl;

	cout << "Press enter to continue . . .";
	cin.get();

	cout << "--------------------------------------------" << endl << endl;

	delete[] marbles;
	delete[] eliminate_marbles;

	// 4. GENKEN

	cout << "The final game is GENKEN." << endl;
	cout << "The contestants will duel until only one remains." << endl << endl;
	cout << "Press enter to continue to the game. . .";
	cin.get();

	cout << endl;

	// the Genken game - until only one contestant remains

	Genken* genken = new Genken[2];
	int g1, g2;

	while (n_remaining != 1)
	{
		for (i = n_remaining - 1; i >= 0; i -= 2)
		{
			genken[0] = Genken();
			genken[1] = Genken();

			while (true)
			{
				try
				{
					if (genken[0].choice == genken[1].choice)
					{
						throw 1;
					}
					else break;
				}
				catch (...)
				{
					genken[0] = Genken();
					genken[1] = Genken();
				}
			}

			i1 = i;
			if (i == 0)
			{
				i2 = n_remaining - 1;
			}
			else i2 = i - 1;

			g1 = genken[0].n_choice; // i1
			g2 = genken[1].n_choice; // i2

			cout << remaining_contestants[i1].number << " -> " << genken[0].choice << " vs ";
			cout << remaining_contestants[i2].number << " -> " << genken[1].choice << " ----- ";

			if ((g1 == 1 && g2 == 2) || (g1 == 2 && g2 == 3) || (g1 == 3 && g2 == 1))
			{
				cout << remaining_contestants[i1].number << " eliminated" << endl;
				eliminateContestants(remaining_contestants, &n_remaining, i1);
			}
			else if ((g1 == 2 && g2 == 1) || (g1 == 3 && g2 == 2) || (g1 == 1 && g2 == 3))
			{
				cout << remaining_contestants[i2].number << " eliminated" << endl;
				eliminateContestants(remaining_contestants, &n_remaining, i2);
			}
		}
	}

	cout << endl;

	delete[] genken;

	// the winner

	cout << "WINNER:\t CONTESTANT NO. "
		<< remaining_contestants[0].number << " "
		<< remaining_contestants[0].name << " "
		<< remaining_contestants[0].surname << endl;

	cout << "--------------------------------------------" << endl << endl;

	cout << "Press enter to continue . . .";
	cin.get();

	cout << "--------------------------------------------" << endl << endl;


	// calculating the prizes

	int winner_prize = remaining_contestants[0].getDebt() * (-1);
	int prize_circle = 0, prize_triangle = 0, prize_square = 0;
	int max_prize;

	for (i = 0; i < n_contestants; i++)	// calculating the winner contestant's prize
	{
		winner_prize += contestants[i].getDebt();
	}

	cout << "The winner won the big prize: $" << winner_prize << endl << endl;

	for (i = 0; i < n_guards; i++)	// calculating the prize for each guard
	{
		guards[i].setPrize(guards[i].calculatePrize(contestants, remaining_contestants[0].number));
	}

	quickSort<Guard>(guards, 0, n_guards - 1);	// sorting guards in descending order of their prizes

	cout << "\t--GUARDS--" << endl;
	cout << "Mask\tName\tSurname\tPrize" << endl;
	cout << "--------------------------------------------" << endl;

	for (i = 0; i < n_guards; i++)
	{
		cout << guards[i].mask << " "
			<< guards[i].name << "\t"
			<< guards[i].surname << "\t$"
			<< guards[i].getPrize() << endl;

		guards[i].calculateTeamPrize(&prize_circle, "circle");		// calculating the prize for each team of guards
		guards[i].calculateTeamPrize(&prize_triangle, "triangle");
		guards[i].calculateTeamPrize(&prize_square, "square");

	}

	cout << endl;

	max_prize = maxNum(maxNum(prize_circle, prize_square), prize_triangle);

	cout << "Team circle - $" << prize_circle << endl
		<< "Team triangle - $" << prize_triangle << endl
		<< "Team square - $" << prize_square << endl
		<< endl;

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

	cout << endl << endl;

	cout << "--------------------------------------------" << endl << endl;

	cout << "Press enter to continue . . .";
	cin.get();

	cout << "--------------------------------------------" << endl << endl;

	delete[] contestants;
	delete[] remaining_contestants;
	delete[] guards;

	return 0;
}