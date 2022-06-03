#pragma once
#include "Account.h"
#include <iostream>

class NormalAccount : public Account
{
public:
	NormalAccount() = delete;
	NormalAccount(int, const StringC&, const StringC&, const StringC&, double, const time_t&);

	void display() const override;
	bool withdraw(double) override;

	Account* clone() const override;
};