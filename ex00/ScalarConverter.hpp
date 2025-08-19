#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter
{
public:
	static void convert(const std::string& str);
private:
	enum LiteralType {
		CHAR,
		INT,
		FLOAT,
		DOUBLE,
		PSEUDO,
		INVALID
	};

	ScalarConverter() = default;
	~ScalarConverter() = default;
	ScalarConverter(const ScalarConverter& other) = default;
	ScalarConverter& operator=(const ScalarConverter& other) = default;

	static bool isChar(const std::string& str);
	static bool isInt(const std::string& str);
	static bool isFloat(const std::string& str);
	static bool isDouble(const std::string& str);
	static bool isPseudoLiteral(const std::string& str);

	static LiteralType detectType(const std::string& str);

	static void printChar(char value);
	static void printInt(int value);
	static void printFloat(float value);
	static void printDouble(double value);
	static void printPseudo(const std::string& str);
};

#endif
