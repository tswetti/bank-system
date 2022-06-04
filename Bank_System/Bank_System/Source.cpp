/*#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>*/

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
	/*_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);*/

	/*Bank b("Bank", "Sofia");
	Customer* c1 = new Customer(1, "Tsvetelina", "Pleven");
	Customer* c2 = new Customer(2, "Ivan", "Sofia");
	Customer* c3 = new Customer(2, "Lili", "Sofia");

	b.addCustomer(c1);
	b.addCustomer(c2);
	b.addCustomer(c3);

	//b.listCustomerAccount(2);
	//b.listCustomers();

	time_t timer;
	time(&timer);

	Account* a = new NormalAccount(1, "tswetti", "123","123456", 10000, timer);

	time(&timer);

	Account* a2 = new SavingsAccount(2, "iii", "12", "123", 12, timer, 5);
	b.addAccount(a);
	b.addAccount(a2);

	b.deleteCustomer(1);
	b.listCustomers();

	/*b.transfer("123456", "123", 200);

	b.deposit("123", 100);
	b.withdraw("123", 200);
	b.withdraw("123456", 12);*/

	//b.listCustomerAccount(1);
	//b.listCustomerAccount(2);
	//b.listAccounts();

	

	//b.listTransactions();

	/*b.listCustomers();
	b.listAccounts();
	b.listCustomerAccount(2);
	
	b.display();

	std::ofstream ofs("log.txt");
	b.exportLog(ofs);
	ofs.close();*/

	appStart();

	return 0;
}

bool appStart()
{
	const int MAX_ADDRESS_LENGTH = 60;
	
	StringC name;
	StringC address;
	char addressArr[MAX_ADDRESS_LENGTH];

	std::cout << "Bank name: ";
	std::cin >> name;
	std::cin.ignore();

	if (strcmp(name.getString(), "quit") == 0)
		return false;

	std::cout << "Address: ";
	std::cin.getline(addressArr, MAX_ADDRESS_LENGTH);
	address = addressArr;

	if (strcmp(addressArr, "quit") == 0)
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
	const int MAX_CMD_LENGTH = 60;

	char cmd[MAX_CMD_LENGTH] = {};
	StringC command;

	std::cin.getline(cmd, MAX_CMD_LENGTH);
	command = cmd;

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
		b.listCustomers();

	else if (command == "list accounts")
		b.listAccounts();

	else if (command == "list customer account")
		b.listCustomerAccFromUserInput();

	else if (command == "list log")
		b.listTransactions();

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
