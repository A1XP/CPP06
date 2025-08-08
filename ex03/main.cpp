#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <random>

Base* generate(void)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> distrib(0, 2);

	int classNum = distrib(gen);

	if (classNum == 0)
		return(new A());
	else if (classNum == 1)
		return(new B());
	else 
		return(new C());
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

void identify(Base& p)
{
	try {
		dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	} catch (std::bad_cast&) {}

	try {
		dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	} catch (std::bad_cast&) {}

	try {
		dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	} catch (std::bad_cast&) {}
}

int main()
{
	Base* ptr = generate();

	std::cout << "Identify by pointer: ";
	identify(ptr);

	std::cout << "Identify by reference: ";
	identify(*ptr);

	delete ptr;
	return 0;
}