#include "SavingsAccount.h"

SavingsAccount::SavingsAccount(int id, const StringC& name, const StringC& pass, const StringC& iban, double amount, const time_t& date, double interest)
	: Account(id, name, pass, iban, amount, date)
{
	interestRate = interest;
}

void SavingsAccount::display() const
{
	std::cout << "Account type: savings account" << std::endl;
	Account::display();
	std::cout << "Interest rate: " << interestRate << "%" << std::endl;
}

bool SavingsAccount::withdraw(double amount)
{
	return false;
}

Account* SavingsAccount::clone() const
{
	return new SavingsAccount(*this);
}