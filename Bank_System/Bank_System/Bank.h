#pragma once
#include "Customer.h"

#include "Account.h"
#include "NormalAccount.h"
#include "SavingsAccount.h"
#include "PrivilegeAccount.h"

#include "Transaction.h"

#include "Container.hpp"
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
	int getTransactionsSize() const;

	bool addCustomer(Customer*);
	bool deleteCustomer(int);

	void addAccount(Account*);
	bool deleteAccount(const StringC&);
	void deleteCustomersAccounts(int);

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

	int getCustomerIndexById(int) const;
	int getAccountIndexByIBAN(const StringC&) const;
	int getAccountIndexByUsername(const StringC&) const;
	int getCustomersMaxId() const;
	StringC getIbanByUsernamePass(const StringC&, const StringC&) const;
	StringC getIbanAfterLogin() const;
};
