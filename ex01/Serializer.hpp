#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <string>
#include <cstdint>

struct Data
{
	std::string _ds;
	int	di;
};

class Serializer
{
public:
	static uintptr_t serialize(Data* ptr);
	static Data* deserialize(uintptr_t raw);
private:
	Serializer() = default;
	~Serializer() = default;
	Serializer(const Serializer& other) = default;
	Serializer& operator=(const Serializer& other) = default;
};

#endif
