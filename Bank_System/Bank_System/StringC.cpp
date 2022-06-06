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

StringC::StringC(int num)
{
	size = integerDigitsCnt(num);

	str = new char[size + 1];

	for (int i = size - 1; i >= 0; i--)
	{
		str[i] = (num % 10) + '0';
		num /= 10;
	}

	str[size] = '\0';
}

StringC::StringC(double num)
{
	int prePoint = num;
	double s = num - prePoint;

	int counter = 0;

	while ((double(s - (int)s) > 0.00000099 || double((int)s - s) > 0.00000099) && counter < 9)
	{
		s *= 10;
		counter++;
	}

	int postPoint = s;

	int firstDigitsCnt = integerDigitsCnt(prePoint);
	int secondDigitsCnt = integerDigitsCnt(postPoint);

	size = firstDigitsCnt + secondDigitsCnt + 1;

	str = new char[size + 1];

	for (int i = firstDigitsCnt + secondDigitsCnt; i > firstDigitsCnt; i--)
	{
		str[i] = (postPoint % 10) + '0';
		postPoint /= 10;
	}

	str[firstDigitsCnt] = '.';

	for (int i = firstDigitsCnt - 1; i >= 0; i--)
	{
		str[i] = (prePoint % 10) + '0';
		prePoint /= 10;
	}

	str[firstDigitsCnt + secondDigitsCnt + 1] = '\0';
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
	if (this->str != nullptr)
		free();

	if (strlen(str) == 0)
	{
		size = 0;
		this->str = new char[1];
		this->str[0] = '\0';
		return;
	}

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

void StringC::getline(std::istream& ifs)
{
	delete[] str;

	char buff[1024];

	ifs.getline(buff, 1024, '\n');
	int length = strlen(buff);
	str = new char[length + 1];

	for (int i = 0; i < length; i++)
		str[i] = buff[i];

	str[length] = '\0';
	size = length;
}

int integerDigitsCnt(int num)
{
	int cnt = 0;

	while (num >= 1)
	{
		cnt++;
		num /= 10;
	}

	return cnt;
}