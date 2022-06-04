#pragma once
#include "Account.h"

class PrivilegeAccount : public Account
{
	double overdraft;

public:
	PrivilegeAccount() = delete;
	PrivilegeAccount(int, const StringC&, const StringC&, const StringC&, const time_t&, double, double = 0);

	void display() const override;
	bool withdraw(double) override;

	Account* clone() const override;
};
