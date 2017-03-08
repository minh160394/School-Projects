#ifndef ICT_READWRITABLE_H__
#define ICT_READWRITABLE_H__

#include <iostream>
#include <fstream>
using namespace std;
namespace ict {
   class ReadWritable {
   public:
	  virtual fstream& store(fstream& file, bool addNewLine = true)const = 0;
      virtual fstream& load(fstream& file) = 0;
      virtual ostream& display(ostream& os, bool linear)const = 0;
      virtual istream& conInput(istream& is) = 0;
   };
}

#endif // ICT_READWRITABLE
