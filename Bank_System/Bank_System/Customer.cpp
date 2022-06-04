#include "Customer.h"
#include "StringC.h"

Customer::Customer(int id, const StringC& name, const StringC& address) : id(id), name(name), address(address) {}

int Customer::getId() const
{
	return id;
}

StringC Customer::getName() const
{
	return name;
}

StringC Customer::getAddress() const
{
	return address;
}

void Customer::display() const
{
	std::cout << "Id: " << id << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Address: " << address << std::endl;
}

Customer* Customer::clone() const
{
	return new Customer(*this);
}