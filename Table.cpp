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


Table::Table()
{

}
Table::~Table()
{

}

void Table::tableCreate( string currentWorkingDirectory, string currentDatabase, string tblName, string input )
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
	/*
		//remove beginning and end ()'s
		//get first open paren
	input.erase( 0, input.find( "(" ) + 1 );
	input.erase( input.find_last_of( ")" ), input.length()-1 );

	commaCount = getCommaCount( input );

	for( int index = 0; index < commaCount; index++ )
	{
		temp = input.substr( 0, input.find( "," ));
		input.erase( 0, input.find(",") + 1 );
		attr.attributeName = getNextWord( temp );
		attr.attributeType = getNextWord( temp );
		fout << attr.attributeName << " ";
		fout << attr.attributeType << endl;
	}
	
	attr.attributeName = getNextWord( input );
	attr.attributeType = getNextWord( input );
	fout << attr.attributeName << " ";
	fout << attr.attributeType << endl;
	*/
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