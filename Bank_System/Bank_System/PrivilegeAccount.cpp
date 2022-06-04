#include "PrivilegeAccount.h"
#include <iostream>

PrivilegeAccount::PrivilegeAccount(int id, const StringC& name, const StringC& pass, const StringC& iban, const time_t& date, double overdraft, double amount)
	: Account(id, name, pass, iban, date, amount)
{
	this->overdraft = overdraft;
}

void PrivilegeAccount::display() const
{
	std::cout << "Account type: privilege account" << std::endl;
	Account::display();
	std::cout << "Overdraft: " << overdraft << std::endl;
}

bool PrivilegeAccount::withdraw(double amount)
{
	if (this->amount + overdraft < amount)
		return false;

	this->amount -= amount;
	return true;
}

Account* PrivilegeAccount::clone() const
{
	return new PrivilegeAccount(*this);
}