#include "Bank.h"

Bank::Bank() : name(), address() {}

Bank::Bank(const StringC& name, const StringC& address) : name(name), address(address) {}

void Bank::setName(const StringC& name)
{
	this->name = name;
}

void Bank::setAddress(const StringC& address)
{
	this->address = address;
}

int Bank::getCustomersSize() const
{
	return customers.getSize();
}

int Bank::getAccountsSize() const
{
	return accounts.getSize();
}

bool Bank::addCustomer(Customer* c)
{
	if (getCustomerIndexById(c->getId()) != -1)
		return false;

	customers.add(c);

	time_t timer = time(NULL);

	StringC tDescr = "Added customer with id ";
	tDescr.concat(c->getId());
	tDescr.concat(".");

	log.add(new Transaction(timer, tDescr));
}

bool Bank::deleteCustomer(int id)
{
	int index = getCustomerIndexById(id);

	if (!customers.deleteAt(index))
		return false;

	deleteCustomersAccounts(id);

	time_t timer = time(NULL);

	StringC tDescr = "Deleted customer with id ";
	tDescr.concat(id);
	tDescr.concat(".");

	log.add(new Transaction(timer, tDescr));

	return true;
}

void Bank::addAccount(Account* a)
{
	// validation is in addAccountByUserInput

	accounts.add(a);

	time_t timer = time(NULL);

	StringC tDescr = "Created account with IBAN: ";
	tDescr.concat(a->getIban());
	tDescr.concat(".");

	log.add(new Transaction(timer, tDescr));
}

bool Bank::deleteAccount(const StringC& iban)
{
	int index = getAccountIndexByIBAN(iban);

	if (!accounts.deleteAt(index))
		return false;

	time_t timer = time(NULL);

	StringC tDescr = "Deleted account with IBAN ";
	tDescr.concat(iban);
	tDescr.concat(".");

	log.add(new Transaction(timer, tDescr));

	return true;
}

void Bank::deleteCustomersAccounts(int id)
{
	for (int i = 0; i < accounts.getSize(); i++)
	{
		if (accounts.getAt(i)->getUserId() == id)
		{
			accounts.deleteAt(i);
			i--;
		}
	}
}

int Bank::getCustomerIndexById(int id) const
{
	for (int i = 0; i < customers.getSize(); i++)
	{
		if (customers.getAt(i)->getId() == id)
			return i;
	}

	return -1;
}

int Bank::getAccountIndexByIBAN(const StringC& iban) const
{
	for (int i = 0; i < accounts.getSize(); i++)
	{
		if (accounts.getAt(i)->getIban() == iban)
			return i;
	}

	return -1;
}

int Bank::getAccountIndexByUsername(const StringC& username) const
{
	for (int i = 0; i < accounts.getSize(); i++)
	{
		if(accounts.getAt(i)->getUsername()==username)
			return i;
	}

	return -1;
}

StringC Bank::getIbanByUsernamePass(const StringC & username, const StringC & pass) const
{
	for (int i = 0; i < accounts.getSize(); i++)
	{
		if (accounts.getAt(i)->isLoggedIn(username, pass))
			return accounts.getAt(i)->getIban();
	}

	return StringC();
}

StringC Bank::getIbanAfterLogin() const
{
	StringC username, pass;

	std::cout << "Username: ";
	std::cin >> username;

	std::cout << "Password: ";
	std::cin >> pass;

	std::cin.ignore();

	return getIbanByUsernamePass(username, pass);
}

void Bank::listCustomers() const
{
	customers.print();
}

void Bank::listAccounts() const
{
	accounts.print();
}

void Bank::listCustomerAccount(int id) const
{
	int accountsCnt = 0;

	for (int i = 0; i < accounts.getSize(); i++)
	{
		if (accounts.getAt(i)->getUserId() == id)
		{
			std::cout << ++accountsCnt << std::endl;
			accounts.getAt(i)->display();
			std::cout << std::endl;
		}
	}
}

void Bank::listTransactions() const
{
	log.print();
}

bool Bank::exportLog(std::ofstream& ofs) const
{
	if (!ofs.is_open())
		return false;

	for (int i = 0; i < log.getSize(); i++)
	{
		log.getAt(i)->exportToFile(ofs);
		ofs << std::endl;
	}
	return true;
}

bool Bank::transfer(const StringC& fromIban, const StringC& toIban, double amount)
{
	if (fromIban == toIban)
		return false;

	int iFrom, iTo;

	iFrom = getAccountIndexByIBAN(fromIban);
	iTo = getAccountIndexByIBAN(toIban);
	
	if (iFrom == -1 || iTo == -1)
		return false;

	if (!accounts.getAt(iFrom)->withdraw(amount))
		return false;

	accounts.getAt(iTo)->deposit(amount);

	time_t timer = time(NULL);

	StringC tDescr = "Deposit from account with IBAN: ";
	tDescr.concat(fromIban);
	tDescr.concat(" to account with IBAN: ");
	tDescr.concat(toIban);
	tDescr.concat(".");

	log.add(new Transaction(timer, tDescr));

	return true;
}


bool Bank::withdraw(const StringC& iban, double amount)
{
	int index = getAccountIndexByIBAN(iban);

	if (index == -1)
		return false;

	if (!accounts.getAt(index)->withdraw(amount))
		return false;

	time_t timer = time(NULL);

	StringC tDescr = "Withdrawal from account with IBAN: ";
	tDescr.concat(iban);
	tDescr.concat(".");

	log.add(new Transaction(timer, tDescr));

	return true;
}

bool Bank::deposit(const StringC& iban, double amount)
{
	int index = getAccountIndexByIBAN(iban);

	if (index == -1)
		return false;

	accounts.getAt(index)->deposit(amount);

	time_t timer = time(NULL);

	StringC tDescr = "Deposit to account with IBAN: ";
	tDescr.concat(iban);
	tDescr.concat(".");

	log.add(new Transaction(timer, tDescr));

	return true;
}

void Bank::display() const
{
	std::cout << "Name: " << name << std::endl;
	std::cout << "Address: " << address << std::endl;
	std::cout << "Customers: " << getCustomersSize() << std::endl;
	std::cout << "Accounts: " << getAccountsSize() << std::endl;
}

void Bank::addCustomerFromUserInput()
{
	StringC name, address;

	std::cout << "Customer name: ";
	name.getline(std::cin);

	std::cout << "Customer address: ";
	address.getline(std::cin);

	int customerId = getCustomersSize() + 1;

	Customer* c = new Customer(customerId, name, address);

	if (addCustomer(c))
	{
		std::cout << "Adding this customer was unsuccessful." << std::endl;
		return;
	}
	std::cout << "Customer with id (" << customerId << ") added successfully." << std::endl;
}

void Bank::deleteCustomerFromUserInput()
{
	int id;
	std::cout << "Customer id: ";
	std::cin >> id;
	std::cin.ignore();

	if (!deleteCustomer(id))
	{
		std::cout << "Invalid id. \nDeleting this customer was unsuccessful." << std::endl;
		return;
	}
	std::cout << "Customer deleted successfully." << std::endl;
}

void Bank::addAccountFromUserInput()
{
	int id;
	StringC username, password, iban, type;

	std::cout << "User id: ";	// adding by Customer's unique field
	std::cin >> id;

	if (getCustomerIndexById(id) == -1)
	{
		std::cout << "Invalid customer id. \nAdding this account was unsuccessful." << std::endl;
		return;
	}

	std::cout << "Username: ";
	std::cin >> username;

	int userIndex = getAccountIndexByUsername(username);

	if (userIndex != -1)
	{
		std::cin.ignore();
		std::cout << "Username is taken." << std::endl;
		return;
	}

	std::cin.ignore();
	std::cout << "Password: ";
	password.getline(std::cin);

	std::cout << "IBAN: ";
	std::cin >> iban;

	if (getAccountIndexByIBAN(iban) != -1)
	{
		std::cout << "IBAN is taken. \nAdding this account was unsuccessful." << std::endl;
		return;
	}

	std::cout << "Type of account: normal | savings | privilege" << std::endl;
	std::cin >> type;

	time_t timer = NULL;

	if (type == "normal")
	{
		std::cin.ignore();
		addAccount(new NormalAccount(id, username, password, iban, timer));
		std::cout << "Account created successfully." << std::endl;
		return;
	}

	else if (type == "savings")
	{
		std::cin.ignore();

		int interestRate;
		std::cout << "Interest rate (percent): ";
		std::cin >> interestRate;
		std::cin.ignore();

		if (interestRate <= 0 || interestRate > 100)
		{
			std::cout << "Interest rate has to be between 0 and 100." << std::endl;
			return;
		}

		addAccount(new SavingsAccount(id, username, password, iban, timer, interestRate));
		std::cout << "Account created successfully." << std::endl;
		return;
	}
	else if (type == "privilege")
	{
		std::cin.ignore();

		double overdraft;
		std::cout << "Overdraft: ";
		std::cin >> overdraft;
		std::cin.ignore();

		if (overdraft < 0)
		{
			std::cout << "Overdraft has to be a positive number." << std::endl;
			return;
		}

		addAccount(new PrivilegeAccount(id, username, password, iban, timer, overdraft));
		std::cout << "Account created successfully." << std::endl;

		return;
	}
	else
		std::cout << "Invalid type." << std::endl;

	std::cin.ignore();
}

void Bank::deleteAccountFromUserInput()
{
	StringC iban;
	std::cout << "Iban of account: " << std::endl;
	std::cin >> iban;
	std::cin.ignore();

	if (!deleteAccount(iban))
		std::cout << "Deleting this account was unsuccessful." << std::endl;
	else
		std::cout << "Account deleted successfully." << std::endl;
}

void Bank::listCustomerAccFromUserInput() const
{
	int id;
	std::cout << "User id: ";
	std::cin >> id;
	std::cin.ignore();

	listCustomerAccount(id);
}

void Bank::withdrawFromUserInput()
{
	StringC iban = getIbanAfterLogin();

	if (iban.getSize() == 0)
	{
		std::cout << "Unsuccessful login." << std::endl;
		return;
	}

	double amount = 0;

	std::cout << "Amount: ";
	std::cin >> amount;
	std::cin.ignore();

	if (!withdraw(iban, amount))
		std::cout << "Withdrawal was unsuccessful." << std::endl;
	else
		std::cout << "Withdrawal was successful." << std::endl;
}

void Bank::depositFromUserInput()
{
	StringC iban = getIbanAfterLogin();

	if (iban.getSize() == 0)
	{
		std::cout << "Unsuccessful login." << std::endl;
		return;
	}

	double amount = 0;

	std::cout << "Amount: ";
	std::cin >> amount;
	std::cin.ignore();

	if (!deposit(iban, amount))
		std::cout << "Incorrect IBAN. \nDeposit was unsuccessful." << std::endl;
	else
		std::cout << "Deposit was successful." << std::endl;
}

void Bank::transferFromUserInput()
{
	StringC ibanFrom = getIbanAfterLogin();

	if (ibanFrom.getSize() == 0)
	{
		std::cout << "Unsuccessful login." << std::endl;
		return;
	}

	SavingsAccount* saccount = dynamic_cast<SavingsAccount*>(accounts.getAt(getAccountIndexByIBAN(ibanFrom)));
	if (saccount != nullptr)
	{
		std::cout << "Cannot transfer from a savings account." << std::endl;
		delete saccount;
		return;
	}
	delete saccount;

	StringC ibanTo;
	double amount = 0;

	std::cout << "Transfer to account with IBAN: ";
	std::cin >> ibanTo;

	if (getAccountIndexByIBAN(ibanTo) == -1)
	{
		std::cin.ignore();
		std::cout << "Incorrect receiver IBAN." << std::endl;
		return;
	}

	std::cout << "Amount: ";
	std::cin >> amount;
	std::cin.ignore();

	if (!transfer(ibanFrom, ibanTo, amount))
		std::cout << "Insufficient funds. \nTransfer was unsuccessful." << std::endl;
	else
		std::cout << "Transfer was successful." << std::endl;
}