#include <cstring>
#include <iostream>
#include <vector>

void	display(std::vector<int> vec, int range)
{

	if (range == 1)
	{
		std::cout << "   ==" << vec[0] << "==" << std::endl;
		return;
	}

	int j = 0;
	//for (std::vector<int>::iterator i = vec.begin(); i != vec.end(); i++)
	while (j < (range * 2) && j < vec.size())
	{
		if (j == (range / 2))
			std::cout << " -";
		if (j == range)
			std::cout << "     pending: ";
		if (j == (range - 1) && range % 2 != 0)
			std::cout << " {" << vec[j] << "}";
		else
			std::cout << " " << vec[j];

		j++;
	}
	std::cout << std::endl;
}

void	johnson(std::vector<int> & vec, int range, char lettre)
{
	if (range == 1)
		std::cout << std::endl;

	std::cout << lettre << " ";
	display(vec, range);


	if (range == 1)
	{
		std::cout << std::endl;
		//std::cout << "      ------------------" << std::endl;
		//std::cout << "            pending:" << std::endl;
		return;
	}

	int middle = (range / 2); 

	for (int i = 0; i < middle; i++)
	{
		if (!(vec[i] > vec[i + middle]))
		{
			std::swap(vec[i], vec[i + middle]);

			if (range != vec.size())
				std::swap(vec[i + range], vec[i + middle + range]);

		}
	}

	std::cout << "  ";
	display(vec, range);

	johnson(vec, range / 2, lettre + 1);

	std::cout << lettre << " ";
	display(vec, range);

/*
	std::cout << lettre << " ";

	for (int i = middle; i < (range - 1); i++)
		std::cout << vec[i] << " ";

	if (range % 2 != 0)
		std::cout << "[" << vec[range - 1] << "]" << std::endl;
	else
		std::cout << vec[range - 1] << std::endl;
*/

}

#include <cstdlib>

int	main(int argc, char **argv)
{
	std::vector<int> vec;

	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	int i = 1;

	while (argv[i])
	{
		vec.push_back(std::atoi(argv[i]));
		i++;
	}

	//vec.insert(vec.begin() + 1, 14);

	char lettre = 'A';
	johnson(vec, vec.size(), lettre);

	std::cout << std::endl;

	//int middle = vec.size() / 2;

	/* normalement recursif, pourquoi
	   for (int i = 0; i < middle; i++)
	   if (!(vec[i + middle] > vec[i]))
	   std::swap(vec[i], vec[i + middle]); */


	return 0;
}
