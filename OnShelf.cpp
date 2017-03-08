#include "OnShelf.h"
#include "Good.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "ReadWritable.h"
#include "wpgeneral.h"
using namespace std;
namespace ict {
	OnShelf::OnShelf(const char filetag)
	{
		recTag_ = filetag;
	}
	fstream & OnShelf::store(fstream & file, bool addNewLine) const
	{
		file << recTag_<<","<<sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << "," << qtyNeeded();
		if (addNewLine == true)
		{
			file << endl;
		}
		return file;
	}
	fstream & OnShelf::load(fstream & file)
	{
		char _sku[MAX_SKU_LEN + 1];
		char _name[20];
		int _quantity;
		int _qtyNeeded;
		bool _taxed;
		double _price;
		file.getline(_sku, 5,',');
		sku(_sku);
		file.clear();
		file.getline(_name,20,',');
		name(_name);
		file.clear();
		file >> _price;
		file.ignore();
		price(_price);
		file >> _taxed;
		file.ignore();
		taxed(_taxed);
		file >> _quantity;
		file.ignore();
		quantity(_quantity);
		file >> _qtyNeeded;
		file.ignore();
		qtyNeeded(_qtyNeeded);
	
		return file;

	}
	ostream & OnShelf::display(ostream & os, bool linear) const
	{
		if (err_.isClear())
		{
			if (linear == true)
			{

				os << setw(MAX_SKU_LEN) << left << sku();
				if (strlen(name()) <= 20)
				{
					os << "|" << setw(20) << left <<name();
				}
				else
				{
					os << "|" << setw(strlen(name())) << left<<name();
				}
			
				if (taxed())
				{	
					os << "|" << setw(7) << setprecision(2)<< fixed << right << cost();
					os << "|" << " t ";	
				
				}
				else
				{
					os << "|" << setw(7) << setprecision(2) <<fixed << right << price();
					os << "|" << "   ";
					
				}
				os << "|" << setw(4) << right << quantity();
				os << "|" << setw(4) << right << qtyNeeded() <<"|";
			}
			else
			{
				os << "Sku: " << sku() << endl;
				os << "Name: " << name() << endl;
				os << "Price: " << price() << endl;
				if (taxed())
				{
					os << "Price after tax: " << cost() << endl;
				}
				else
				{
					os << "Price after tax: " << "N/A" << endl;
				}
				os << "Quantity On Hand: " << quantity() << endl;
				os << "Quantity Needed: " << qtyNeeded() << endl;

			}
		}
		else
		{
			os << err_.message();
		}
		return os;
	}
	istream & OnShelf::conInput(istream & is)
	{

		char _sku[MAX_SKU_LEN + 1];
		char _name[100];
		int _quantity;
		int _qtyNeeded;
		char _taxed;
		double _price;
		//
		if (!is.fail())
		{
			err_.clear();
			cout << "Sku: ";
			is >> _sku;
			sku(_sku);
			is.clear();
			cout << "Name: ";
			is >> _name;
			name(_name);
			is.clear();


			//
			if (err_.isClear())
			{
				cout << "Price: ";
				is >> _price;
				if (!is.fail())
				{
					price(_price);
					is.clear();
				}
				else
				{
					err_.message("Invalid Price Entry");
					is.setstate(ios::failbit);
				}
			}
			//
			if (err_.isClear())
			{
				cout << "Taxed: ";
				is >> _taxed;
				if (!is.fail())
				{
					if (_taxed == 'Y' || _taxed == 'y')
					{
						taxed(true);
						is.clear();
					}
					else if (_taxed == 'N' || _taxed == 'n')
					{
						taxed(false);
						is.clear();
					}
					else
					{
						err_.message("Only (Y)es or (N)o are acceptable");
						is.setstate(ios::failbit);
					}
				}
					else
					{
						err_.message("Only (Y)es or (N)o are acceptable");
						is.setstate(ios::failbit);
					}
				
			}
				//
				if (err_.isClear())
				{
					cout << "Quantity On hand: ";
					is >> _quantity;
					if (!is.fail())
					{
						quantity(_quantity);
						is.clear();
					}
					else
					{
						err_.message("Invalid Quantity Needed Entry");
						is.setstate(ios::failbit);
					}
				}

				//		
				if (err_.isClear())
				{
					cout << "Quantity Needed: ";
					is >> _qtyNeeded;
					if (!is.fail())
					{
						qtyNeeded(_qtyNeeded);
						is.clear();
					}
					else
					{
						err_.message("Invalid Quantity Needed Entry");
						is.setstate(ios::failbit);
					}
				}
			}
			return is;
		}
	}
