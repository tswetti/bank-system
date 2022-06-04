#include "Transaction.h"

Transaction::Transaction(const time_t& time, const StringC& description) : time(time), description(description) {}

void Transaction::display() const
{
	std::cout << "Time of transaction: " << ctime(&time);
	std::cout << "Transaction: " << description << std::endl;
}

bool Transaction::exportToFile(std::ofstream& ofs) const
{
	if (!ofs.is_open())
		return false;

	ofs << ctime(&time) << description << std::endl;
	return true;
}

Transaction* Transaction::clone() const
{
	return new Transaction(*this);
}