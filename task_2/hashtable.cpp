#include "hashtable.h"

using namespace std;

int HashFunc(const Key& s, int max_size)
{
    int ind = 0;
    for (char c : s) {
        ind += c;
    }
    ind %= max_size;
    return ind;
}

HashTable::HashTable() {
    average_student.weight = 70;
    average_student.age = 20;
    max_size = 10;
    current_size = 0;
    list<pair<Key, Value>>* l = nullptr;
    hash.resize(max_size, l);
}

HashTable::~HashTable() {
    hash.clear();
    max_size = 0;
    current_size = 0;
}

HashTable::HashTable(const HashTable& b) : HashTable() {
    average_student.weight = 70;
    average_student.age = 20;
    current_size = b.current_size;
    max_size = b.max_size;
    hash = b.hash;
}

HashTable::HashTable(HashTable&& b) {
    hash = b.hash;
    current_size = b.current_size;
    max_size = b.max_size;
    for (auto& i : b.hash) {
        i = nullptr;
    }
    b.max_size = 0;
    b.current_size = 0;
}

HashTable& HashTable::operator=(const HashTable& b) {
    if (this == &b) {
        return *this;
    }
    current_size = b.current_size;
    max_size = b.max_size;
    hash.clear();
    hash = b.hash;
    return *this;
}

HashTable& HashTable::operator=(HashTable&& b) {
    if (this == &b) {
        return *this;
    }
    current_size = b.current_size;
    max_size = b.max_size;
    hash.clear();
    hash = b.hash;
    for (auto& i : b.hash) {
        i = nullptr;
    }
}

void HashTable::swap(HashTable& b) {
    int tmpcur = current_size;
    int tmpmax = max_size;
    max_size = b.max_size;
    b.max_size = tmpmax;
    current_size = b.current_size;
    b.current_size = tmpcur;
    hash.swap(b.hash);
}

void HashTable::clear() {
    list<pair<Key, Value>>* l = nullptr;
    hash.clear();
    hash.resize(max_size, l);
}

bool HashTable::erase(const Key& k) {
    if (!contains(k))
        return false;
    else {
        int ind = HashFunc(k, max_size);
        for (auto it = hash[ind]->begin(); it != hash[ind]->end(); it++) {
            if (it->first == k) {
                hash[ind]->erase(it);
                current_size--;
                return true;
            }
        }
    }
}

bool HashTable::insert(const Key& k, const Value& v) {
    if (contains(k))
        return false;
    else {
        int ind = HashFunc(k, max_size);
        if (hash[ind] == nullptr) {
            hash[ind] = new list<pair<Key, Value>>;
        }
        hash[ind]->push_front(make_pair(k, v));
        current_size++;
        if (current_size / max_size > 0.8) {
            list<pair<Key, Value>>* val = nullptr;
            resize(max_size*2, val);
        }
        return true;
    }
}

bool HashTable::contains(const Key& k) const {
    int i = HashFunc(k, max_size);
    if (hash[i] == nullptr) {
        return false;
    }
    for (const auto& it : *hash[i]) {
        if (it.first == k) {
            return true;
        }
    }
    return false;
}
Value& HashTable::operator[](const Key& k) {
    if (contains(k)) {

        int ind = HashFunc(k, max_size);
        for (auto& it : *hash[ind]) {
            if (it.first == k) {
                return it.second;
            }
        }
    }
    insert(k, average_student);
    return average_student;
}

Value& HashTable::at(const Key& k) {
    if (contains(k)) {
        int i = HashFunc(k, max_size);
        for (auto& it : *hash[i]) {
            if (it.first == k) {
                return it.second;
            }
        }
    }
    else {
        throw invalid_argument("Can't find element on this position");
    }
}

size_t HashTable::size() const {
    return current_size;
}

bool HashTable::empty() const {
    for (const auto it : hash) {
        if (it != nullptr) {
            return false;
        }
    }
    return true;
}

void HashTable::resize(int New_Size, list<pair<Key, Value>>* Val) {
    max_size = New_Size;
    hash.resize(max_size, Val);
}

bool operator==(const HashTable& a, const HashTable& b) {
    return a.hash == b.hash;
}

bool operator!=(const HashTable& a, const HashTable& b) {
    return a.hash != b.hash;
}