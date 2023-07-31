#include <cstring>
#include <iostream>
#include <vector>

//delete ? :
#include <cstdlib>
#include <algorithm>
#include <climits>

int	get_upper_jacobsthal(int nb)
{
	if (nb < 0)
		return 0;
	if (nb == 0)
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

bool	is_even(int nb)
{
	if (nb % 2 == 0)
		return true;
	return false;
}

void	move_element(std::vector<int> & vec, std::vector<int>::iterator from, std::vector<int>::iterator to)
{
	if (from == vec.end() || to == vec.end() || from == to)
		return;

	int tmp = *from;

	vec.erase(from);

	vec.insert(to, tmp);
}

void	johnson(std::vector<int> & vec, int range)
{
	int size = range;
	int middle = (range / 2); 

	if (range == 1)
		return;

	for (int i = 0; i < middle; i++)
	{
		if ((vec[i] > vec[i + middle]))
		{
			std::swap(vec[i], vec[i + middle]);

			while (size != vec.size())
			{
				std::swap(vec[i + size], vec[i + middle + size]);
				size += range;
			}

		}
	}

	//----------------------------------
	johnson(vec, range / 2);
	//----------------------------------

	if (range == vec.size())
		return;

	std::vector<int>::iterator it;
	int loop = 0;
	int jacob_index = 0;
	int real_index = range * 2 - 1;
	int shift = 0;
	int upper = 0;
	int offset_right;

	while (loop < range)
	{

		if (loop != 0)
		{
			jacob_index = get_next_jacobsthal_index(jacob_index);
			while (jacob_index >= range)
			{
				shift++;
				jacob_index = get_next_jacobsthal_index(jacob_index);
			}
			upper = get_upper_jacobsthal(jacob_index);
			upper -= shift;
			real_index = (range * 2 - 1) - jacob_index - (upper - jacob_index - 1) + loop;
		}

		it = std::lower_bound(vec.begin(), vec.begin() + (range - 1) + loop, vec[real_index]);
		offset_right = (*it < vec[real_index]) ? 1 : 0;
		move_element(vec, vec.begin() + real_index, it + offset_right);
		size = range * 2;
		while (size != vec.size())
		{
			move_element(vec, vec.begin() + real_index + size, it + offset_right + size);
			size += range * 2;
		}
		loop++;
	}
}

int	get_next_power_two(int nb)
{
	if (nb < 2)
		return 0;

	int result = 2;

	while (result < nb)
		result *= 2;

	return result;
}

void	display_container(std::vector<int> & vec)
{
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

bool is_sorted(const std::vector<int>& vec) {
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
	if (argc == 2)
	{
		std::cerr << "Can't sort only one element." << std::endl;
		return 1;
	}

	int i = 1;

	while (argv[i])
	{
		if (std::atoi(argv[i]) < 0)
		{
			std::cerr << "Error: negative number" << std::endl;
			return 1;
		}
		vec.push_back(std::atoi(argv[i]));
		i++;
	}

	std::cout << "Before:   ";
	display_container(vec);

	int saved_size = vec.size();
	int next_power_two = get_next_power_two(vec.size());

	while (vec.size() < next_power_two)
		vec.push_back(INT_MAX);

	johnson(vec, vec.size());

	vec.erase(vec.begin() + saved_size, vec.end());

	std::cout << "After:   ";
	display_container(vec);

	/*
	if (!is_sorted(vec))
		std::cout << "\n NOT SORTED \n";
	else
		std::cout << "\nsorted\n";
	*/

	return 0;
}
