#include <iostream>
#include <string>
#include <fstream> //read du fichier
#include <map>
#include <sstream> //for isstringstream, string -> int
#include <cstdlib> //pour abort

#include "../inc/BitcoinExchange.hpp"

#define NODEBUG 41
#define DEBUG 40

std::map<std::string, double>	file_to_map(std::string file, int debug, std::string sep_str)
{
	std::ifstream	inputFile(file.c_str()); //check openning

	std::map<std::string, double>	data;

	std::string	line_readed	= "";
	std::string	date		= "";
	std::string	value_str	= "";
	double		value		= 0;
	size_t		pos		= 0;
	int		loop		= 0;//remove?

	//std::istringstream	iss;
	char *endptr;

	(void)debug;

	while (getline(inputFile, line_readed))
	{
		if (loop == 0)
		{loop++; continue;}

		//security check line

		pos = line_readed.find(sep_str.c_str(), 0);       //if (pos == std::string::npos) ??

		date = line_readed.substr(0, pos);        //if (line_readed[pos + 1] == '\0') ??

		value_str = line_readed.substr(pos + sep_str.size());

		//STRINGSTREAM
		/*
		iss.str(value_str);
		if (loop != 0 && !(iss >> value))
		{std::cerr << "abort: loop {" << loop << "}" << std::endl; abort();}//change

		iss.clear();// est ce suffisant
			    //iss.seekg(0); //utilite?
		//std::cout << "{" << value << "}" << std::endl;
		*/

		//STRTOD
		value = std::strtod(value_str.c_str(), &endptr);
		//if endptr == str...

		while (data.find(date) != data.end()) //! dates identiques
			date += '.';

		if (data.insert(std::pair<std::string, double>(date, value)).second == false)
		{
			std::cout << "\n" << "Error insert [" << date << "] [" << value_str << "]" << std::endl;
			abort();
		}
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

	dollar_rate = file_to_map("data.csv", NODEBUG, ",");

	(void)argv;

	bitcoins = file_to_map(argv[1], DEBUG, " | ");

	/*
	for (std::map<std::string, double>::iterator it = dollar_rate.begin(); it != dollar_rate.end(); it++)
		std::cout << "[" << it->first << "] - [" << it->second << "]" << std::endl;

	for (std::map<std::string, double>::iterator it = bitcoins.begin(); it != bitcoins.end(); it++)
		std::cout << "[" << it->first << "] - [" << it->second << "]" << std::endl;
	*/

	int i = 0;
	//for (std::map<std::string, double>::iterator it = dollar_rate.begin(); i < 1601 ; it = dollar_rate.at(i))

	for (std::map<std::string, double>::iterator it = dollar_rate.begin(); it != dollar_rate.end(); it++)
	{
		i++;
		if (i % 100 == 0)
			std::cout << "[" << it->first << "] - [" << it->second << "]" << std::endl;
	}

	std::cout << "\n------------------------------\n\n";

	for (std::map<std::string, double>::iterator it = bitcoins.begin(); it != bitcoins.end(); it++)
		std::cout << "[" << it->first << "] - [" << it->second << "]" << std::endl;

	std::cout << std::endl;
	return 0;
}
