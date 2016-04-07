// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>
#include <cstdlib>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);
vector <Slav *> Slavs_sex(Slav *,int,Slav_sex);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);

	cout << "# Male Slavs\n";
	Slav_sex key = male;
	vector <Slav *> vectorOfSlavs = Slavs_sex(slavs,n,key);
	for (int i = 0; i < vectorOfSlavs.size(); i++){
		cout << vectorOfSlavs[i]->description() << endl;
	}

	cout << "# Female Slavs\n";
	key = female;
	vectorOfSlavs = Slavs_sex(slavs,n,key);
	for (int i = 0; i < vectorOfSlavs.size(); i++){
		cout << vectorOfSlavs[i]->description() << endl;
	}

	delete [] slavs;
}

vector <Slav *> Slavs_sex(Slav * slavs, int n, Slav_sex key)
{
	map <Slav *, Slav_sex> mapOfSlavs;
	vector <Slav *> vectorOfSlavs;

	for (int i = 0; i < n; i++){
		mapOfSlavs.insert(pair<Slav *, Slav_sex>(&slavs[i],slavs[i].sex()));
	}

	for (map<Slav *, Slav_sex>::iterator it=mapOfSlavs.begin(); it!=mapOfSlavs.end(); ++it){
		if (it->second == key)
			vectorOfSlavs.push_back(it->first);
	}

	return vectorOfSlavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.
	bool slavs_used [n];
	for (int i = 0; i < n; i++){
		slavs_used[i] = false;
	}
	for (int i = 0; i < n; i++){
		int tmp;
		do {
			tmp = rand()%n;
		} while (slavs_used[tmp]!=0);
		vectorOfSlavs.push_back(&slavs[tmp]);
		slavs_used[tmp] = 1;
	}


	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze
	for (vector<Slav *>::iterator it = vectorOfSlavs.begin(); it != vectorOfSlavs.end(); ++it){
		cout << (*it)->description() << endl;
	}


	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektora do zbioru.
	for (vector<Slav *>::iterator it = vectorOfSlavs.begin(); it != vectorOfSlavs.end(); vectorOfSlavs.erase(it)){
		setOfSlavs.insert(*it);
	}
	
	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór
	for (set<Slav *>::iterator it=setOfSlavs.begin(); it!=setOfSlavs.end(); ++it){
		mapOfSlavs.insert(pair<Slav *, Slav *>(*it,*(it++)));
	}
	for (set<Slav *>::iterator it=setOfSlavs.begin(); it!=setOfSlavs.end(); it = setOfSlavs.begin()){
		setOfSlavs.erase(it);
	}

	// Wykorzystując iterator, wyświetl wszystkie pary 
	for (map<Slav *, Slav *>::iterator it=mapOfSlavs.begin(); it!=mapOfSlavs.end(); ++it){
		cout << (it->first)->description() << " " << (it->second)->description() << endl;
	}

	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.
	for (int i = 0; i < n; i++){
		queueOfSlavs.push (&slavs[i]);
	}

	REPORT_ADAPTERS;

	printf("## stack\n");

	// Przenieś Słowian z kolejki do stosu.
	for (int i = 0; i < n; i++){
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.
	for (int i = 0; i < n; i++){
		cout << (stackOfSlavs.top())->description() << endl;
		stackOfSlavs.pop();
	}

	REPORT_ADAPTERS;
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}