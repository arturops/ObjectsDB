

#include "Database.h"

Database::Database(char * filename)
{
	database = NULL;
	open(filename);
}


//Creating a database
bool Database::open(char* filename)
{
	if(sqlite3_open(filename, &database) == SQLITE_OK)//we create the database
		return true;
	
	return false; //if we fail creating the database
}


vector< vector<string> > Database::query(char* query)
{
	sqlite3_stmt *statement;
	vector< vector<string> > results;

	if(sqlite3_prepare_v2(database, query, -1, &statement, 0) == SQLITE_OK)
	{
		//int cols =  sqlite3_column_count(statement);
		int result = 0;
		while(true)
		{
			result =  sqlite3_step(statement); //if the sqlite3_step finds something matching the query (columns of data) it returns SQLITE_ROW
			
			if(result == SQLITE_ROW)
			{
				//if something found for querying get the amounts of columns of the query
				//usually with SELECT 
				int cols = sqlite3_column_count(statement);
				vector<string> values;
				for(int col = 0; col < cols; col++)
				{
					string text;//text initialized as empty string ""
					char* ptr_txt = (char*)sqlite3_column_text(statement, col);//request for the columns
					if(ptr_txt)//we do this to avoid pushing back NULL to pointer to string 
					{
						text = ptr_txt;
					}	
					values.push_back(text);
				}
				results.push_back(values);
			}
			else
			{
				//if nothing found or the function is CREATE TABLE, INSERT then we have no columns of data for that query
				//we just have to finalize
				break;
			}
		}
		
		sqlite3_finalize(statement);
	}

	string error = sqlite3_errmsg(database);
	if(error != "not an error") //errmsg returns "not an error" if there was no problem with the database query
		cout << query << " " << error << endl;

	return results;
}



void Database::close()
{
	sqlite3_close(database);
}
