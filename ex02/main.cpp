#include <cstring>
#include <iostream>
#include <vector>

void	display(std::vector<int> vec, int range, int tiret, int display_range, int display_pendings)
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
		if (j == (range / 2) && tiret)
			std::cout << " -";
		if (j == range && display_pendings)
			std::cout << "     pending: ";
		//if (j == range && !display_pendings)
		//	std::cout << " _";
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

/* int	my_binary_search(std::vector<int> & vec, int range, int number)
{
	return 0;
}*/

bool	is_even(int nb)
{
	if (nb % 2 == 0)
		return true;
	return false;
}

void	move_element(std::vector<int> & vec, std::vector<int>::iterator from, std::vector<int>::iterator to)
{
	int tmp = *from;

	vec.erase(from);

	vec.insert(to, tmp);
}

//0, 1, 1, 3, 5, 11, 21, 43

void	johnson(std::vector<int> & vec, int range, char lettre)
{
	if (range == 1)
		std::cout << std::endl;

	std::cout << lettre << " ";
	display(vec, range, 1, 1, 1);

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
		//if (!(vec[i] > vec[i + middle]))
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

	if (range == vec.size() || range == vec.size() - 1)
		return;
	if (range == 8)
	{
		std::cout << "ENDDD\n";
		display(vec, range, 0, 0, 0);
		return;
	}

	std::cout << lettre << " ";


	display(vec, range, 1, 0, 0);

	int j = range ; // = middle?
	//std::cout << "R" << range << "J" << j << "\n";
	std::vector<int>::iterator it;

	//RAJOUTER la prise en compte des laisses de cote quand c est impair

	//while ((is_even(range) && j < range - 1) || (!is_even(range) && j < range - 2))
	
	int loop = 0;

	while (j < range * 2)
	{
		//lower_bound va trouver le nombre directement superieur dans la suite des nombres deja tries, ou le plus grand des nombres deja tries si vec[j] (le pounding en cours) est superieur a tous
		//middle - 1, -1 a tester
		it = std::lower_bound(vec.begin(), vec.begin() + (range - 1) + loop, vec[j]);

		//j est plus grand que tout le reste, vec.end() ne devrait jamais etre renvoye puisqu on ne donne jamais vec.end() en deuxieme argument (tests sur!)
		//si j == range c est que j est au debut des pendings et il doit donc rester a sa place
		if (it == vec.end() || (*it) < vec[j])
		{
			std::cout << "@ ";
			//if (j == range + loop)
			if (it + 1 == vec.begin() + j)
			{
				std::cout << "J" << j << " stay" << std::endl;
				j++;
				loop++;
				continue;
			}

			move_element(vec, vec.begin() + j, vec.begin() + range + loop);

			if (range != vec.size())
				move_element(vec, vec.begin() + j + (range * 2), vec.begin() + range + loop);

			//if range != vec.size() bouger symetriquement les pendings des couches superieurs
		}
		else
		{
			std::cout << "# ";
			move_element(vec, vec.begin() + j, it);

			if (range != vec.size())
				move_element(vec, vec.begin() + j + (range * 2), it + (range * 2));
			//if range != vec.size() bouger symetriquement les pendings des couches superieurs
		}

		std::cout << "J" << j << " ";
		display(vec, range, 1, 0, 0);

		//std::cout << "J[" << j << "] UNPREDICTABLE CASE" << std::endl;

		j++;
		loop++;
	}

	//display(vec, range, 1, 0);
	std::cout << "----------------\n";

}


/*
   int number;
   for (int i = middle; i < range; i++)
   {
   number = vec[i];
   vec.erase(vec.begin() + i);

//insertion

if (range != vec.size())
{
//same for the pendings
}
}
 */
/* ancien affichage des pendings
   std::cout << lettre << " ";

   for (int i = middle; i < (range - 1); i++)
   std::cout << vec[i] << " ";

   if (range % 2 != 0)
   std::cout << "[" << vec[range - 1] << "]" << std::endl;
   else
   std::cout << vec[range - 1] << std::endl;
 */
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
