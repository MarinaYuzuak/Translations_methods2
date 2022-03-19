#pragma once
#include <vector>
#include <iostream>
#include <vector>
#include "data.h"

int Find(const std::vector<std::string>& arr, std::string);

class HashTableVar
{
private:
    static const int default_size = 16;
    std::vector<Variable> arr;
    size_t size;
    int HashFunction(const Variable& v, int table_size);

public:
    HashTableVar();
    ~HashTableVar();
    bool Add(const Variable& value);
    int Find(const Variable& value);
    void SetType(int n, const std::string& type) { arr[n].type = type; }
    void SetValue(int n, const std::string& value) { arr[n].value = value; }
    const Variable& Get(int n) { return arr[n]; }
    void printTable();
};

class HashTableConst
{
private:
    static const int default_size = 16;
    std::vector<std::string> arr;
    size_t size;
    int HashFunction(const std::string& v, int table_size);

public:
    HashTableConst();
    ~HashTableConst();
    bool Add(const std::string& value);
    int Find(const std::string& value);
    const std::string& Get(int n) { return arr[n]; }
    void printTable();
};
