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

void	display_map(std::map<std::string, double> data, int modulo) 
{
	int i = 0;

	for (std::map<std::string, double>::iterator it = data.begin(); it != data.end(); it++)
	{
		i++;
		if (i % modulo == 0)
			std::cout << "[" << it->first << "] - [" << it->second << "]" << std::endl;
	}
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

	bitcoins = file_to_map(argv[1], DEBUG, " | ");

	display_map(dollar_rate, 100);

	std::cout << "\n ----------------------- \n\n";

	display_map(bitcoins, 1);

	std::cout << "\n ----------------------- \n";
	////////////////////////////////////////////

	std::map<std::string, double>::iterator itD;
	std::map<std::string, double>::iterator itD_last;

	for (std::map<std::string, double>::iterator itB = bitcoins.begin(); itB != bitcoins.end(); itB++)
	{
		itD = dollar_rate.begin();
		itD_last = dollar_rate.end();
		//for (std::map<std::string, double>::iterator itD = dollar_rate.begin(); itD != dollar_rate.end(); itD++)
		while (itD != dollar_rate.end())
		{
			if (itB->first < itD->first)
			{
				if (itD_last != dollar_rate.end()) //si ce n'est pas le premier tour et donc itD_last est bon
					std::cout << "CROSS {" << itB->first << "} {" << itD_last->first << "}" << std::endl;
				else //sinon c est le premier tour et on doit prendre itD et non last
					std::cout << "CROSS {" << itB->first << "} {" << itD->first << "}" << std::endl;
					
				break;//??
			}
			itD_last = itD;
			itD++;
		}

		//if (itD == dollar_rate.end() && !(itB->first < itD_last->first))
		if (itD == dollar_rate.end())
			std::cout << "CROSS END {" << itB->first << "} {" << itD_last->first << "}" << std::endl;

	}

	std::cout << std::endl;

	return 0;
}
