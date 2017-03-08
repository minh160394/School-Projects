#ifndef ICT_GOOD_H__
#define ICT_GOOD_H__
#include "ReadWritable.h"
#include "wpgeneral.h"

namespace ict{
	class Good : public ReadWritable{
		char sku_[MAX_SKU_LEN + 1];
		char* name_;
		double price_;
		bool taxed_;
		int quantity_;
		int qtyNeeded_;
	public :
		Good();
		Good(const char* sku, const char* name, double price, int qtyNeeded, bool taxed = 0);
		Good(const Good& other);
		virtual ~Good();
		Good& operator =(const Good& other);
		void sku(const char* skunumber);
		void price(double price);
		void name(const char* name);
		void taxed(bool taxed);
		void quantity(int quantity);
		void qtyNeeded(int qytNeedednumber);
		
		const char* sku()const;
		double price()const;
		const char* name()const;
		bool taxed()const;
		int quantity()const;
		int qtyNeeded()const;
		double cost()const;
		Good& operator +=(int number);	
		bool operator==(const char* right)const;
	};

	double operator+=(double& value, const Good& right);
	std::ostream & operator<<(std::ostream & os , const Good & s);
	std::istream & operator >> (std::istream & is,  Good & s);


}


#endif