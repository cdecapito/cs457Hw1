

#include <iostream>
#include <vector>
#include <string>
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

void startSimulation();
void removeSemiColon( string &input );
bool startEvent( string input, vector< Database> &dbms );
string getAction( string &input );
string getContainer( string &input );
bool databaseExists( vector<Database> dbms, Database dbInput );
void handleError( int errorType, string errorContainerName );




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
void startSimulation()
{
	string input;
	vector< Database > dbms;

	bool simulationEnd = false;
	cout << "-- Expected output" << endl;

	do{
		cout << "> ";
		getline( cin, input );
		//helper function to remove semi colon
		removeSemiColon( input );
		//call helper function to check if modifying db or tbl
		simulationEnd = startEvent( input, dbms );

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
void removeSemiColon( string &input )
{
	input.erase( input.find( ';' ) );
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
bool startEvent( string input, vector< Database> &dbms )
{
	bool exitProgram = false;
	bool errorExists = false;
	int errorType;
	string errorContainerName;
	string actionType = getAction( input );
	string containerType;

	if( actionType.compare( SELECT )  == 0 )
	{

	}
	else if( actionType.compare( USE ) == 0 )
	{

	}
	else if( actionType.compare( CREATE ) == 0 ) 
	{
		containerType = getContainer( input );
		//cout << "TYPE " << input << endl;
		if( containerType == DATABASE_TYPE )
		{
			Database dbTemp;
			//call Create db function
			dbTemp.databaseCreate( input );
			if( databaseExists( dbms, dbTemp ) == true )
			{
				errorExists = true;
				errorContainerName = dbTemp.databaseName;
				errorType = ERROR_DB_EXISTS; 
			}
			else
			{
				cout << "--Database " << dbTemp.databaseName << " created." << endl;
				dbms.push_back( dbTemp );
			}

		}
		else if( containerType == TABLE_TYPE )
		{
			//call create tbl function
		}

	}
	else if( actionType.compare( DROP ) == 0 )
	{
		containerType = getContainer( input );
		if( containerType == DATABASE_TYPE )
		{
			//call drop db function
		}
		else if( containerType == TABLE_TYPE )
		{
			//call drop tbl function
		}

	}
	else if( actionType.compare( ALTER ) == 0 ) 
	{
		containerType = getContainer( input );
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

	if( errorExists )
	{
		handleError( errorType, errorContainerName );
	}

	return exitProgram;
}


/**
 * @brief getAction
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
string getAction( string &input )
{

	string actionType;
	//take first word of input and set as action word
	actionType = input.substr( 0, input.find(" "));
	//erase word from original str to further parse
	input.erase( 0, input.find(" ")+1);

	return actionType;	
}


/**
 * @brief getContainer
 *
 * @details determines whether functionality is performed on DB or TBL
 *          
 * @pre input exists
 *
 * @post returns string of Database or Table
 *
 * @par Algorithm 
 *      Use string find and erase functions
 *      
 * @exception None
 *
 * @param [in] none
 *
 * @param [out] input provides string of command from terminal
 *
 * @return string
 *
 * @note None
 */
string getContainer( string &input )
{
	string actionType;
	//take first word of input and set as container word
	actionType = input.substr( 0, input.find(" "));
	//erase word from original str to further parse
	input.erase( 0, input.find(" ")+1);

	return actionType;	
}



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
bool databaseExists( vector<Database> dbms, Database dbInput )
{
	int size = dbms.size();
	for( int index = 0; index < size; index++ )
	{
		if( dbInput.databaseName == dbms[ index ].databaseName )
		{
			return true;
		}
	}
	return false;
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
void handleError( int errorType, string errorContainerName )
{
	if( errorType == ERROR_DB_EXISTS )
	{
		cout << "--!Failed to create database " << errorContainerName;
		cout << " because it already exists." << endl;
	}
	else if( errorType == ERROR_DB_NOT_EXISTS )
	{

	}
	else if( errorType == ERROR_TBL_EXISTS )
	{

	}
	else if( errorType == ERROR_TBL_NOT_EXISTS )
	{

	}
}