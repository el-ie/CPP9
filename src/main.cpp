#include <iostream>
#include <string>
#include <fstream> //read du fichier
#include <map>
#include <sstream> //for isstringstream, string -> int
#include <cstdlib> //pour abort

#include "../inc/BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Bad number of arguments" << std::endl;
		return 1;
	}

	std::ifstream	inputFile(argv[1]);
	std::string	line_readed;

	std::map<std::string, float>	database;
	std::string			date;
	std::string			value_str;
	float				value;
	size_t	pos;

	std::istringstream	iss;

	//protect read

	int	loop = 0;//remove?

	while (getline(inputFile, line_readed))
	{
		//security check line

		//std::cout << line_readed << std::endl;

		pos = line_readed.find(',');
		//if (pos == std::string::npos) ??

		date = line_readed.substr(0, pos);

		//if (line_readed[pos + 1] == '\0') ??
		value_str = line_readed.substr(pos + 1);

		std::cout << value_str << " : ";//DELETE

		iss.str(value_str);
		if (loop != 0 && !(iss >> value))
			{std::cerr << "abort: loop {" << loop << "}" << std::endl; abort();}//change

		iss.clear();// est ce suffisant

		std::cout << value << std::endl;

		if (database.insert(std::pair<std::string, float>(date, value)).second == false)
			abort();

		loop++;
	}

/*
	for (std::map<std::string, float>::iterator it = database.begin(); it != database.end(); it++)
		std::cout << "[" << it->first << "] - [" << it->second << "]" << std::endl;
		*/

	
return 0;
}
