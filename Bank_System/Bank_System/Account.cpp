#include "Account.h"
#include <iostream>

Account::Account(int id, const StringC& name, const StringC& pass, const StringC& iban, double amount, const time_t& date)
	: userId(id), username(name), password(pass), iban(iban), amount(amount), dateOfCreation(date){}

void Account::display() const
{
	std::cout << "IBAN: " << iban << std::endl;
	std::cout << "User id: " << userId << std::endl;
	std::cout << "Balance: " << amount << std::endl;
}

double Account::getBalance() const
{
	return amount;
}

void Account::deposit(double amount)
{
	this->amount += amount;
}