#include <iostream>
#include <vector>
#include <string>
using namespace std;

#ifndef TABLE_H
#define TABLE_H

struct Attributes{
	string attrName;
	string attrType;
};

class Table{
	public: 
		string tblName;
		vector <Attributes> attr;
		int attrNum;

		Table();
		~Table();
		void tableCreate( string input );
		void tableDrop( string input );
		void tableAlter( string input );
		void tableSelect( string input );

		//tableAlter Helper function
		void addAttr( string input );
};

#endif