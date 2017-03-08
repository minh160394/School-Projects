#ifndef ICT_CUSTOMMADE_H__
#define ICT_CUSTOMMADE_H__
#include "OnShelf.h"
#include "Date.h"
#include "Error.h"
#include <fstream>
using namespace std;
namespace ict {
   class CustomMade :public OnShelf{
   private:
	   Date delivery_;
	   
   public:
	   CustomMade(const char recTag_ = 'C') :OnShelf(recTag_) {};
      void delivery(const Date &value);
	  const Date& delivery()const;
	   fstream& store(fstream& file, bool addNewLine = true)const;
	  fstream & load(fstream & file);
	 ostream& display(ostream& ostr, bool linear)const;
	  istream& conInput(istream& istr);
   };
}


#endif
