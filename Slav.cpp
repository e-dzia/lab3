#include "Slav.h"
#include <fstream>
#include <cstdlib>
#include <string>
#include <iterator>

using namespace std;

vector <string> Slav::names;
int Slav::_counter = 0;

void Slav::init()
{
	srand(time(NULL));
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}

Slav::Slav()
{
	static int amountOfNames = (init(), names.size());
	_name = names[rand() % amountOfNames];
	_id = _counter++;
}

string Slav::description()
{
	return string("  ") + _name + " [" + to_string(_id) + "]";
}

Slav_sex Slav::sex()
{
	if (_name[_name.length()-1]=='a')
		return female;
	else return male;
}
/* W niegdyś 21, a obecnie 24 (po dodaniu bibliotek) linijce, jest wykonywana leniwa inicjalizacja, czyli inicjalizacja "na ostatnią chwilę".
Operator ',' powoduje, że wykonują się po kolei wszystkie instrukcje, to znaczy najpierw init(), a potem names.size(). Operator ten zwraca osatnią instrukcję, tzn. names.size(), którą przypisuje do statycznej (liczonej tylko raz) zmiennej typu int amountOfNames.*/