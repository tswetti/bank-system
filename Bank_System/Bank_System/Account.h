#pragma once

#include "StringC.h"
#include <ctime>

class Account
{
	int userId;
	StringC username;
	StringC password;

protected:
	StringC iban;
	double amount;
	time_t dateOfCreation;

public:
	Account() = delete;
	Account(int, const StringC&, const StringC&, const StringC&, const time_t&, double);

	virtual void display() const;
	double getBalance() const;
	void deposit(double);

	virtual bool withdraw(double) = 0;

	virtual Account* clone() const = 0;

	int getUserId() const;
	StringC getIban() const;
};
