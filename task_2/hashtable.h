#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <iostream>
#endif

using namespace std;

// � ���� ������ ��� �������� �� ��������� ������ ��������� ���������,
// ��� ����������� �� �������. ��� ������������ �������,
// ������ ���� ������ � ��������: ������ ����� ��������� ������ (��������, ���
// ��������, ��������� - ������������ ��������� (��������, ���������
// �������������� ��������.
struct Student {
	unsigned age;
	unsigned weight;
};

typedef std::string Key;
typedef Student Value;

class HashTable
{
	vector<list<pair<Key, Value>>*> hash;
	int current_size;
	int max_size;
	Value average_student/*{}*/;

public:
	HashTable();
	~HashTable();
	HashTable(const HashTable& b);
	HashTable(HashTable&& b);
	HashTable& operator=(const HashTable& b);
	HashTable& operator=(HashTable&& b);
	// ���������� �������� ���� ���-������.
	void swap(HashTable& b);
	// ������� ���������.
	void clear();
	// ������� ������� �� ��������� �����.
	bool erase(const Key& k);
	// ������� � ���������. ������������ �������� - ���������� �������.
	bool insert(const Key&  k, const Value& v);
	// �������� ������� �������� �� ��������� �����.
	bool contains(const Key& k) const;
	// ���������� �������� �� �����. ������������ �����.
	// � ������ ���������� ����� � ����������, ������� �������� � ���������
	// ��������, ��������� ������������� �� ��������� � ������� ������ �� ����.
	Value& operator[](const Key& k);
	// ���������� �������� �� �����. ������� ���������� ��� �������.
	Value& at(const Key& k);
	const Value& at(const Key& k) const;
	size_t size() const;
	bool empty() const;
	friend bool operator==(const HashTable& a, const HashTable& b);
	friend bool operator!=(const HashTable& a, const HashTable& b);
	void resize(int New_Size, list<pair<Key, Value>>* Val);
};

bool operator==(const HashTable& a, const HashTable& b);
bool operator!=(const HashTable& a, const HashTable& b);
int HashFunc(const Key& s, int max_size);



