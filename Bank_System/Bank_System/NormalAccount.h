#pragma once
#include "Account.h"
#include <iostream>

class NormalAccount : public Account
{
public:
	NormalAccount() = delete;
	NormalAccount(int, const StringC&, const StringC&, const StringC&, const time_t&, double = 0);

	void display() const override;
	bool withdraw(double) override;

	Account* clone() const override;
};