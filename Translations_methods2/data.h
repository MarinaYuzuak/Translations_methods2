#pragma once
#include <string>

struct Variable
{
    std::string name;
    std::string type;
    std::string value;
};

enum class TypesOfTables
{
    VARIABLE_TABEL,
    CONSTATN_TABEL,
    KEYWORDS_TABLE,
    OPERATIONS_TABEL,
    SEPARATORS_TABEL
};

enum class SymbolType
{
    FORWARD_SLASH,
    LETTER_OR_UNDERSCORE, // буква или нижнее подчеркивание
    NUMBER,
    OPERATION,
    SEPARATOR,
    DEFAULT
};