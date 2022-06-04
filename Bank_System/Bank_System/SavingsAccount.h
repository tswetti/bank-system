#pragma once
#include "Account.h"
#include <iostream>

class SavingsAccount : public Account
{
	double interestRate;

public:
	SavingsAccount() = delete;
	SavingsAccount(int, const StringC&, const StringC&, const StringC&, const time_t&, double, double = 0);

	void display() const override;
	bool withdraw(double) override;

	Account* clone() const override;
};
