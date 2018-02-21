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
			cout << attr.attributeName << " variables." << endl;
			system( ( "rm " +  filePath ).c_str() ) ;
			fout.close();
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
		cout << attr.attributeName << " variables." << endl;
		system( ( "rm " +  currentDatabase + "/" + tblName ).c_str() ) ;
		fout.close();
		return;
	}

	//push onto vecotr
	tblAttributes.push_back( attr );
	
	//output to file
	fout << attr.attributeName << " ";
	fout << attr.attributeType << endl;
	fout.close();

	cout << "-- Table " << tblName << " created." << endl;
}



void Table::tableDrop( string dbName )
{
	system( ( "rm " +  dbName + "/" + tableName ).c_str() ) ;
	cout << "-- Table " << tableName << " deleted." << endl;
}

void Table::tableAlter( string currentWorkingDirectory, string currentDatabase, string input, bool &errorCode )
{
	vector < Attribute > tableAttributes;
	Attribute attr;
	int commaCount = 0;
	string temp;
	//create filepath  to read from file
	string filePath = "/" + currentDatabase + "/" + tableName;
	ifstream fin( ( currentWorkingDirectory + filePath ).c_str() );

	string action = getNextWord( input );

	if( action == "ADD" )
	{
		while( !fin.eof() )
		{
			Attribute tempAttr;
			fin >> tempAttr.attributeName;
			fin >> tempAttr.attributeType;
			if( !tempAttr.attributeType.empty() && !tempAttr.attributeName.empty() )
			{
				tableAttributes.push_back( tempAttr );
			}
		}

		commaCount = getCommaCount( input );

		ofstream fout( ( currentWorkingDirectory + filePath ).c_str() );
		//get additional attributes
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
			if( attributeNameExists( tableAttributes, attr ) )
			{
				errorCode = true;
				cout << "-- !Failed to modify table " << tableName << " because there are multiple ";
				cout << attr.attributeName << " variables." << endl;
				system( ( "rm " +  filePath ).c_str() ) ;
				return;
			}

			//push attribute onto file
			tableAttributes.push_back( attr );
		}
	
		//remove leading WS from input
		removeLeadingWS( input );
		//parse next two words
		attr.attributeName = getNextWord( input );
		//type is remaining string
		attr.attributeType = input;
		if( attributeNameExists( tableAttributes, attr ) )
		{
			errorCode = true;
			cout << "-- !Failed to modify table " << tableName << " because there are multiple ";
			cout << attr.attributeName << " variables." << endl;
			return;
		}
		//push onto vecotr
		tableAttributes.push_back( attr );

		int tableSize = tableAttributes.size();
		for( int index = 0; index < tableSize; index++ )
		{
			fout << tableAttributes[ index ].attributeName << " ";
			fout << tableAttributes[ index ].attributeType << endl;
		}

		cout << "-- Table " << tableName << " modified." << endl;
	}
	else
	{
		return;
	}
}


void Table::tableSelect( string currentWorkingDirectory, string currentDatabase )
{
	vector< string > attributes;
	string filePath = "/" + currentDatabase + "/" + tableName;
	string temp;
	ifstream fin( ( currentWorkingDirectory + filePath ).c_str() );
	while( !fin.eof() )
	{
		getline( fin, temp);
		if( !temp.empty() )
		{
			attributes.push_back( temp );
		}
	}
	cout << "-- ";
	int size = attributes.size();
	for( int index = 0; index < size; index++ )
	{
		cout << attributes[ index ];
		if( index != size - 1 )
		{
			cout << " | ";
		}
	}
	cout << endl;
}

#endif