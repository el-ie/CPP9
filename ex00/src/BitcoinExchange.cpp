#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _name("default")
{
	std::cout << "BitcoinExchange default constructor" << std::endl;
}

BitcoinExchange::BitcoinExchange(const std::string &name) : _name(name)
{
	std::cout << "BitcoinExchange constructor" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	std::cout << "BitcoinExchange copy constructor" << std::endl;
	*this = other;
}

BitcoinExchange::~BitcoinExchange()
{
	std::cout << "BitcoinExchange destructor" << std::endl;
}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange &other)
{
	std::cout << "BitcoinExchange assignation operator" << std::endl;
	this->_name = other._name;
	return *this;
}

//void	BitcoinExchange::set_()
//void	BitcoinExchange::get_()
//void	BitcoinExchange::()
//void	BitcoinExchange::_()
