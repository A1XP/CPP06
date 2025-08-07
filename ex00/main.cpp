#include <iostream>
#include "ScalarConverter.hpp"

// int main(int argc, char* argv[])
// {
// 	if (argc != 2)
// 	{
// 		std::cout << "Usage: ./converter <literal>" << std::endl;
// 		return (1);
// 	}

// 	std::string input = argv[1];

// 	ScalarConverter::convert(input);

// 	return (0);
// }

int main()
{
	std::string command;

	while (true)
	{
		std::cout << "Enter <literal>: ";
		std::getline(std::cin, command);

		if (std::cin.eof())
		{
			std::cout << "EOF detected. Exit" << std::endl;
			break;
		}
		if (command == "EXIT")
		{
			std::cout << "Goodbye!" << std::endl;
			break;
		}
		else
		{
			ScalarConverter::convert(command);
		}
	}
	return (0);
}