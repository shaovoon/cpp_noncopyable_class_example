// NonCopyableClass.cpp : Defines the entry point for the console application.
//
#include <mutex>
#include <iostream>

// Works for C++11 and above
class DeletedCopyFunc
{
public:
	DeletedCopyFunc(int value): m_Value(value) {}
public:
	DeletedCopyFunc(const DeletedCopyFunc&) = delete;
	DeletedCopyFunc& operator=(const DeletedCopyFunc&) = delete;

private:
	int m_Value;
	std::mutex m_Mutex;
};

// Works for all C++ versions
class PrivateCopyFunc
{
public:
	PrivateCopyFunc(int value) : m_Value(value) {}
private:
	PrivateCopyFunc(const PrivateCopyFunc&);
	PrivateCopyFunc& operator=(const PrivateCopyFunc&);

private:
	int m_Value;
	std::mutex m_Mutex;
};

class CopyableClass
{
public:
	CopyableClass(int value) : m_Value(value) {}
	CopyableClass(const CopyableClass& that)
	{
		std::cout << "CopyableClass Copy Constructor called!" << std::endl;
		this->m_Value = that.m_Value;
	}
	CopyableClass& operator=(const CopyableClass& that)
	{
		std::cout << "CopyableClass Assignment Operator called!" << std::endl;
		this->m_Value = that.m_Value;
		return *this;
	}

private:
	int m_Value;
};

int main()
{
	/*
	DeletedCopyFunc a(10);
	DeletedCopyFunc b(a);
	b = a;

	PrivateCopyFunc c(10);
	PrivateCopyFunc d(c);
	d = c;
	*/

	CopyableClass a(10);
	CopyableClass b = a; // CopyableClass Copy Constructor called!
	b = a; // CopyableClass Assignment Operator called!

	CopyableClass c(a); // CopyableClass Copy Constructor called!

	return 0;
}

