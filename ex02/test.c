
#include <cstring>
#include <iostream>
#include <vector>

int	main(int argc, char **argv)
{
	std::vector<int>	vec;

	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	int i = 1;

	while (argv[i])
	{
		vec.push_back(atoi(argv[i]));
		i++;
	}

	int middle = vec.size() / 2;

	//normalement recursif, pourquoi
	for (int i = 0; i < middle; i++)
		if (!(vec[i + middle] > vec[i]))
			std::swap(vec[i], vec[i + middle]);

	

	for (std::vector<int>::iterator i = vec.begin(); i != vec.end(); i++)
		std::cout << " " << *i;

	return 0;
}
