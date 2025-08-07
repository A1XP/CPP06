#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits>
#include <exception>


bool ScalarConverter::isChar(const std::string& str)
{
	if (str.size() != 1)
		return (false);
	return (std::isprint(str[0]) && !std::isdigit(str[0]));
}

bool ScalarConverter::isInt(const std::string& str)
{
	size_t start = 0;
	if (str.empty())
		return (false);
	if (str[0] == '+' || str[0] == '-')
		start++;
	if (start == str.size())
		return (false);
	for (size_t i = start; i < str.size(); i++)
		if (!std::isdigit(str[i]))
			return (false);
	return (true);
}

bool ScalarConverter::isDouble(const std::string& str)
{
	size_t start = 0;
	if (str.empty())
		return (false);
	if (str[0] == '+' || str[0] == '-')
		start++;
	size_t pos = str.find('.', start);
	if (pos == std::string::npos)
		return (false);

	const std::string before = str.substr(start, pos - start);
	const std::string after = str.substr(pos + 1);

	if (before.empty() && after.empty())
		return (false);

	if (before.find('.') != std::string::npos || after.find('.') != std::string::npos)
		return (false);

	for (auto c : before)
		if (!std::isdigit(c))
			return (false);
	for (auto c : after)
		if (!std::isdigit(c))
			return (false);

	return (true);
}

bool ScalarConverter::isFloat(const std::string& str)
{
	if (str.size() < 2 || str.back() != 'f')
		return (false);
	std::string core = str.substr(0, str.size() - 1);
	return (isDouble(core));
}

bool ScalarConverter::isPseudoLiteral(const std::string& str)
{
	return (str == "nan" || str == "nanf" ||
		str == "-inf" || str == "+inf" ||
		str == "-inff" || str == "+inff");
}

ScalarConverter::LiteralType ScalarConverter::detectType(const std::string& str)
{
	if (isPseudoLiteral(str))
		return (PSEUDO);
	if (isChar(str))
		return (CHAR);
	if (isInt(str))
		return (INT);
	if (isFloat(str))
		return (FLOAT);
	if (isDouble(str))
		return (DOUBLE);
	return (INVALID);
}

void ScalarConverter::printChar(char value)
{
	if (std::isprint(value))
		std::cout << "char: '" << value << "'\n";
	else
		std::cout << "char: Non displayable\n";

	std::cout << "int: " << static_cast<int>(value) << "\n";
	std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(value) << "f\n";
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(value) << "\n";
}

void ScalarConverter::printInt(int value)
{
	if (std::isprint(static_cast<unsigned char>(value)))
		std::cout << "char: '" << static_cast<char>(value) << "'\n";
	else
		std::cout << "char: Non displayable\n";

	std::cout << "int: " << value << "\n";
	std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(value) << "f\n";
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(value) << "\n";
}

void ScalarConverter::printFloat(float value)
{
	if (std::isprint(static_cast<unsigned char>(value)))
		std::cout << "char: '" << static_cast<char>(value) << "'\n";
	else
		std::cout << "char: Non displayable\n";
	if (value >= std::numeric_limits<int>::max() ||
		value <= std::numeric_limits<int>::min())
		std::cout << "int: INT limit\n";
	else
		std::cout << "int: " << static_cast<int>(value) << "\n";
	std::cout << "float: " << std::fixed << std::setprecision(1) << value << "f\n";
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(value) << "\n";
}


void ScalarConverter::printDouble(double value)
{
	if (std::isprint(static_cast<unsigned char>(value)))
		std::cout << "char: '" << static_cast<char>(value) << "'\n";
	else
		std::cout << "char: Non displayable\n";

	if (value >= std::numeric_limits<int>::max() ||
		value <= std::numeric_limits<int>::min())
		std::cout << "int: INT limit\n";
	else
		std::cout << "int: " << static_cast<int>(value) << "\n";
	std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(value) << "f\n";
	std::cout << "double: " << std::fixed << std::setprecision(1) << value << "\n";
}

void ScalarConverter::printPseudo(const std::string& str)
{
	std::cout << "char: impossible\n";
	std::cout << "int: impossible\n";

	if (str.back() == 'f')
		std::cout << "float: " << str << "\n";
	else
		std::cout << "float: " << str << "f\n";

	if (str.back() == 'f')
		std::cout << "double: " << str.substr(0, str.size() - 1) << "\n";
	else
		std::cout << "double: " << str << "\n";
}

void ScalarConverter::convert(const std::string& str)
{
	try {
		switch (detectType(str))
		{
		case CHAR:
			printChar(str[0]);
			break;

		case INT:
		{
			int value = std::stoi(str);
			printInt(value);
			break;
		}

		case FLOAT:
		{
			std::string core = str.substr(0, str.size() - 1);
			float value = std::stof(core);
			printFloat(value);
			break;
		}

		case DOUBLE:
		{
			double value = std::stod(str);
			printDouble(value);
			break;
		}

		case PSEUDO:
			printPseudo(str);
			break;

		case INVALID:
		default:
			std::cout << "Type: invalid\n";
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Conversion error: " << e.what() << "\n";
	}
}
