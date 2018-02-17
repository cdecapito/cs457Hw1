#include <iostream>
#include <vector>
#include <string>
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

void Database::databaseDrop( string input )
{

}

/**
 * @brief databaseCreate
 *
 * @details creates new database
 *          
 * @pre input exists
 *
 * @post database is created and initalized
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
void Database::databaseCreate( string input )
{
	databaseName = input;
	tableNum = 0;

}

void Database::databaseAlter( string input )
{

}

void Database::databaseUse( string input )
{

}


#endif