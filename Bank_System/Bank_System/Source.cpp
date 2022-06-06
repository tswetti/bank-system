#include "StringC.h"
#include "Bank.h"
#include "NormalAccount.h"
#include "PrivilegeAccount.h"
#include "SavingsAccount.h"
#include "Customer.h"

#include <ctime>
#include <fstream>

bool appStart();
bool commandMenu(Bank&);

int main()
{
	appStart();

	return 0;
}

bool appStart()
{	
	StringC name;
	StringC address;

	std::cout << "Bank name: ";
	name.getline(std::cin);

	if (name == "quit")
		return false;

	std::cout << "Address: ";
	address.getline(std::cin);

	if (address == "quit")
		return false;

	Bank b(name, address);
	std::cout << "Bank created successfully!" << std::endl << std::endl;

	std::cout << "Commands: add customer | delete customer | add account | delete account" << std::endl;
	std::cout << "\t  list customers | list accounts | list customer account | list log | display" << std::endl;
	std::cout << "\t  withdraw | deposit | transfer" << std::endl;
	std::cout << "\t  export log | quit" << std::endl << std::endl;


	while (commandMenu(b));

	return true;
}

bool commandMenu(Bank& b)
{
	StringC command;

	std::cout << ">";

	command.getline(std::cin);

	if (command == "quit")
		return false;

	if (command == "add customer")
		b.addCustomerFromUserInput();

	else if (command == "delete customer")
		b.deleteCustomerFromUserInput();

	else if (command == "add account")
		b.addAccountFromUserInput();

	else if (command == "delete account")
		b.deleteAccountFromUserInput();

	else if (command == "list customers")
	{
		if (b.getCustomersSize() == 0)
			std::cout << "No customers." << std::endl;
		else
			b.listCustomers();
	}

	else if (command == "list accounts")
	{
		if (b.getAccountsSize() == 0)
			std::cout << "No accounts." << std::endl;
		else
			b.listAccounts();
	}

	else if (command == "list customer account")
		b.listCustomerAccFromUserInput();

	else if (command == "list log")
	{
		if (b.getTransactionsSize() == 0)
			std::cout << "No transactions." << std::endl;
		else
			b.listTransactions();
	}

	else if (command == "display")
		b.display();

	else if (command == "withdraw")
		b.withdrawFromUserInput();

	else if (command == "deposit")
		b.depositFromUserInput();

	else if (command == "transfer")
		b.transferFromUserInput();

	else if (command == "export log")
	{
		std::ofstream ofs("log.txt");

		if (!ofs.is_open())
			std::cout << "Export was unsuccessful." << std::endl;

		else
		{
			b.exportLog(ofs);
			std::cout << "Log exported successfully to log.txt" << std::endl;
		}

		ofs.close();
	}

	else
		std::cout << "Invalid command!" << std::endl;

	return true;
}
