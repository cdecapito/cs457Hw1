#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include "sim.cpp"



using namespace std;

int main()
{
	//get cwd
	char buffer[50];
	getcwd( buffer, sizeof( buffer ) );
	string currentWorkingDirectory( buffer );

	startSimulation( currentWorkingDirectory );

	return 0;
}

