#include <cstring>
#include <iostream>
#include "wpgeneral.h"
#include "Good.h"
#include <fstream>
using namespace std;
namespace ict{
	Good::Good()
	{
		sku_[0] = 0;
		name_ = nullptr;
		price_ = 0;
		taxed_ = true;
		quantity_ = 0;	
		qtyNeeded_ = 0;

	}

	Good::Good(const char* skucode, const char * name, double price, int qtyNeedednumber, bool taxed )
	{
		strncpy(sku_, skucode, MAX_SKU_LEN + 1);
		name_ = new char[strlen(name) + 1];
		strcpy(name_, name);
		price_ = price;
		quantity_ = 0;
		qtyNeeded_ = qtyNeedednumber;
		taxed_ = taxed;
	}

	Good::Good(const Good & other)
	{
		strncpy(sku_, other.sku_, MAX_SKU_LEN + 1);
		price_ = other.price_;
		quantity_ = other.quantity_;
		qtyNeeded_ = other.qtyNeeded_;
		taxed_ = other.taxed_;
		if (other.name_ != nullptr)
		{
			name_ = new char[strlen(other.name_) + 1];
			strcpy(name_, other.name_);
		}
		else
		{
			name_ = nullptr;
		}
	}

	Good::~Good()
	{
		delete[] name_;
	}

	Good& Good::operator=(const Good & other)
	{
		if(this != &other)
		{
			strncpy(sku_, other.sku_, MAX_SKU_LEN + 1);
			price_ = other.price_;
			quantity_ = other.quantity_;
			qtyNeeded_ = other.qtyNeeded_;
			taxed_ = other.taxed_;
			if (other.name_ != nullptr)
			{
				name_ = new char[strlen(other.name_) + 1];
				strcpy(name_, other.name_);
			}
			else
			{
				name_ = nullptr;
			}

		}
		return *this;

	}

	void Good::sku(const char* skunumber)
	{
		strncpy(sku_, skunumber, MAX_SKU_LEN + 1);
	}

	void Good::price(double price)
	{
		price_ = price;
	}

	void Good::name(const char * name)
	{
		name_ = nullptr;//may be
		delete[] name_;
		name_ = new char[strlen(name) + 1];
		strcpy(name_, name);
	}

	void Good::taxed(bool taxed)
	{
		taxed_ = taxed;
	}

	void Good::quantity(int quantity)
	{
		quantity_ = quantity;
	}

	void Good::qtyNeeded(int qytNeedednumber)
	{
		qtyNeeded_ = qytNeedednumber;
	}

	const char * Good::sku()const
	{
		return sku_;
	}

	double Good::price()const
	{
		return price_;
	}

	const char * Good::name()const
	{
		return name_;
	}

	bool Good::taxed()const
	{
		return taxed_;
	}

	int Good::quantity()const
	{
		return quantity_;
	}


	int Good::qtyNeeded()const
	{
		return qtyNeeded_;
	}

	double Good::cost() const
	{
		if (!taxed())
		{
			return price_ ;
		}
		else
		{
			return price_ * TAX + price_;
		}
	}

	Good & Good::operator+=(int number)
	{
		quantity_ += number;
		return *this;
	}

	bool Good::operator==(const char* right)const
	{
		return (strcmp(sku_, right) == 0);
	}


	double operator+=(double& value, const Good & right)
	{		
		return value = right.cost() * right.quantity();
	}

	std::ostream & operator<<(std::ostream & os, const Good & s)
	{
		s.display(os,true);
		return os;
	}

	std::istream& operator>>(std::istream & is, Good& i)
	{
		i.conInput(is);
		return is;
	}

	
}