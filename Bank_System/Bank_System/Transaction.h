#pragma once
#include "StringC.h"
#include <ctime>
#include <iostream>

class Transaction
{
	time_t time;
	StringC description;

public:
	Transaction() = delete;
	Transaction(const time_t&, const StringC&);

	bool exportToFile(std::ofstream&) const;

	void display() const;

	Transaction* clone() const;
};
