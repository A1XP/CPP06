#include <iostream>
#include "Serializer.hpp"

int main()
{
	Data data;
	data._ds = "Hello, World!";
	data.di = 42;

	std::cout << "Address of data: " << &data << "\n";

	uintptr_t raw = Serializer::serialize(&data);
	std::cout << "Serialized uintptr_t raw in hex: 0x" 
			  << std::hex << raw << std::dec << "\n";
	std::cout << "Serialized uintptr_t raw : " 
			  << raw << std::dec << "\n";

	Data* ptr = Serializer::deserialize(raw);

	std::cout << "Deserialized pointer: " << ptr << "\n";

	if (ptr == &data)
	{

		std::cout << "Success: pointers are equal.\n";
		std::cout << "Data._ds = " << ptr->_ds << "\n";
		std::cout << "Data.di = " << ptr->di << "\n";
	}
	else
	{
		std::cout << "Error: pointers are NOT equal.\n";
	}

	return 0;
}
