#pragma once
#pragma warning(disable:4996)

#include <cstring>
#include <fstream>

class StringC
{
	char* str;
	size_t size;

	void copy(const StringC&);
	void free();

public:
	StringC(const char*);

	StringC();
	StringC(const StringC&);
	StringC(StringC&&);

	StringC& operator=(const StringC&);
	StringC& operator=(StringC&&);

	~StringC();

	size_t getSize() const;
	const char* getString() const;

	void setString(const char*);

	void concat(const StringC&);

	friend std::ostream& operator<<(std::ostream&, const StringC&);
	friend std::istream& operator>>(std::istream&, StringC&);
};

bool operator==(const StringC&, const StringC&);

