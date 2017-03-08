#include "CustomMade.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
namespace ict {

	void CustomMade::delivery(const Date & value)
	{
		delivery_ = value;
	}

	const Date & CustomMade::delivery() const
	{
		return delivery_;
	}
	fstream & CustomMade::store(fstream & file1, bool addNewLine) const
	{	
		OnShelf::store(file1, false);
		
			file1 << ",";
			file1 << delivery();
		
		if (addNewLine == true)
		{	
			file1 << endl;
		
		}
	
		return file1;
	}

	fstream & CustomMade::load(fstream & file)
	{
		
		OnShelf::load(file);
		delivery_.read(file);
		
		return file;
	}

	ostream & CustomMade::display(ostream & ostr, bool linear) const
	{	
		OnShelf::display(ostr, linear);
		if(err_.isClear())
		{

			if (linear == true)
			{
				
				ostr << delivery();
			}
			else
			{
				ostr << "delivery date: " << delivery()<<endl;
			}
		}
		return ostr;
	}

	istream & CustomMade::conInput(istream & istr)
	{	
		Date dd;
	
			OnShelf::conInput(istr);
			if (err_.isClear())
			{
				cout << "delivery date (YYYY/MM/DD) : ";
				istr >> dd;
					
			
					if (dd.bad())
					{
						if (dd.bad())
						{
							if (dd.errCode() == CIN_FAILED)
							{
								err_.message("Invalid Date Entry");
							}
							else if (dd.errCode() == YEAR_ERROR)
							{
								err_.message("Invalid Year in Date Entry");
							}
							else if (dd.errCode() == MON_ERROR)
							{
								err_.message("Invalid Month in Date Entry");
							}
							else if (dd.errCode() == DAY_ERROR)
							{
								err_.message("Invalid Day in Date Entry");
							}

						}	istr.setstate(ios::failbit);
					}
					else
					{
							delivery(dd);
					}
				}			
		return istr;
	}
	
		
	}



