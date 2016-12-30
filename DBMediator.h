
#ifndef __DBMEDIATOR_H__
#define __DBMEDIATOR_H__

#include "Database.h"
#include "BaseObject.h"
#include "definitions.h"

#include <map>

/**********************************************************************************************/
/*	Class DBMediator																																					*/
/*	It is a database mediator between the Database class and the program. It makes queries for*/
/*	the current database and tables easier.										 																*/
/*	m_database -  is the database object to interact with Database.														*/
/*																																														*/
/*																																														*/
/**********************************************************************************************/

class DBMediator {
	
	public:
		Database 	m_database;
		char * 		m_projectTable; 	//not implemented yet
		char * 		m_elementsTable;	//not implemented yet

		//databaseName is the name of the database to connect/create
		DBMediator(std::string databaseName);
		~DBMediator();
		
		//CLOSE current connected database 
		void closeDB();

		//DELETE records specified by a QUERY ---NOT IMPLEMENTED YET
		void deleteRecords(std::string table, std::string columns, std::string extraConditions=";"); 

		//DELETE MANY OBJECTS - uses deleteRecord to iteratively remove record by record contained in the input vector baseObj
		void deleteRecords(std::string table, std::vector<BaseObject*> baseObj);

		//DELETE ONE SINGLE RECORD - removes one record from DB
		void deleteRecord(std::string table, BaseObject* baseObj);

		//UPDATE - update a specfied record with the given information ---NOT IMPLEMENTED YET
		void updateRecords(std::string table, std::string columns, std::string extraConditions=";");

		//INSERT - adds record to database
		void insertRecords(std::string table, BaseObject* b, std::string extraConditions="");

		//SELECT - select records and return a matrix of strings with the query information
		std::vector< std::vector<std::string> > selectRecords(std::string table, std::string columns="*", std::string extraConditions="");

		//PARSE SELECT INTO DATA STRUCTURE BY DATA TYPES - converts the return value of selectRecords into a Record object
		// that has the types of a BaseObject
		std::vector<ElementsRecord> parseSelectRecords( std::vector< std::vector<std::string> >  selectResult);

		//CREATE TABLE - creates a table in the current database
		void createTable(std::string table, std::string columns, std::string extraConditions="");


};

#endif