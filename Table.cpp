#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include "Table.h"

using namespace std;

#ifndef TABLE_CPP
#define TABLE_CPP

int getCommaCount( string str )
{
	int length = str.length();
	int count = 0;
	for( int index = 0; index < length; index++ )
	{
		//look for num of commas
		if( str[ index ] == ',' )
		{
			count ++;
		}
	}
	return count;
}
string getNextWord( string &input )
{

	string actionType;
	//take first word of input and set as action word
	actionType = input.substr( 0, input.find(" "));
	//erase word from original str to further parse
	input.erase( 0, input.find(" ") + 1 );

	return actionType;	
}

void removeLeadingWS( string &input )
{
	int index = 0;
	while( input[ index ] == ' ' )
	{ 
		index++;
	}

	input.erase( 0, index );
}

bool attributeNameExists( vector< Attribute > attributeTable, Attribute attr )
{
	int size = attributeTable.size();
	for( int index = 0; index < size; index++ )
	{
		if( attributeTable[ index ].attributeName == attr.attributeName )
		{
			return true;
		}
	}
	return false;
}


Table::Table()
{

}
Table::~Table()
{

}

void Table::tableCreate( string currentWorkingDirectory, string currentDatabase, string tblName, string input, bool &errorCode )
{
	vector< Attribute> tblAttributes;
	Attribute attr;
	string temp;
	int commaCount;

	//get filepath, Database name + table name
	string filePath = "/" + currentDatabase + "/" + tblName;
	//output to file using ofstream operator
	ofstream fout( ( currentWorkingDirectory + filePath ).c_str() );

	//parse input str
		//remove beginning and end ()'s
		//get first open paren
	input.erase( 0, input.find( "(" ) + 1 );
	input.erase( input.find_last_of( ")" ), input.length()-1 );

	commaCount = getCommaCount( input );

	for( int index = 0; index < commaCount; index++ )
	{
		//remove beginning parameter
		temp = input.substr( 0, input.find( "," ));
		input.erase( 0, input.find(",") + 1 );
		//remove leading white space
		removeLeadingWS( temp );
		//parse, get next two words
		attr.attributeName = getNextWord( temp );
		attr.attributeType = getNextWord( temp );

		//check that variable name does not already exist
		if( attributeNameExists( tblAttributes, attr ) )
		{
			errorCode = true;
			cout << "-- !Failed to create table " << tblName << " because there are multiple ";
			cout << attr.attributeName << " variable's." << endl;
			system( ( "rm " +  filePath ).c_str() ) ;
			return;
		}

		//push attribute onto file
		tblAttributes.push_back( attr );

		//output to file
		fout << attr.attributeName << " ";
		fout << attr.attributeType << endl;
	}
	
	//remove leading WS from input
	removeLeadingWS( input );
	//parse next two words
	attr.attributeName = getNextWord( input );
	//type is remaining string
	attr.attributeType = input;
	if( attributeNameExists( tblAttributes, attr ) )
	{
		errorCode = true;
		cout << "-- !Failed to create table " << tblName << " because there are multiple ";
		cout << attr.attributeName << " variable's." << endl;
		system( ( "rm " +  currentDatabase + "/" + tblName ).c_str() ) ;
		return;
	}

	//push onto vecotr
	tblAttributes.push_back( attr );
	
	//output to file
	fout << attr.attributeName << " ";
	fout << attr.attributeType << endl;

	cout << "-- Table " << tblName << " created." << endl;
}



void Table::tableDrop( string input )
{

}
void Table::tableAlter( string input )
{

}
void Table::tableSelect( string input )
{

}

#endif