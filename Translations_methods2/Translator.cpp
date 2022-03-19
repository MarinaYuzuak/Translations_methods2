#include "Translator.h"

#include <fstream>
#include <iostream>

void Translator::lexicalAnalysis(const path& _path)
{
	std::ofstream fout_errors(_path / "errors.txt");
	std::ofstream fout_tokens(_path / "tokens.txt");

	std::ifstream fin(_path / "program.txt");
	if (fin.is_open())
	{
		std::string str;
		std::string first_symbol;
		std::string second_symbol;
		std::string current_symbol;
		std::string identifier;
		std::vector<std::string> source_line;
		size_t line = 0;
		size_t line_of_multiline_comment;
		int number_in_table;
		bool out_of_multiline_comment = true;

		while (std::getline(fin, str))
		{
			line++;
			std::stringstream sstr;          sstr << str;
			source_line.clear();
			while (sstr >> str)
				source_line.push_back(str);

			first_symbol = " ";
			for (size_t i = 0; i < source_line.size(); i++)
			{
				str = source_line[i];
				for (size_t j = 0; j < str.size(); j++)
				{
					first_symbol = str[j];
					if (!out_of_multiline_comment)
					{
						str.size() == j + 1 ? second_symbol = " " : second_symbol = str[j + 1];
						if (first_symbol == "*" && second_symbol == "/")
						{
							out_of_multiline_comment = true;
							str.size() == ++j + 1 ? first_symbol = " " : first_symbol = str[j + 1];
						}
					}

					if (out_of_multiline_comment && first_symbol != " ")
					{
						SymbolType first_symbol_type = SymbolType::DEFAULT;

						if (("a" <= first_symbol && first_symbol <= "z") || ("A" <= first_symbol && first_symbol <= "Z") || first_symbol == "_")
							first_symbol_type = SymbolType::LETTER_OR_UNDERSCORE;
						else if ("0" <= first_symbol && first_symbol <= "9")
							first_symbol_type = SymbolType::NUMBER;
						else if (first_symbol == "/")
							first_symbol_type = SymbolType::FORWARD_SLASH;
						else if ((number_in_table = Find(separators, first_symbol)) != -1)
							first_symbol_type = SymbolType::SEPARATOR;
						else
						{
							str.size() == j + 1 ? second_symbol = " " : second_symbol = str[j + 1];

							if ((number_in_table = Find(operations, first_symbol + second_symbol)) != -1)
							{
								first_symbol_type = SymbolType::OPERATION;
								j++;
							}
							else if ((number_in_table = Find(operations, first_symbol)) != -1)
								first_symbol_type = SymbolType::OPERATION;
						}

						switch (first_symbol_type)
						{
						case SymbolType::LETTER_OR_UNDERSCORE:
						{
							identifier = first_symbol;
							for (size_t i = j + 1; i < str.size(); i++, j++)
							{
								current_symbol = str[i];
								if ("a" <= current_symbol && current_symbol <= "z" || "A" <= current_symbol && current_symbol <= "Z"
									|| "0" <= current_symbol && current_symbol <= "9" || current_symbol == "_")

									identifier += current_symbol;
								else
									break;
							}

							Variable variable{ identifier, "non", "non" };
							int in_keywords_tabel = Find(keywords, identifier);
							int in_identifier_tabel = identifier_tabel.Find(variable);

							if (in_keywords_tabel == -1)
							{
								if (in_identifier_tabel == -1)
								{
									identifier_tabel.Add(variable);
									in_identifier_tabel = identifier_tabel.Find(variable);
								}
								fout_tokens << "(" << (int)TypesOfTables::VARIABLE_TABEL << ","
									<< in_identifier_tabel << ") ";
							}
							else
								fout_tokens << "(" << (int)TypesOfTables::KEYWORDS_TABLE << ","
								<< in_keywords_tabel << ") ";
						}
						break;
						case SymbolType::NUMBER:
						{
							identifier = first_symbol;
							for (size_t i = j + 1; i < str.size(); i++, j++)
							{
								current_symbol = str[i];
								if ("0" <= current_symbol && current_symbol <= "9")
									identifier += current_symbol;
								else
									break;
							}
							if (!("0" <= current_symbol && current_symbol <= "9")
								&& Find(operations, current_symbol) == -1 && Find(separators, current_symbol) == -1)
							{
								j = errorHandler(str.substr(j));
								fout_errors << "Error in line " << line << ": " << str << std::endl;
							}
							else
							{
								int in_constant_tabel = constant_tabel.Find(identifier);

								if (in_constant_tabel == -1)
								{
									constant_tabel.Add(identifier);
									in_constant_tabel = constant_tabel.Find(identifier);
								}
								fout_tokens << "(" << (int)TypesOfTables::CONSTATN_TABEL << ","
									<< in_constant_tabel << ") ";
							}
						}
						break;
						case SymbolType::FORWARD_SLASH:
						{
							str.size() == j + 1 ? second_symbol = " " : second_symbol = str[++j];
							if (second_symbol == "*")
							{
								out_of_multiline_comment = false;
								line_of_multiline_comment = line;
								for (size_t i = j + 1; i < str.size(); i++, j++)
								{
									current_symbol = str[i];
									if (current_symbol == "*")
									{
										str.size() == i + 1 ? second_symbol = " " : second_symbol = str[i + 1];
										if (second_symbol == "/")
										{
											out_of_multiline_comment = true;
											break;
										}
									}
								}
							}
							else if (second_symbol == "/")
							{
								j = str.size();
								i = source_line.size();
							}
							else
							{
								fout_errors << "Error in line " << line << ": " << str << std::endl;
								j = str.size();
								i = source_line.size();
							}
						}
						break;
						case SymbolType::SEPARATOR:
							fout_tokens << "(" << (int)TypesOfTables::SEPARATORS_TABEL << ","
								<< number_in_table << ") ";
							break;
						case SymbolType::OPERATION:
							fout_tokens << "(" << (int)TypesOfTables::OPERATIONS_TABEL << ","
								<< number_in_table << ") ";
							break;
						default:
							j = errorHandler(str.substr(j));
							fout_errors << "Error in line " << line << ": " << str << std::endl;
							break;
						}
					}
				}
			}
			if (out_of_multiline_comment && first_symbol != " ")
				fout_tokens << std::endl;
		}
		if (!out_of_multiline_comment)
			fout_errors << "Error in line " << line_of_multiline_comment << ": unclosed multiline comment" << std::endl;
	}
	else
	{
		std::cerr << "File `program.txt` not open..." << std::endl;
		std::exit(2);
	}
	fin.close();
	fout_errors.close();
	fout_tokens.close();
}

size_t Translator::errorHandler(std::string str)
{
	std::string begin_of_operation;
	for (size_t i = 0; i < str.size(); i++)
	{
		begin_of_operation = str[i];
		if (Find(operations, begin_of_operation) != -1)
			return i - 1;
	}
	return str.size();
}
