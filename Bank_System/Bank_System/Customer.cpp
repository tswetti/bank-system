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