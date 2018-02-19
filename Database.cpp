#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include "Database.h"


using namespace std;

#ifndef DATABASE_CPP
#define DATABASE_CPP

Database::Database()
{

}

Database::~Database()
{

}

void Database::databaseDrop()
{
	cout << "-- Database " << databaseName << " deleted." << endl;
	system( ( "rmdir " + databaseName ).c_str() );
}

/**
 * @brief databaseCreate
 *
 * @details creates new database directory
 *          
 * @pre input exists
 *
 * @post database DIRECTORY is created and initalized
 *
 * @par Algorithm 
 *      
 *      
 * @exception None
 *
 * @param [in] input provides string of db name
 *
 * @param [out] 
 *
 * @return None
 *
 * @note None
 */
void Database::databaseCreate()
{
	cout << "-- Database " << databaseName << " created." << endl;
	system( ( "mkdir " + databaseName ).c_str() );
}

void Database::databaseAlter( string input )
{

}

void Database::databaseUse()
{
	cout << "-- Using Database " << databaseName;
	cout << "." << endl;
}

bool Database::tableExists( string tblName )
{
	int tblSize = databaseTable.size();
	for( int index = 0; index < tblSize; index++ )
	{
		if( databaseTable[ index ].tableName == tblName )
		{
			return true;
		}
	}
	return false;
}


#endif