#include "Account.h"
#include <iostream>

Account::Account(int id, const StringC& name, const StringC& pass, const StringC& iban, const time_t& date, double amount = 0)
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

int Account::getUserId() const
{
	return userId;
}

StringC Account::getIban() const
{
	return iban;
}

StringC Account::getUsername() const
{
	return username;
}

bool Account::isLoggedIn(const StringC& user, const StringC& pass) const
{
	return user == username && pass == password;
}