#include <iostream>
#include <string>
#include <fstream> //read du fichier
#include <map>
#include <cstdlib> //pour abort

#include <cfloat>
#include <cmath>
#include <limits>

#include "../inc/BitcoinExchange.hpp"

bool	isOnlyDigits(std::string str)
{
	for (int i = 0; str[i]; ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(str[i])))
			return false;
	}
	return true;
}

bool	correct_number_format(std::string str)
{
	for (int i = 0; str[i]; ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(str[i])))
			if (str[i] != '.' && str[i] != '+' && str[i] != '-')
				return false;
	}
	return true;
}

bool	read_correct_date(std::string line)
{
	if (line.empty())
		return false;

	if (line.size() < 10)
		return false;

	if (!isOnlyDigits(line.substr(0,4) + line.substr(5,2) + line.substr(8,2)))
		return false;

	if (line[4] != '-' || line[7] != '-')
		return false;
	return true;
}

bool	correct_format_read(std::string str, std::string sep_str)
{
	if (str.empty())
		return false;

	if (str.find(sep_str) == std::string::npos)
		return false;

	if (!read_correct_date(str))
		return false;
	
	if (sep_str == " | ")
	{

		if (str.size() < 14)
			return false;
		if (str[11] != '|')
			return false;
		if (str[12] != ' ')
			return false;
		if (!correct_number_format(str.substr(13)))
			return false;
	}
	else if (sep_str == ",")
	{

		if (str.size() < 12)
			return false;
		if (str[10] != ',')
			return false;
		if (!correct_number_format(str.substr(11)))
			return false;
	}
	
	return true;
}

bool	file_to_map(std::ifstream & inputFile, std::map<std::string, double> & data, std::string sep_str)
{
	std::string	line_readed	= "";
	std::string	date		= "";
	std::string	value_str	= "";
	double		value		= 0;
	size_t		pos		= 0;

	char *endptr;

	getline(inputFile, line_readed); 

	while (getline(inputFile, line_readed))
	{
		if (inputFile.fail())
			return false;

		if (line_readed.empty())
			continue;

		if (!correct_format_read(line_readed, sep_str))
		{
			std::cerr << "Error: bad input => " << line_readed << std::endl;
			continue;
		}

		pos = line_readed.find(sep_str.c_str(), 0);
		date = line_readed.substr(0, pos);
		value_str = line_readed.substr(pos + sep_str.size());
		value = std::strtod(value_str.c_str(), &endptr);

		while (data.find(date) != data.end())
			date += '.';

		data.insert(std::pair<std::string, double>(date, value));
	}

	inputFile.close();

	return	true;
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

void	similar_dates_remove_points(std::string & date)
{
	while (date.at(date.length() - 1) == '.')
		date.erase(date.length() - 1);
}

#define DEBUG 0

//date doit etre une copie pour enlever les .
bool	correct_date(std::string date)
{
	if (date.empty())
		return false;

	if (date.find('.') != std::string::npos)
		similar_dates_remove_points(date);

	if (date.size() != 10)
	{
		if (DEBUG) std::cout << "if (date.size() != 10)" << std::endl;
		return false;
	}

	if (!isOnlyDigits(date.substr(0,4) + date.substr(5,2) + date.substr(8,2)))
	{
		if (DEBUG) std::cout << "!Isdigitonly" << std::endl;
		return false;
	}

	if (date[4] != '-' || date[7] != '-')
	{	
		if (DEBUG) std::cout << "Guillement" << std::endl;
		return false;
	}

	std::string year_str = date.substr(0,4);
	std::string month_str = date.substr(5,2);
	std::string day_str = date.substr(8,2);

	int	year = std::atoi(year_str.c_str());
	int	month = std::atoi(month_str.c_str());
	int	day = std::atoi(day_str.c_str());

	if (year == 2009 && month == 1 && day == 1)
		return false;

	if (year < 2009 || year > 2023)
	{
		if (DEBUG) std::cout << "year < 2009 || year > 2023 " << std::endl;
		return false;
	}

	if (year == 2023 && month > 7)
	{
		if (DEBUG) std::cout << "year == 2023 || month > 6 " << std::endl;
		return false;
	}

	if (month < 1 || month > 12)
	{
		if (DEBUG) std::cout << "month < 1 || month > 12 " << std::endl;
		return false;
	}

	if (day < 1 || day > 31)
	{
		if (DEBUG) std::cout << "day < 1 || day > 31 " << std::endl;
		return false;
	}


	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
		{
			if (DEBUG) std::cout <<"month == 4 || month == 6 || month == 9 || month == 11 ET day > 30\n";
			return false;
		}
	}


	if (month == 2)
	{
		if (DEBUG) std::cout << "month ==2\n" << std::endl;
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
	if (!correct_date(Bdate) || Bvalue < 0 || Bvalue > 1000)
	{
		if (!correct_date(Bdate))
			std::cerr << "Error: Incorrect Date => " << Bdate << std::endl;
		if (Bvalue < 0)
			std::cerr << "Error: not a positive number. (" << Bvalue << ")" << std::endl;
		if (Bvalue > 1000)
			std::cerr << "Error: too large a number. (" << Bvalue << ")" << std::endl;
		return;
	}

	double result = Bvalue * Drate;

	std::cout << Bdate << " => " << Bvalue << " = " << result << std::endl;
}

int	error_log(std::string str)
{
	std::cerr << str << std::endl;
	return 1;
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (error_log("Error: could not open file.");
		
	std::ifstream	data_file("data.csv");

	if (!data_file.is_open() || data_file.fail() || data_file.bad())
		return (error_log("Error: could not open file."));

	std::ifstream	bitcoin_wallet_file(argv[1]);

	if (!bitcoin_wallet_file.is_open() || bitcoin_wallet_file.fail() || bitcoin_wallet_file.bad())
	{
		data_file.close();
		return (error_log("Error: could not open file."));
	}

	std::map<std::string, double>	dollar_rate, bitcoins;

	if (file_to_map(data_file, dollar_rate, ",") == false)
	{
		std::cerr << "Error reading." << std::endl;
		data_file.close();
		bitcoin_wallet_file.close();
		return 1;
	}

	if (file_to_map(bitcoin_wallet_file, bitcoins, " | ") == false)
	{
		std::cerr << "Error reading." << std::endl;
		bitcoin_wallet_file.close();
		return 1;
	}

	if (dollar_rate.empty() || bitcoins.empty())
	{
		std::cerr << "Error: Incorrect Input" << std::endl;
		return 1;
	}

	//display_map(bitcoins, 1);//delete

	//display_map(dollar_rate, 100);

	//std::cout << "\n ----------------------- \n\n";

	//display_map(bitcoins, 1);

	//std::cout << "\n ##################################################### \n\n";

	std::map<std::string, double>::iterator itD;
	std::map<std::string, double>::iterator itD_last;

	for (std::map<std::string, double>::iterator itB = bitcoins.begin(); itB != bitcoins.end(); itB++)
	{
		itD = dollar_rate.begin();
		itD_last = dollar_rate.end();

		while (itD != dollar_rate.end())
		{
			if (itB->first < itD->first)
			{
				if (itD_last != dollar_rate.end()) //si ce n'est pas le premier tour et donc itD_last est bon
				{
					//std::cout << "Dollar rate date = " << itD_last->first << std::endl;
					check_and_calcul(itB->first, itB->second, itD_last->second); //itD_last
				}
				else //sinon c est le premier tour et on doit prendre itD et non last
				{
					//std::cout << "Dollar rate date = " << itD_last->first << std::endl;
					check_and_calcul(itB->first, itB->second, itD->second);
				}

				break;//??
			}
			itD_last = itD;
			itD++;
		}
		if (itD == dollar_rate.end())
			check_and_calcul(itB->first, itB->second, itD_last->second);
	}

	std::cout << std::endl;

	return 0;
}
