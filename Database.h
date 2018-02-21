#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "Table.cpp"

#ifndef DATABASE_H
#define DATABASE_H

class Database{
	public: 
		string databaseName;
		vector <Table> databaseTable;
		int tableNum;

		Database();
		~Database();
		void databaseDrop();
		void databaseCreate();
		void databaseAlter( string input );
		void databaseUse();
		bool tableExists( string tblName, int &tblReturn );
};

#endif