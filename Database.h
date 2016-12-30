//
//Class created to CREATE TABLE (create a database), INSERT, SELECT

#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>

using namespace std;

/**********************************************************************************************/
/*	Class Database																																						*/
/*	This is the core class that allows the interaction with SQLite databases.									*/
/*	Requires a databaseName to either open or create a database.															*/
/*	It performs queries																																				*/
/*																																														*/
/*																																														*/
/**********************************************************************************************/

class Database
{
	public:
		Database(char * filename);
		~Database(){};
		
		//creates/connects to a database
		bool open(char* filename);

		//query a database using the statement given as char* query
		vector< vector<string> > query(char* query);

		//closes database
		void close();

	private:
		sqlite3 *database;

};//end header

#endif
