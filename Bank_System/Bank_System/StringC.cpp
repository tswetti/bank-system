#include "StringC.h"

void StringC::copy(const StringC& other)
{
	str = new char[strlen(other.str) + 1];
	strcpy(str, other.str);
	size = other.size;
}

void StringC::free()
{
	delete[] str;
}

StringC::StringC(const char* str)
{
	if (str == nullptr)
	{
		this->str = new char[1];
		this->str[0] = '\0';
		size = 0;
	}
	else
	{
		size = strlen(str);
		this->str = new char[size + 1];
		strcpy(this->str, str);
	}
}

StringC::StringC()
{
	str = new char[1];
	str[0] = '\0';
	size = 0;
}

StringC::StringC(const StringC& other)
{
	copy(other);
}

StringC::StringC(StringC&& other)
{
	str = other.str;
	size = other.size;
	other.str = nullptr;
}

StringC& StringC::operator=(const StringC& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

StringC& StringC::operator=(StringC&& other)
{
	if (this != &other)
	{
		free();
		str = other.str;
		size = other.size;
		other.str = nullptr;
	}
	return *this;
}

StringC::~StringC()
{
	free();
}

size_t StringC::getSize() const
{
	return size;
}

const char* StringC::getString() const
{
	return str;
}

void StringC::setString(const char* str)
{
	if (str != nullptr)
		free();

	size = strlen(str);
	this->str = new char[size + 1];
	strcpy(this->str, str);
}

void StringC::concat(const StringC& other)
{
	char* temp = new char[getSize() + other.getSize() + 1];
	strcpy(temp, str);
	strcat(temp, other.str);

	delete[] str;
	str = temp;
	size = size + other.getSize();
}

std::ostream& operator<<(std::ostream& os, const StringC& string)
{
	os << string.str;
	return os;
}

std::istream& operator>>(std::istream& is, StringC& string)
{
	delete[] string.str;
	char buff[1024];
	is >> buff;

	string.size = strlen(buff);
	string.str = new char[string.size + 1];
	strcpy(string.str, buff);

	return is;
}

bool operator==(const StringC& lhs, const StringC& rhs)
{
	return strcmp(lhs.getString(), rhs.getString()) == 0;
}