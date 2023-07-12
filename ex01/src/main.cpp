#include <iostream>
#include <string>

#include <stack>

#define PLUS 43
#define MINUS 45
#define DIVI 47
#define MULTI 42

/*
enum OPERATOR {
	PLUS = -42,
	MINUS,
	MULTI,
	DIVI,
};
*/

bool	is_operator(int c)
{
	if (c == '+' || c == '-')
		return true;
	if (c == '*' || c == '/')
		return true;
	return false;
}

bool	check_input(std::string input)
{
	if (is_operator(input[0]) || !is_operator(input[input.size() - 1]))
		return false;
		
	int nb_count = 0;
	int operators_count = 0;

	for (int i = 0; input[i]; i++)
	{
		if (input[i] < '0' && input[i] > '9')
			if (!is_operator(input[i]))
				return false;

		if (input[i] < '0' && input[i] > '9')
			nb_count++;
		if (is_operator(input[i]))
			operators_count++;
	}

	if (nb_count != (operators_count - 1))
		return false;

	return true;
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: bad number of arguments" << std::endl;
		return 1;
	}

	if (!check_input(argv[1]))
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	std::stack<double>	RPN;

	std::string		line = argv[1];

	for (int i = line.size() - 1; i >= 0; i--)
	{
		if (!is_operator(argv[1][i]))
			RPN.push(static_cast<double>(argv[1][i] - 48));
		else
			RPN.push(static_cast<double>(argv[1][i]));

	}

	///*
	while (!RPN.empty())
	{
		if (RPN.top() >= 0 && RPN.top() <= 9)
			std::cout << "char [" << static_cast<char>(RPN.top() + 48) << "]" << std::endl;
		else
			std::cout << "char [" << static_cast<char>(RPN.top()) << "]" << std::endl;
		RPN.pop();
	}
	//*/

	double result = 0;
	int current = 0;
	bool	first_loop = true;

	while (!RPN.empty())
	{
		std::cout << "char [" << RPN.top() << "]" << std::endl;

		current = RPN.top();

		//if (!is_operator(current)

		if (is_operator(current) && !first_loop)
		{
			if (current == '+')
				result += current;
			if (current == '-')
				result -= current;
			if (current == '*')
				result *= current;
			if (current == '/')
				result /= current;
		}

		RPN.pop();
		first_loop = false;
	}

	return 0;
}
