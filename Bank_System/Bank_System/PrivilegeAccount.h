#pragma once
#include "Account.h"

class PrivilegeAccount : public Account
{
	double overdraft;

public:
	PrivilegeAccount() = delete;
	PrivilegeAccount(int, const StringC&, const StringC&, const StringC&, double, const time_t&, double);

	void display() const override;
	bool withdraw(double) override;

	Account* clone() const override;
};
