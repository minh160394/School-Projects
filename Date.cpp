// header files go here
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Date.h"
#include "wpgeneral.h"
using namespace std;
namespace ict {
   
   // member functions
   void Date::errCode(int errorCode)
   {
      readErrorCode_ = errorCode;
   }
   // returns a unique value representing the date
   // this value is used to compare two dates
   int Date::value()const {
      return year_ * 372 + mon_ * 31 + day_;
   }
   int Date::errCode()const
   {
      return readErrorCode_;
   }

   bool Date::bad() const
   {
      return readErrorCode_ != NO_ERROR;
   }
   // constructors

   Date::Date(int year, int mon, int day)
   {
	  
      year_ = year;
      mon_ = mon;
      day_ = day;
	  readErrorCode_ = NO_ERROR;
   }
   Date::Date(int year, int mon, int day, int error)
   {

	   year_ = year;
	   mon_ = mon;
	   day_ = day;
	   readErrorCode_ = error;
   }

   Date::Date()
   {
	   year_ = 0; mon_ = 0; day_ = 0, readErrorCode_ = NO_ERROR; 
   }

   // operators
   bool Date::operator==(const Date & D) const
   {
      return this->value() == D.value();
   }

   bool Date::operator!=(const Date & D) const
   {
      return this->value() != D.value();
   }

   bool Date::operator<(const Date & D) const
   {
      return this->value() < D.value();
   }

   bool Date::operator>(const Date & D) const
   {
      return this->value() > D.value();
   }

   bool Date::operator<=(const Date & D) const
   {
      return this->value() <= D.value();
   }

   bool Date::operator>=(const Date & D) const
   {
      return this->value() >= D.value();
   }

   // bool validate(), this is an optional private function
   // for validation logic and setting the _readErrorCode.
   // see the read() function description for more details




   std::ostream&  Date::write(std::ostream & ostr) const
   {
	   // TODO: insert return statement here
	   ostr<< year_ << "/" << setw(2)<<right<<mon_ << "/" <<setw(2)<<right<<day_;
	   return ostr;
   }

   // IO functions
   std::istream&  Date::read(std::istream & istr)
   {
	   char a, b;
	   istr.clear();
	   istr.ignore(0,'\n');
	   istr >> year_ >> a >> mon_ >> b >> day_;
	  
	   if (a != '/')
	   {
		   errCode(CIN_FAILED);
		
	   }
	  else if(mdays() == -1 || year_ < 1990 || year_> 9999)
	  {
		  errCode(YEAR_ERROR);
	  }	
	  else if (b != '/')
	  {
		  errCode(CIN_FAILED);
	  }
	  else if (mdays() == -1 || mon_ < 0 || mon_ > 12)
	  {
		  errCode(MON_ERROR);
	  }
	
	  else if (mdays() == -1 || day_ < 0 || day_ > 31)
	  {
		  errCode(DAY_ERROR);
	  }
	  else
	  {
		 errCode(NO_ERROR);
	
	  }   
	   
	   return istr;
   }

   // mdays():
   // returns the day of the month.
   // _mon value must be set for this function to work
   // if _mon is invalid, this function returns -1
   // leap years are considered in this logic
   int Date::mdays()const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
      mon--;
      return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
   }
   // non-memeber operator overloads
   std::istream & operator >> (std::istream & is, Date & s)
   {
	   // TODO: insert return statement here
	   s.read(is);
	   return is;
   }

   std::ostream & operator<<(std::ostream & os, const Date & s)
   {
	   // TODO: insert return statement here
	   s.write(os);
	   return os;
   }

}
