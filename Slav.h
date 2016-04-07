#pragma once
#include <string>
#include <vector>

using namespace std;

enum Slav_sex {
	male = 0,
	female = 1
};

class Slav
{
private:
	static void init();

	static std::vector <string> names;
	static int _counter;

	string _name;
	int _id;

public:
	Slav();

	static int counter() { return _counter; }
	
	string name() { return _name; }
	int id() { return _id; }

	string description();

	Slav_sex sex();
};
