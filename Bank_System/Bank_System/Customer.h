#pragma once

#include "StringC.h"
#include <iostream>

class Customer
{
	int id;
	StringC name;
	StringC address;

public:
	Customer() = delete;
	Customer(int, const StringC&, const StringC&);

	int getId() const;
	StringC getName() const;
	StringC getAddress() const;

	void display() const;

	Customer* clone() const;
};
