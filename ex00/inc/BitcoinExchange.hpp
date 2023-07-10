#ifndef BITCOINEXCHANGE_CLASS_HPP
# define BITCOINEXCHANGE_CLASS_HPP

#include <iostream>
#include <string>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const std::string &name);
		BitcoinExchange(const BitcoinExchange &other);
   	   ~BitcoinExchange ();
		BitcoinExchange & operator=(const BitcoinExchange &other);

	private:
		std::string	_name;
	protected:
};

#endif /* BITCOINEXCHANGE_CLASS_HPP */
