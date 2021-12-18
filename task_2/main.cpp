#include "hashtable.h"
#include <iostream>


int main()
{
	HashTable a;
	Student s;
	s.age = 10;
	s.weight = 70;
	Key name = "Valery Simka", n = "Konstantin Troitsky";
	a.insert(name, s);
	cout << a.contains(n);
	return 0;
}