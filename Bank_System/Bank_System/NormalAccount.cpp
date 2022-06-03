#include "NormalAccount.h"

NormalAccount::NormalAccount(int id, const StringC& name, const StringC& pass, const StringC& iban, double amount, const time_t& date)
	: Account(id, name, pass, iban, amount, date) {}

void NormalAccount::display() const
{
	std::cout << "Account type: normal account" << std::endl;
	Account::display();
}

bool NormalAccount::withdraw(double amount)
{
	if (this->amount < amount)
		return false;

	this->amount -= amount;
	return true;
}

Account* NormalAccount::clone() const
{
	return new NormalAccount(*this);
}