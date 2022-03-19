#pragma once
#include "data.h"
#include "Tables.h"

#include <filesystem>
#include <array>
#include <vector>

#define _PRINT_DEBUG

using std::filesystem::path;

class Translator
{
public:
	Translator(const path& _path)
	{
		lexicalAnalysis(_path);
#ifdef _PRINT_DEBUG
		constant_tabel.printTable();
		identifier_tabel.printTable();
#endif
	}

private:
	void lexicalAnalysis(const path&);
	size_t errorHandler(std::string str); // возвращает номер символа в слове, на котором остановился

private:
	const std::vector<std::string> keywords{ "else", "if", "int", "main", "return","void" };
	const std::vector<std::string> separators{ "(", ")",  ",", ";","{", "}" };
	const std::vector<std::string> operations{ "!=", "*", "+", "-", "<", "==", "=", "*=", "+=", "-=" };

	HashTableVar identifier_tabel;
	HashTableConst constant_tabel;
};
