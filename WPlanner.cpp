#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include "WPlanner.h"
#include "Good.h"
#include "OnShelf.h"
#include "CustomMade.h"
#include <istream>

using namespace std;
namespace ict {

	WPlanner::WPlanner(const char* filename) {
		strcpy(filename_, filename);
		noOfItems_ = 0;
		for (int i = 0; i < MAX_NO_RECS; i++) {
			items_[i] = nullptr;
		}
		loadRecs();
		
	}
   void WPlanner::deleteItem()
   {
     
	  char * x;
	  x = new char[MAX_SKU_LEN + 1];
	  getSku(x);
	  int i = SearchItems(x);
          cout << endl;
	  if(i == -1)
	  {
		  cout << "Item Not found!" << endl << endl;
	  }
	  else
	  {
		  cout << "The following Item will be deleted:" << endl;
		  items_[i]->display(cout, false);
		  cout << endl;
		  cout << "Type (Y) to confirm or (N) to abort: ";
		  char x=0;
		  cin >> x;
		  cout <<endl;
		  if(x == 'Y'||x =='y')
		  {
			  cout << "Item deleted!"<<endl <<endl;
			  noOfItems_ = noOfItems_ - 1;
			  for (int number= i ;number < noOfItems_; number++)
			  {
				  items_[number] = items_[number + 1];
			  }

		  }
		  else
		  {
			  cout << "Aborted!" <<endl<<endl;
		  }

	  }



   }

   void WPlanner::getSku(char * sku)
   {
	  
	   cout << "Please enter the SKU: ";

	   cin >> sku;
	   cin.clear();
	   
	   if (cin.fail())
	   {
		   cin.clear();
		   cin.ignore();
	   }
	   
   }
   void WPlanner::saveRecs() {
	   datafile_.open(filename_, ios::out);
	   if (datafile_.is_open())
	   {
		   for(int i = 0 ; i < noOfItems_; i++)
		   {
			   items_[i]->store(datafile_, true);
		   }
		   datafile_.close();
	   }





   }
   void WPlanner::loadRecs() {
	   int readIndex = 0;
	   char Type=0;
	   Good* a; 
	   fstream datafile_;
	   datafile_.open(filename_, std::ios::in);
	   if (!datafile_.fail())
	   {
		  
		   while(!datafile_.fail())
		   {
			   datafile_ >> Type;
			   if (Type == 'C')
			   {
				   a = new CustomMade();
				
			   }
			   else if (Type == 'O')
			   {
				   a= new OnShelf();
				   
			   }
			   
				 datafile_.ignore();
			   	  a->load(datafile_);
				  items_[readIndex] = a;
			      noOfItems_ = readIndex;
				  readIndex++;
				
		   }
		  
	   }
	   else
	   {
		   datafile_.clear();
		   datafile_.close();
		   datafile_.open(filename_, std::ios::out);
		   datafile_.close();
	   } 
	   datafile_.close();
		
   }



   void WPlanner::updateQty()
   {
	   char* sku;
	   sku = new char[MAX_SKU_LEN+1];
	   getSku(sku);
	   int index = 0;
		   index=SearchItems(sku);
	   if (cin.fail()) 
	   {
		   cout << "Invalid Quantity value!" << endl;
	   }
	   if (index == -1)
	   {
		   cout << endl << "Not found!" << endl;
	   }
	   else
	   {
		   cout << endl;
		   items_[index]->display(cout, false);
		   cout << endl;
		   int goods;
		   cout << "Please enter the number of purchased goods: ";
		   cin >> goods;
		   if (goods <= items_[index]->qtyNeeded() - items_[index]->quantity())
		   {
			   *items_[index] += goods;
			   saveRecs();
			   cout << endl << "Updated!" << endl << endl;
		   }
		   else
		   {
			   cout << "Too many purchased, only " << items_[index]->qtyNeeded();
			   cout << "needed, please return the extra " << items_[index]->qtyNeeded() - goods << "." << endl;
		   }
	   }
	   cin.clear();
	   cin.ignore();
   }
   void WPlanner::listItems()const {
	   double total=0;
      cout << " Row | SKU | Good Name          | Cost  |Tax| QTY|Need| Delivery" << endl
         << "-----|-----|--------------------|-------|---|----|----|----------" << endl;
	  for (int i = 0; i < noOfItems_; i++)
	  {
		  int count = 0;
		  count = i + 1;
		  cout << setw(4) << right << count;
		  cout << " | ";
		  items_[i]->display(cout, true);
		  cout << endl;
		  total += items_[i]->cost() * items_[i]->quantity();
	  }
      cout << "-----+-----+--------------------+-------+---+----+----+----------" << endl;

	  cout << "Total cost of the Wedding: "<<"$"<< total << endl <<endl;
   }
   int WPlanner::SearchItems(const char* sku)const {

	   for (int i = 0; i < noOfItems_; i++) {
		   if(*items_[i] == sku)
		   {
			   return i;
		   }
		
	   }   return -1;
   }
   void WPlanner::addItem(bool isCustomMade) {
	   Good *a=nullptr;
	   if (isCustomMade == true)
	   {
		   a = new CustomMade();
		   a->conInput(cin);
		   if (!cin.fail())
		   {
			   items_[noOfItems_] = a;
			   noOfItems_++;
			   saveRecs();
			   cout << endl << "Good added" << endl << endl;
		   }
		   else
		   {
			   a->display(cout, true);
		   }
		   
	   }
	   else if (isCustomMade == false)
	   {
		   a = new OnShelf();
		   a->conInput(cin);
		   if (!cin.fail())
		   {
			   items_[noOfItems_] = a;
			   noOfItems_++;
			   saveRecs();
			   cout << endl << "Good added" << endl << endl;
		   }
		   else
		   {
			   a->display(cout, true);
		   }
	   }
   }
   int WPlanner::menu() {
      int select =-1;
		  cout << "Wedding Planner Management Program" << endl;
		  cout << "1 - List goods" << endl;
		  cout << "2 - Add On Shelf Good" << endl;
		  cout << "3 - Add Custom-Made Good" << endl;
		  cout << "4 - Update Good quantity" << endl;
		  cout << "5 - Delete" << endl;
		  cout << "0 - Exit program" << endl;
		  cout << "> ";
		  cin >> select;
		  cout << endl;
		  cin.clear();
		  if (std::cin.fail() != true && (select >= 0 && select <= 5)) {
			  cin.ignore();
			  cin.clear();


		  }
		  else {
			  select = -1;
			  cin.ignore();
			  cin.clear();
		  }
		  return select;
		  
   }
  
   int WPlanner::run() {
		   bool done = false;
		   while (!done) {
			   switch (menu()) {
			   case 1:
				   listItems();
				   break;
			   case 2:
				   addItem(false);
				   break;
			   case 3:
				   addItem(true);
				   break;
			   case 4:
				   updateQty();
				   break;
			   case 5:
				   deleteItem();
				   break;
			   case 0:
				   done = true;
				   cout << "Goodbye!!" << endl << endl;
				   break;
			   case -1:
				   cout << "===Invalid Selection, try again.===" << endl << endl;
				   break;
			   }
		   }
		   return 0;
	   } // WPlanner::run() end
   
}


/* outputs

Wedding Planner Management Program
1 - List goods
2 - Add On Shelf Good
3 - Add Custom-Made Good
4 - Update Good quantity
5 - Delete
0 - Exit program
>



Not found!

Please enter the number of purchased goods:

Too many purchased, only 5 needed, please return the extra 15.

Updated!

Not implemented!

*/
