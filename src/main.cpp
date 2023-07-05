#include <iostream>
#include <string>
#include <fstream> //read du fichier
#include <map>
#include <sstream> //for isstringstream, string -> int
#include <cstdlib> //pour abort

#include "../inc/BitcoinExchange.hpp"

std::map<std::string, double>	file_to_map(std::string file, char separator)
{
	std::ifstream	inputFile(file.c_str());

	std::map<std::string, double>	data;

	std::string	line_readed	= "";
	std::string	date		= "";
	std::string	value_str	= "";
	double		value		= 0;
	size_t		pos		= 0;
	int		loop		= 0;//remove?

	std::istringstream	iss;

	/*
	   std::map<std::string, double>	database;
	   std::string	line_readed;
	   std::string			date;
	   std::string			value_str;
	   double				value;
	   size_t	pos;
	   std::istringstream	iss;
	 */

	while (getline(inputFile, line_readed))
	{
		if (loop == 0)
		{loop++; continue;}

		//security check line

		pos = line_readed.find(separator);
		//if (pos == std::string::npos) ??

		date = line_readed.substr(0, pos);

		//if (line_readed[pos + 1] == '\0') ??
		value_str = line_readed.substr(pos + 1);

		//std::cout << "[" << value_str << "]" << " : ";

		iss.str(value_str);
		if (loop != 0 && !(iss >> value))
		{std::cerr << "abort: loop {" << loop << "}" << std::endl; abort();}//change

		iss.clear();// est ce suffisant
			    //iss.seekg(0); //utilite?

			    //std::cout << "{" << value << "}" << std::endl;

		if (data.insert(std::pair<std::string, double>(date, value)).second == false)
			abort();

	}

	return	data;
	// resoudre le probleme de la perte de la deuxieme decimale dans la conversion
	// a partir de 2020-07-25,9551.28 (wtf)
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Bad number of arguments" << std::endl;
		return 1;
	}

	//protect read

	std::map<std::string, double>	dollar_rate, bitcoins;

	dollar_rate = file_to_map("data.csv", ',');

	(void)argv[1];
	//bitcoin = file_to_map(argv[1], '|')

	for (std::map<std::string, double>::iterator it = dollar_rate.begin(); it != dollar_rate.end(); it++)
		std::cout << "[" << it->first << "] - [" << it->second << "]" << std::endl;

	return 0;
}
