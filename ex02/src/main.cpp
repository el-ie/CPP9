#include <cstring>
#include <iostream>
#include <vector>
#include <deque>

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

template <typename container>
void	move_element(container & sequence, int real_index, typename container::iterator to)
{
	typename container::iterator from = sequence.begin() + real_index;

	if (from == sequence.end() || to == sequence.end() || from == to)
		return;

	int tmp = *from;

	sequence.insert(to, tmp);
	sequence.erase(sequence.begin() + real_index + 1);

}

template <typename container>
int	get_index(container & sequence, typename container::iterator it)
{
	int i = 0;
	while (sequence.begin() + i != it)
		i++;
	return i;
}

template <typename container>
void	johnson(container & sequence, int range)
{
	int size = range;
	int middle = (range / 2); 

	if (range == 1)
		return;

	for (int i = 0; i < middle; i++)
	{
		if ((sequence[i] > sequence[i + middle]))
		{
			std::swap(sequence[i], sequence[i + middle]);

			while (size != sequence.size())
			{
				std::swap(sequence[i + size], sequence[i + middle + size]);
				size += range;
			}

		}
	}

	//----------------------------------
	johnson(sequence, range / 2);
	//----------------------------------

	if (range == sequence.size())
		return;

	typename container::iterator it;
	int loop = 0;
	int jacob_index = 0;
	int real_index = range * 2 - 1;
	int shift = 0;
	int upper = 0;
	int offset_right;

	int target = 0;

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
		it = std::lower_bound(sequence.begin(), sequence.begin() + (range - 1) + loop, sequence[real_index]);
		offset_right = (*it < sequence[real_index]) ? 1 : 0;
		target = get_index(sequence, it);
		move_element(sequence, real_index, it + offset_right);
		size = range * 2;
		while (size != sequence.size())
		{
			//move_element(sequence, sequence.begin() + real_index + size, it + offset_right + size);
			move_element(sequence, real_index + size, sequence.begin() + target + offset_right + size);
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

template <typename container>
void	display_container(container & sequence)
{
	for (typename container::iterator it = sequence.begin(); it != sequence.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

template <typename container>
bool is_sorted(container & sequence) {
	for (std::size_t i = 1; i < sequence.size(); ++i) {
		if (sequence[i-1] > sequence[i]) {
			return false;
		}
	}
	return true;
}

int	err_log(std::string str)
{
	std::cerr << str << std::endl;
	return 1;
}

bool	correct_characters(char *str)
{
	for (int i = 0; str[i]; i++)
		if (str[i] < '0' || str[i] > '9')
			return false;
	return true;
}

int	main(int argc, char **argv)
{
	std::vector<int> vec;

	if (argc < 2)
		return (err_log("Error"));
	
	if (argc == 2)
		return(err_log("Can't sort only one element."));

	int i = 1;

	while (argv[i])
	{
		if (!correct_characters(argv[i]))
			return (err_log("Error: Bad input.")); 
		if (std::atoi(argv[i]) < 0)
			return (err_log("Error: negative number.")); 
		vec.push_back(std::atoi(argv[i]));
		i++;
	}

	//if (is_sorted(vec))
		//return (err_log("Container already sorted."));

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

	   if (!is_sorted(vec))
	   std::cout << "\n NOT SORTED \n";
	   else
	   std::cout << "\nsorted\n";

	return 0;
}
