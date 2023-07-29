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

void	display_vector(std::vector<int> & vec, int separe1, int separe2)
{
	std::vector<int>::iterator it = vec.begin();
	int i = 0;

	while (it != vec.end())
	{
		if (i == separe2 || i == separe1)
			std::cout << " - ";
		std::cout << *it << " ";
		it++;
		i++;
	}
	std::cout << std::endl;
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

	int jacob_index = 0;
	int real_index = (range * 2) - 1;
	int inserted = 0;

	int biggest = 0;

	while (loop < range)
	{
		std::cout << ">";
		//display(vec, range, 0, 0, 0);
		display_vector(vec, range + inserted, range * 2 + inserted);
		std::cout << "J" << jacob_index << " R" << real_index << "{" << vec[real_index] << "} L" << loop << " r" << range << std::endl; 

		//lower_bound va trouver le nombre directement superieur dans la suite des nombres deja tries, ou le plus grand des nombres deja tries si vec[j] (le pounding en cours) est superieur a tous //middle - 1, -1 a tester
		it = std::lower_bound(vec.begin(), vec.begin() + (range - 1) + loop, vec[real_index]);

		biggest = (*it < vec[real_index]) ? 1 : 0;
		int distance = std::distance(it + biggest, vec.begin() + real_index);

		vec.insert(it + biggest, vec[real_index]);
		inserted++;
		if (lettre != 'B' && lettre != 'A')
		{
		std::cout << "mirror: from " << real_index + (range * 2) + inserted << std::endl;
		//erreur : les nombres precedemment inserted peuvent etre a gauche ou droite de it, il faut l index precis de it
			move_element(vec, vec.begin() + real_index + (range * 2) + inserted, vec.begin() + real_index + (range * 2) + inserted - distance);//if (range != vec.size())
			}

		//display(vec, range, 0, 0, 0);
		loop++;

		jacob_index = get_next_jacobsthal_index(jacob_index);
		if (jacob_index >= range )
			jacob_index = range - 1;
		real_index = (range * 2) + inserted - 1 - jacob_index;

		display_vector(vec, range + inserted, range * 2 + inserted);
	}

	//DELETE THE INSERTED
	for (int k = 0; k < range; k++)
		vec.erase(vec.begin() + (range * 2));

	std::cout << "  ";
	display(vec, range, 0, 0, 0);

	std::cout << "----------------\n";

}

#include <cstdlib>

bool isSorted(const std::vector<int>& vec) {
	for (std::size_t i = 1; i < vec.size(); ++i) {
		if (vec[i-1] > vec[i]) {
			return false;
		}
	}
	return true;
}

#include <algorithm>

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

	std::cout << std::endl;

	if (vec.size() != saved_size)
		std::cout << "!! SIZE OF VECTOR CHANGED" << std::endl;
	else if (!isSorted(vec))
		std::cout << "NOT SORTED $$$$$$$$$$$$$$\n";
	else
		std::cout << "sorted\n";


	return 0;
}
