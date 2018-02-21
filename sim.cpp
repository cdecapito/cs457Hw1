// Program Information /////////////////////////////////////////////////////////
/**
  * @file sim.cpp
  *
  * @brief implements simulation functions    
  * 
  * @details Performs command line instructions to create and drop db/tbls
  *
  * @version 1.01 Carli DeCapito
  *			 February 10, 2018 - DB create/drop impementation, create directories
  *
  *			 1.00 Carli DeCapito
  *			 February 8, 2018 -- Initial Setup, Create/Drop DB Implementation
  *
  * @note None
  */

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include "Database.cpp"

using namespace std;

const string DATABASE_TYPE = "DATABASE";
const string TABLE_TYPE = "TABLE";

const string DROP = "DROP";
const string CREATE = "CREATE";
const string SELECT = "SELECT";
const string USE = "USE";
const string ALTER = "ALTER";
const string EXIT = ".EXIT";

const int ERROR_DB_EXISTS = -1;
const int ERROR_DB_NOT_EXISTS = -2;
const int ERROR_TBL_EXISTS = -3;
const int ERROR_TBL_NOT_EXISTS = -4;
const int ERROR_INCORRECT_COMMAND = -5;

void startSimulation( string currentWorkingDirectory );
bool removeSemiColon( string &input );
bool startEvent( string input, vector< Database> &dbms, string currentWorkingDirectory, string &currentDatabase );
string getNextWord( string &input );
bool databaseExists( vector<Database> dbms, Database dbInput, int &indexReturn );
void removeDatabase( vector< Database > &dbms, int index );
void handleError( int errorType, string commandError, string errorContainerName );
void convertToLC( string &input );

/**
 * @brief startSimulation 
 *
 * @details takes string input and begins to parse
 *          
 * @pre None
 *
 * @post Program ends when .EXIT is inputted
 *
 * @par Algorithm 
 *      Loop until .EXIT is inputted from terminal
 *		Otherwise parse string to find out what action to take
 *      
 * @exception None
 *
 * @param [in] None
 *
 * @param [out] None
 *
 * @return None
 *
 * @note None
 */
void startSimulation( string currentWorkingDirectory )
{
	string input;
	string currentDatabase;
	vector< Database > dbms;

	bool simulationEnd = false;

	do{
		cout << "> ";
		getline( cin, input );
		//helper function to remove semi colon
		if( removeSemiColon( input ) )
		{
			//call helper function to check if modifying db or tbl
			simulationEnd = startEvent( input, dbms, currentWorkingDirectory, currentDatabase );
		}

	}while( simulationEnd == false );

	cout << "All done. " << endl; 
}


/**
 * @brief removeSemiColon
 *
 * @details removes semi colons from input string
 *          
 * @pre string exists
 *
 * @post string ; is removed
 *
 * @par Algorithm 
 *      using find and erase string functions
 *      
 * @exception None
 *
 * @param [in] none
 *
 * @param [out] input provides a string of the input command
 *
 * @return None
 *
 * @note None
 */
bool removeSemiColon( string &input )
{
	//CHECK IF SEMI EXISTS
	int semiIndex = 0;
	int strLen = input.length();
	bool semiExists = false;
	//find where ; exists if it does exist
	for ( int index = 0; index < strLen; index++ )
	{
		if( input[ index ] == ';' )
		{
			semiExists = true;
			semiIndex = index;
		}
	}
	//if semi colon does not exist or is not at the end
	if( semiExists == false || semiIndex != ( strLen - 1 ) )
	{
		//if input is exit then we are fine
		if( input == EXIT )
		{
			return true;
		}
		else
		{
			//otherwise incorrect syntax
			handleError( ERROR_INCORRECT_COMMAND, "NULL", input );
			return false;
		}

	}
	else
	{
		//if semi colon is at end then erase it
		input.erase( input.find( ';' ) );
		return true;
	}
	
}




/**
 * @brief startEvent
 *
 * @details Initiates action to take: create, use, drop, select, alter
 *          
 * @pre input and dbms exists
 *
 * @post action is done
 *
 * @par Algorithm 
 *      stores data into DB class and into tables
 *      
 * @exception None
 *
 * @param [in] input provides string of input command
 *
 * @param [out] dbms provides system of database to add databases and tables
 *
 * @return None
 *
 * @note None
 */
bool startEvent( string input, vector< Database> &dbms, string currentWorkingDirectory, string &currentDatabase )
{
	bool exitProgram = false;
	bool errorExists = false;

	//bool tblExists;
	int indexReturn;
	int errorType;
	string originalInput = input;
	string errorContainerName;
	string actionType = getNextWord( input );
	string containerType;

	if( actionType.compare( SELECT )  == 0 )
	{

	}
	else if( actionType.compare( USE ) == 0 )
	{
		
		Database dbTemp;
		dbTemp.databaseName = input;
		bool dbExists = databaseExists( dbms, dbTemp, indexReturn );
		
		//check if database exists
		if( dbExists )
		{
			//if it does then set current database as string
			currentDatabase = dbTemp.databaseName;
			dbTemp.databaseUse();
		}
		else
		{
			//if it does not then return error message
			errorExists = true;
			errorContainerName = dbTemp.databaseName;
			errorType = ERROR_DB_NOT_EXISTS; 
		}
	}
	else if( actionType.compare( CREATE ) == 0 ) 
	{
		//get string if we are modifying table or db
		containerType = getNextWord( input );
		//databse create
		if( containerType == DATABASE_TYPE )
		{
			Database dbTemp;
			//call Create db function
			dbTemp.databaseName = input;
			//check that db does not exist already
			bool dbExists = databaseExists( dbms, dbTemp, indexReturn );

			if( dbExists )
			{
				//if it does then return error message
				errorExists = true;
				errorContainerName = dbTemp.databaseName;
				errorType = ERROR_DB_EXISTS; 
			}
			else
			{
				//if it does not, return success message and push onto vector
				dbms.push_back( dbTemp );

				//create directory
				dbTemp.databaseCreate();
			}
		}
		//table create
		else if( containerType == TABLE_TYPE )
		{
			
			//call create tbl function
			Database dbTemp;
			dbTemp.databaseName = currentDatabase;
			//get indexReturn of database
			databaseExists( dbms, dbTemp, indexReturn );
			
			//get table name
			Table tblTemp;
			tblTemp.tableName = getNextWord( input );

			//check that table exists
			if( !(dbms[ indexReturn ].tableExists( tblTemp.tableName )) )
			{
				//check that table attributes are not the same
				bool attrError = false;
				tblTemp.tableCreate( currentWorkingDirectory, currentDatabase, tblTemp.tableName, input, attrError );
				if( !attrError  )
				{
					//if it doesnt then push table onto database	
					dbms[ indexReturn ].databaseTable.push_back( tblTemp );
				}
			}
			else
			{
				//if it does than handle error
			 	errorExists = true;
			 	errorType = ERROR_TBL_EXISTS;
			 	errorContainerName = tblTemp.tableName;	
			}

		}
		else
		{
			errorExists = true;
			errorType = ERROR_INCORRECT_COMMAND;
			errorContainerName = originalInput;	
		}

	}
	else if( actionType.compare( DROP ) == 0 )
	{
		containerType = getNextWord( input );
		if( containerType == DATABASE_TYPE )
		{
			//create temp db to be dropped
			Database dbTemp;
			dbTemp.databaseName = input;

			//check if database exists
			if( databaseExists( dbms, dbTemp, indexReturn ) != true )
			{
				//if it does not then return error message
				errorExists = true;
				errorContainerName = dbTemp.databaseName;
				errorType = ERROR_DB_NOT_EXISTS; 
			}
			else
			{
				//if it does, return success message and remove from indexReturn element
				removeDatabase( dbms, indexReturn );

				//remove directory
				dbTemp.databaseDrop();
			}


		}
		else if( containerType == TABLE_TYPE )
		{
			//call drop tbl function
		}
		else
		{
			errorExists = true;
			errorType = ERROR_INCORRECT_COMMAND;
			errorContainerName = originalInput;	
		}

	}
	else if( actionType.compare( ALTER ) == 0 ) 
	{
		containerType = getNextWord( input );
		if( containerType == DATABASE_TYPE )
		{
			//call alter db function
		}
		else if( containerType == TABLE_TYPE )
		{
			//call alter tbl function
		}

	}
	else if( actionType.compare( EXIT ) == 0 )
	{
		exitProgram = true;
	}
	else
	{
		errorExists = true;
		errorType = ERROR_INCORRECT_COMMAND;
		errorContainerName = originalInput;
	}

	if( errorExists )
	{
		handleError( errorType, actionType, errorContainerName );
	}

	return exitProgram;
}


/**
 * @brief getNextWord
 *
 * @details determines what action is: create, drop, use, select, alter
 *          
 * @pre input exists
 *
 * @post returns string depending on action
 *
 * @par Algorithm 
 *      use first word to determine action
 *      
 * @exception None
 *
 * @param [in] none
 *
 * @param [out] input provides input command from terminal
 *
 * @return string
 *
 * @note None
 */
 /*
string getNextWord( string &input )
{

	string actionType;
	//take first word of input and set as action word
	actionType = input.substr( 0, input.find(" "));
	//erase word from original str to further parse
	input.erase( 0, input.find(" ") + 1 );

	return actionType;	
}
*/




/**
 * @brief databaseExists
 *
 * @details checks whether dbInput exists in dbms
 *          
 * @pre dbms exists and dbInput exists
 *
 * @post returns true if dbExists, false otherwise
 *
 * @par Algorithm 
 *      loop through dbms return true if match is found
 *      
 * @exception None
 *
 * @param [in] dbms provides vector of dbs
 *
 * @param [in] dbInput provides db to be created
 *
 * @return bool
 *
 * @note None
 */
bool databaseExists( vector<Database> dbms, Database dbInput, int &indexReturn )
{
	int size = dbms.size();
	for( indexReturn = 0; indexReturn < size; indexReturn++ )
	{
		if( dbInput.databaseName == dbms[ indexReturn ].databaseName )
		{
			return true;
		}
	}
	return false;
}



void removeDatabase( vector< Database > &dbms, int index )
{
	dbms.erase( dbms.begin() + index );
}


/**
 * @brief handleError
 *
 * @details takes an errorType and outputs an error based off of it
 *          
 * @pre errorType and errorContainerName exist
 *
 * @post outputs error to terminal
 *
 * @par Algorithm 
 *      checks errorTYpe and outputs accordingly
 *      
 * @exception None
 *
 * @param [in] errorType provides an int value of the appropriate error
 *
 * @param [in] errorContainerName provides error source
 *
 * @return None
 *
 * @note None
 */
void handleError( int errorType, string commandError, string errorContainerName )
{

	//convert to lowercase for use
	convertToLC( commandError );

	// if problem is that databse does exist (used for create db )
	if( errorType == ERROR_DB_EXISTS )
	{
		cout << "-- !Failed to " << commandError << " database " << errorContainerName;
		cout << " because it already exists." << endl;
	}
	//if problem is that database does not exist ( used for use, drop)
	else if( errorType == ERROR_DB_NOT_EXISTS )
	{
		cout << "-- !Failed to " << commandError << " database " << errorContainerName;
		cout << " because it does not exist." << endl;
	}
	//if problem is that table exists ( used for create table)
	else if( errorType == ERROR_TBL_EXISTS )
	{
		cout << "-- !Failed to " << commandError << " table " << errorContainerName;
		cout << " because it already exists." << endl;
	}
	//if problem is that table does not exist( used for alter, select, drop )
	else if( errorType == ERROR_TBL_NOT_EXISTS )
	{
		cout << "-- !Failed to " << commandError << " table " << errorContainerName;
		cout << " because it does not exist." << endl;
	}
	//if problem is that an unrecognized error occurs
	else if( errorType == ERROR_INCORRECT_COMMAND )
	{
		cout << "-- !Failed to complete command. "<< endl;
		cout << "-- !Incorrect instruction: " << errorContainerName << endl;
	}
}

void convertToLC( string &input )
{
	int size = input.size();
	for( int index = 0; index < size; index++ )
	{
		input[ index ] = tolower( input[ index ] );
	}
}

