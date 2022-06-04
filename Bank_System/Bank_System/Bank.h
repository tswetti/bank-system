#pragma once
#include "Customer.h"

#include "Account.h"
#include "NormalAccount.h"
#include "SavingsAccount.h"
#include "PrivilegeAccount.h"

#include "Transaction.h"

#include "Container.h"
#include "StringC.h"

#include <iostream>
#include <ctime>

class Bank
{
	StringC name;
	StringC address;
	Container<Customer> customers;
	Container<Account> accounts;
	Container<Transaction> log;

public:
	Bank();
	Bank(const StringC&, const StringC&);

	void setName(const StringC&);
	void setAddress(const StringC&);

	int getCustomersSize() const;
	int getAccountsSize() const;

	bool addCustomer(const Customer*);
	bool deleteCustomer(int);

	bool addAccount(const Account*);
	bool deleteAccount(const StringC&);
	bool deleteCustomersAccounts(int);

	int getCustomerIndexById(int) const;
	int getAccountIndexByIBAN(const StringC&) const;

	void listCustomers() const;
	void listAccounts() const;
	void listCustomerAccount(int) const;
	void listTransactions() const;

	bool exportLog(std::ofstream&) const;

	bool transfer(const StringC&, const StringC&, double);
	bool withdraw(const StringC&, double);
	bool deposit(const StringC&, double);

	void display() const;

	void addCustomerFromUserInput();
	void deleteCustomerFromUserInput();
	void addAccountFromUserInput();
	void deleteAccountFromUserInput();

	void listCustomerAccFromUserInput() const;

	void withdrawFromUserInput();
	void depositFromUserInput();
	void transferFromUserInput();
};
