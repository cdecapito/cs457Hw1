#include <iostream>
#include <vector>
#include <string>
using namespace std;

#ifndef TABLE_H
#define TABLE_H

struct Attribute{
	string attributeName;
	string attributeType;
};

class Table{
	public: 
		string tableName;
		int attrNum;

		Table();
		~Table();
		void tableCreate( string currentWorkingDirectory, string currentDatabase, string tblName, string input, bool &errorCode );
		void tableDrop( string dbName );
		void tableAlter( string currentWorkingDirectory, string currentDatabase, string input, bool &errorCode );
		void tableSelect( string currentWorkingDirectory, string currentDatabase );
};

#endif