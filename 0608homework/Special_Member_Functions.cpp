#include <iostream>

using namespace std;

class Homework // ¾èÀºº¹»ç
{
	int num = 0;
	char* ptr = nullptr;

public:
	Homework() = default;
	Homework(const int num, const char* ptr)
		: num(num)
	{
		this->ptr = new char[strlen(ptr) + 1];
		strcpy(this->ptr, ptr);
	}

	~Homework() = default;
	
	Homework(const Homework& rhs) : num(rhs.num), ptr(rhs.ptr) {}
	
	Homework& operator= (const Homework& rhs)
	{
		this->num = rhs.num;
		this->ptr = rhs.ptr;
		return *this;
	}
	
	Homework(Homework&& rhs) noexcept : num(rhs.num), ptr(rhs.ptr) {}
	
	Homework& operator= (Homework&& rhs) noexcept
	{
		this->num = rhs.num;
		this->ptr = rhs.ptr;
		return *this;
	}
};

class Homework2 // ±íÀºº¹»ç
{
	int num = 0;
	char* ptr = nullptr;

public:
	Homework2() = default;
	Homework2(const int num, const char* ptr)
		: num(num)
	{
		this->ptr = new char[strlen(ptr) + 1];
		strcpy(this->ptr, ptr);
	}

	~Homework2()
	{
		if (this->ptr != NULL)
		{
			delete[] ptr;
			this->ptr = nullptr;
		}
	}

	Homework2(const Homework2& rhs)
	{
		this->num = rhs.num;

		if (rhs.ptr != nullptr)
		{
			this->ptr = new char[this->num];
			for (int i = 0; i < this->num; i++)
			{
				this->ptr[i] = rhs.ptr[i];
			}
		}
		else
			this->ptr = nullptr;
	}

	Homework2& operator= (const Homework2 & rhs)
	{
		if (this == &rhs)
			return *this;

		if (this->ptr != nullptr)
		{
			delete[] this->ptr;
			this->ptr = nullptr;
		}

		this->num = rhs.num;

		if (rhs.ptr != nullptr)
		{
			this->ptr = new char[num];
			for (int i = 0; i < this->num; i++)
			{
				this->ptr[i] = rhs.ptr[i];
			}
		}
		else
			this->ptr = nullptr;

		return *this;
	}

	Homework2(Homework2&& rhs) noexcept
	{
		this->ptr = std::move(rhs.ptr);
		this->num = std::move(rhs.num);

		rhs.ptr = nullptr;
	}

	Homework2& operator= (Homework2&& rhs) noexcept
	{
		if (this == &rhs)
			return *this;

		if (this->ptr != nullptr)
		{
			if (rhs.ptr != nullptr && ptr != rhs.ptr)
			{
				delete[] this->ptr;
				this->ptr = nullptr;

				this->ptr = std::move(rhs.ptr);
			}
		}
		else
		{
			this->ptr = std::move(rhs.ptr);
		}

		this->num = std::move(rhs.num);

		rhs.ptr = nullptr;

		return *this;
	}
};

int main()
{


	return 0;
}