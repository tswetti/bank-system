#include "SavingsAccount.h"

SavingsAccount::SavingsAccount(int id, const StringC& name, const StringC& pass, const StringC& iban, const time_t& date, double interest, double amount)
	: Account(id, name, pass, iban, date, amount)
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