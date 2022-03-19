#include "Tables.h"

int HashTableConst::HashFunction(const std::string& s, int table_size)
{
    int hash_result = 0, a = 31415, b = 27183;
    for (size_t i = 0; i < s.size(); i++, a = a * b % (table_size - 1))
        hash_result = (a * hash_result + s[i]) % table_size;
    return hash_result;
}

HashTableConst::HashTableConst()
{
    arr.resize(default_size);
    size = 0;
}

HashTableConst::~HashTableConst() {}

bool HashTableConst::Add(const std::string& value)
{
    if (size + 1 > arr.size())
        arr.resize(2 * arr.size());

    int h1 = HashFunction(value, arr.size());
    int h2 = (h1 * 2 + 1) % arr.size();

    for (size_t i = 0; arr[h1] != "" && i < arr.size(); i++, h1 = (h1 + h2) % arr.size())
        if (arr[h1] == value)
            return false;

    arr[h1] = value;
    size++;
    return true;
}

int HashTableConst::Find(const std::string& value)
{
    int h1 = HashFunction(value, arr.size());
    int h2 = (h1 * 2 + 1) % arr.size();

    for (size_t i = 0; arr[h1] != "" && i < arr.size(); i++, h1 = (h1 + h2) % arr.size())
        if (arr[h1] == value)
            return h1;
    return -1;
}

int HashTableVar::HashFunction(const Variable& v, int table_size)
{
    int hash_result = 0, a = 31415, b = 27183;
    for (size_t i = 0; i < v.name.size(); i++, a = a * b % (table_size - 1))
        hash_result = (a * hash_result + v.name[i]) % table_size;
    return hash_result;
}

HashTableVar::HashTableVar()
{
    arr.resize(default_size);
    size = 0;
}

HashTableVar::~HashTableVar() {}

bool HashTableVar::Add(const Variable& value)
{
    if (size + 1 > arr.size())
        arr.resize(2 * arr.size());

    int h1 = HashFunction(value, arr.size());
    int h2 = (h1 * 2 + 1) % arr.size();

    for (size_t i = 0; arr[h1].name != "" && i < arr.size(); i++, h1 = (h1 + h2) % arr.size())
        if (arr[h1].name == value.name)
            return false;

    arr[h1] = value;
    size++;
    return true;
}

int HashTableVar::Find(const Variable& value)
{
    int h1 = HashFunction(value, arr.size());
    int h2 = (h1 * 2 + 1) % arr.size();

    for (size_t i = 0; arr[h1].name != "" && i < arr.size(); i++, h1 = (h1 + h2) % arr.size())
        if (arr[h1].name == value.name)
            return h1;
    return -1;
}

int Find(const std::vector<std::string>& arr, std::string s)
{
    for (size_t i = 0; i < arr.size(); i++)
        if (arr[i] == s)
            return i;

    return -1;

}

void HashTableConst::printTable()
{
    std::cout << "\nConstant table\n";
    std::cout << "|---------------|---------------|\n";
    std::cout << "|  Num in table |     Value     |\n";
    std::cout << "|---------------|---------------|\n";

    int index = 0;
    for (size_t i = 0; i < arr.size(); i++)
        if ((index = Find(arr[i])) != -1)
        {
            std::cout << "|" << index << "\t\t|" << arr[index] << "\t\t|" << std::endl;
            std::cout << "|---------------|---------------|\n";
        }
}

void HashTableVar::printTable()
{
    std::cout << "\nIdentifier table\n";
    std::cout << "|---------------|---------------|---------------|---------------|\n";
    std::cout << "|  Num in table |     Name      |      Type     |     Value     |\n";
    std::cout << "|---------------|---------------|---------------|---------------|\n";

    int index = 0;
    for (size_t i = 0; i < arr.size(); i++)
        if ((index = Find(arr[i])) != -1)
        {
            std::cout << "|" << index << "\t\t|" << arr[index].name << "\t\t|"
                << arr[index].type << "\t\t|" << arr[index].value << "\t\t|" << std::endl;
            std::cout << "|---------------|---------------|---------------|---------------|\n";
        }
}
