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
		void databaseDrop( string input );
		void databaseCreate( string input );
		void databaseAlter( string input );
		void databaseUse( string input );
		bool databaseExists( string input );
};

#endif