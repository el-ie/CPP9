#include <iostream>
#include <string>
#include <fstream> //read du fichier
#include <map>
#include <sstream> //for isstringstream, string -> int
#include <cstdlib> //pour abort

#include <cfloat>
#include <cmath>

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

bool	isOnlyDigits(std::string str)
{
	for (int i = 0; str[i]; ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(str[i])))
			return false;
	}
	return true;
}

#define DEBUGG 1

bool	correct_date(std::string date)
{
	//TODO gerer le cas de la double date avec l'ajout des points ....	

	if (date.size() != 10)
	{
		if (DEBUGG) std::cout << "if (date.size() != 10)" << std::endl;
		return false;
	}

	if (!isOnlyDigits(date.substr(0,4) + date.substr(5,2) + date.substr(8,2)))
	{
		if (DEBUGG) std::cout << "!Isdigitonly" << std::endl;
		return false;
	}

	if (date[4] != '-' || date[7] != '-')
	{	
		if (DEBUGG) std::cout << "Guillement" << std::endl;
		return false;
	}

	std::string year_str = date.substr(0,4);
	std::string month_str = date.substr(5,2);
	std::string day_str = date.substr(8,2);

	int	year = std::atoi(year_str.c_str());
	int	month = std::atoi(month_str.c_str());
	int	day = std::atoi(day_str.c_str());

	if (year < 2009 || year > 2023)
	{
		if (DEBUGG) std::cout << "year < 2009 || year > 2023 " << std::endl;
		return false;
	}

	if (year == 2023 && month > 6)
	{
		if (DEBUGG) std::cout << "year == 2023 || month > 6 " << std::endl;
		return false;
	}

	if (month < 1 || month > 12)
	{
		if (DEBUGG) std::cout << "month < 1 || month > 12 " << std::endl;
		return false;
	}

	if (day < 1 || day > 31)
	{
		if (DEBUGG) std::cout << "day < 1 || day > 31 " << std::endl;
		return false;
	}


	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
		{
			if (DEBUGG) std::cout <<"month == 4 || month == 6 || month == 9 || month == 11 ET day > 30\n";
			std::cout << "day > 30" << std::endl;
			return false;
		}
	}


	if (month == 2)
	{
		if (DEBUGG) std::cout << "month ==2\n" << std::endl;
		if (day > 29)
			return false;

		if (year % 4 == 0)
		{
			if (!(year % 100 == 0) || year % 400 == 0)
				if (day > 29)
					return false;
		}
		else
			if (day > 28)
				return false;
	}


	return true;
}

void	check_and_calcul(std::string Bdate, double Bvalue, double Drate)
{

	std::cout << std::endl << "			=>  [" << Bdate << "]  <=" << std::endl;

	if (!correct_date(Bdate) || Bvalue < 0 || Bvalue > 1000)
	{
		if (!correct_date(Bdate))
		{
			//std::cerr << "Error: bad input => " << Bdate << std::endl;
			std::cerr << Bdate << "] INCORRECT DATE" << std::endl;
			std::cerr << "\n----------------------------" << std::endl;
		}
		if (Bvalue < 0)
			std::cerr << "Error: not a positive number. (" << Bvalue << ")" << std::endl;
		if (Bvalue > 1000)
			std::cerr << "Error: too large a number. (" << Bvalue << ")" << std::endl;
		return;
	}

	(void)Drate;

	//double result = Bvalue * Drate; //check over the flow ?

	//std::cout << Bdate << " => " << Bvalue << " = " << result << "(" << Drate << ")" << std::endl;


}

int	main(int argc, char **argv)
{
	/*
	   if (argc != 2)
	   {
	   std::cerr << "Error: could not open file." << std::endl; //????????
	   return 1;
	   }
	 */

	(void)argc;

	//protect read

	std::map<std::string, double>	dollar_rate, bitcoins;

	dollar_rate = file_to_map("data.csv", NODEBUG, ",");

	bitcoins = file_to_map(argv[1], DEBUG, " | ");

	display_map(dollar_rate, 100);

	std::cout << "\n ----------------------- \n\n";

	display_map(bitcoins, 1);

	std::cout << "\n ##################################################### \n";
	////////////////////////////////////////////
	/*
	   std::cout << "correct = " << correct_date(argv[2]) << std::endl;
	   return 0;
	 */
	///////////////////////////////////////////

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
					check_and_calcul(itB->first, itB->second, itD->second);
				//std::cout << "normal CROSS {" << itB->first << "} {" << itD_last->first << "}" << std::endl;
				else //sinon c est le premier tour et on doit prendre itD et non last
					check_and_calcul(itB->first, itB->second, itD->second);
				//std::cout << "first CROSS {" << itB->first << "} {" << itD->first << "}" << std::endl;

				break;//??
			}
			itD_last = itD;
			itD++;
		}
		//if (itD == dollar_rate.end() && !(itB->first < itD_last->first))
		if (itD == dollar_rate.end())
			check_and_calcul(itB->first, itB->second, itD->second);
		//std::cout << "CROSS END {" << itB->first << "} {" << itD_last->first << "}" << std::endl;
	}

	std::cout << std::endl;

	return 0;
}

/*
int	main(int argc, char **argv)
{
	(void)argc;

	int result = correct_date(argv[1]);
	if (result == 1)
		std::cout << "Success" << std::endl;
	if (result == 0)
		std::cout << "FAIL" << std::endl;
}
*/

