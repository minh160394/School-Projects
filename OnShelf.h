#ifndef ICT_ONSHELF_H__
#define ICT_ONSHELF_H__
#include "Good.h"
#include "Error.h"
#include "ReadWritable.h"
#include <fstream>
using namespace std;
namespace ict {
	class OnShelf : public Good {
	private:
		char recTag_;
   protected:
	   Error err_;
   public:
		 OnShelf( const char filetag = 'O');
	      fstream& store(fstream& file, bool addNewLine = true)const ;
	     fstream& load(fstream& file);
		 ostream& display(ostream& os, bool linear)const ;
		  istream& conInput(istream& is) ;
   };
}
#endif