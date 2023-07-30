#include <cstring>
#include <iostream>
#include <vector>

//if nb is jacobsthal it will return the next upper jacobsthal
int	get_upper_jacobsthal(int nb)
{
	if (nb < 1)
		return 1;
	if (nb < 3)
		return 3;

	int jm2 = 1;
	int jm1 = 3;
	int tmp;

	while (nb >= (jm2 * 2) + jm1)
	{
		tmp = jm1;
		jm1 = jm1 + (2 * jm2);
		jm2 = tmp;
	}

	return ((jm2 * 2) + jm1);
}

bool	is_jacobsthal_number(int nb)
{

	if (nb < 5 && (nb == 0 || nb == 1 || nb == 3))
		return true;

	int jm2 = 1;
	int jm1 = 3;
	int tmp;

	while (nb > (jm2 * 2) + jm1)
	{
		tmp = jm1;
		jm1 = jm1 + (2 * jm2);
		jm2 = tmp;
	}

	if (nb == (jm2 * 2) + jm1)
		return true;
	return false;
}

int	get_next_jacobsthal_index(int last_index)
{

	if (!is_jacobsthal_number(last_index))
		return (last_index - 1);

	return (get_upper_jacobsthal(get_upper_jacobsthal(last_index)) - 1);

}

void	display(std::vector<int> vec, int range, int tiret, int display_range, int display_pendings)
{
	if (range == 1)
	{
		std::cout << "   ==" << vec[0] << "==" << std::endl;
		return;
	}

	int j = 0;
	while (j < (range * 2) && j < vec.size())
	{
		if (j == (range / 2) && tiret)
			std::cout << " -";
		if (j == range && display_pendings)
			std::cout << "     pending: ";
		if (j == range && !display_pendings)
			std::cout << " _";
		if (j == (range - 1) && range % 2 != 0)
			std::cout << " {" << vec[j] << "}";
		else
			std::cout << " " << vec[j];

		j++;
	}
	if (display_range)
		std::cout << "     range(" << range << ")";
	std::cout << std::endl;
}

bool	is_even(int nb)
{
	if (nb % 2 == 0)
		return true;
	return false;
}

void	move_element(std::vector<int> & vec, std::vector<int>::iterator from, std::vector<int>::iterator to)
{
	if (from == vec.end())//delete
	{
		std::cerr << "ERROR move element vec.end" << std::endl;
		return;
	}
	int tmp = *from;

	vec.erase(from);

	vec.insert(to, tmp);
}

void	johnson(std::vector<int> & vec, int range, char lettre)
{
	if (range == 1)
		std::cout << std::endl;

	std::cout << lettre << " ";
	display(vec, range, 1, 1, 1);

	if (range == 1)
	{
		std::cout << std::endl;
		return;
	}

	int middle = (range / 2); 

	for (int i = 0; i < middle; i++)
	{
		if ((vec[i] > vec[i + middle]))
		{
			std::swap(vec[i], vec[i + middle]);

			if (range != vec.size())
				std::swap(vec[i + range], vec[i + middle + range]);

		}
	}

	std::cout << "  ";
	display(vec, range, 1, 1, 1);

	//----------------------------------
	johnson(vec, range / 2, lettre + 1);
	//----------------------------------

	std::vector<int>::iterator it;

	if (range % 2 != 0 && range > 2) //range > 2 securite??
	{
		//std::cout << "          "; display(vec, range, 0, 1, 0); std::cout << "          tri du restant\n";
		it = std::lower_bound(vec.begin(), vec.begin() + (range - 2), vec[range - 1]);
		if (vec[range - 1] <= *it) //add//it != vec.end()
		{
			move_element(vec, vec.begin() + range - 1, it);
			if (range != vec.size())
				move_element(vec, vec.begin() + (range * 2) - 1, it + range);
		}
		//std::cout << "          "; display(vec, range, 0, 1, 0);
	}

	if (range == vec.size())
	{
		std::cout << "ENDDD\n";
		display(vec, range, 0, 0, 0);
		return;
	}

	std::cout << lettre << " ";

	display(vec, range, 0, 1, 0);

	int j = range;
	int loop = 0;

	int index = 0;

	while (j < range * 2)
	{
	/*
		std::cout << ">";
		display(vec, range, 0, 0, 0);
		std::cout << "J" << j << " " << "{" << vec[j] << "} " ; 
	*/

		//lower_bound va trouver le nombre directement superieur dans la suite des nombres deja tries, ou le plus grand des nombres deja tries si vec[j] (le pounding en cours) est superieur a tous //middle - 1, -1 a tester
		it = std::lower_bound(vec.begin(), vec.begin() + (range - 1) + loop, vec[j]);
		//it = std::lower_bound(vec.begin(), vec.begin() + (range - 1) + loop, vec[range + index]);

		//if (*it >= vec[range + index])
		if (*it >= vec[j])
		{
			move_element(vec, vec.begin() + j, it);
			if (range * 2 != vec.size() && range * 2 != vec.size() - 1)
				move_element(vec, vec.begin() + j + (range * 2), it + (range * 2));//if (range != vec.size())
		}

		//display(vec, range, 0, 0, 0);
		j++;
		loop++;
		
		//index = get_next_jacobsthal_index(index);
	}

	std::cout << "  ";
	display(vec, range, 0, 0, 0);

	std::cout << "----------------\n";

}

#include <cstdlib>
#include <algorithm>

bool isSorted(const std::vector<int>& vec) {
    for (std::size_t i = 1; i < vec.size(); ++i) {
        if (vec[i-1] > vec[i]) {
            return false;
        }
    }
    return true;
}
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

	int saved_size = vec.size();

	std::vector<int> copy = vec;
	std::sort(copy.begin(), copy.end());

	/*
	   for (std::vector<int>::iterator it = copy.begin(); it != copy.end(); it++)
	   std::cout << *it << " ";
	   std::cout << std::endl;
	 */

	char lettre = 'A';
	johnson(vec, vec.size(), lettre);

	if (!std::equal(copy.begin(), copy.end(), vec.begin()))
	{
		std::cout << "ERROR the vectors are not equal" << std::endl;
		return 1;
	}
	else
		std::cout << "vectors are equal +++++" << std::endl;

	std::cout << std::endl;

	if (vec.size() != saved_size)
		std::cout << "!! SIZE OF VECTOR CHANGED" << std::endl;
	else if (!isSorted(vec))
		std::cout << "NOT SORTED $$$$$$$$$$$$$$\n";
	else
		std::cout << "sorted\n";


	return 0;
}
