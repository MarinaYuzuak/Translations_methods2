#include "Translator.h"

int main()
{

	using ::std::filesystem::path;

	path dir_to_file = "files/test-6";
	Translator tarnslator(dir_to_file);

	return 0;
}