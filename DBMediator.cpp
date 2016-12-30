
#include "DBMediator.h"

		DBMediator::DBMediator(std::string databaseName) : m_database(const_cast<char *> (databaseName.c_str()) ){};
		DBMediator::~DBMediator(){};

		//close
		void DBMediator::closeDB(){
			m_database.close();
		}
		
		//DELETE
		void DBMediator::deleteRecords(std::string table, std::string columns, std::string extraConditions){

		} 

		//DELETE MANY OBJECTS
		void DBMediator::deleteRecords(std::string table, std::vector<BaseObject*> baseObj){
			for(int r=0; r<baseObj.size(); r++){
				deleteRecord(table, baseObj[r]);
			}

		}

		//DELETE ONE SINGLE RECORD
		void DBMediator::deleteRecord(std::string table, BaseObject* baseObj){
			std::ostringstream strQuery;
			strQuery << "DELETE FROM " << table << " WHERE ID = " << baseObj->m_id << " AND PROJECT_ID = " <<
									baseObj->m_projectid << " AND OBJNAME_ID = '" << baseObj->m_nameid <<"';";
			m_database.query(const_cast<char *> (strQuery.str().c_str()));					  
		}


		//UPDATE
		void DBMediator::updateRecords(std::string table, std::string columns, std::string extraConditions){

		}

		//INSERT
		void DBMediator::insertRecords(std::string table, BaseObject* b, std::string extraConditions){
			std::ostringstream strQuery;
			strQuery << "INSERT INTO " << table << " VALUES("<<
				b->m_id << "," << b->m_projectid << ","<< b->m_group <<",'" << b->m_stype << "'," << 
				(int)b->m_enType <<","<< b->m_typeid << ",'" << b->m_nameid << "'," << b->m_dminX << 
				"," << b->m_dminY << "," << b->m_dminZ << "," <<
				b->m_dmaxX << "," << b->m_dmaxY << "," << b->m_dmaxZ << ");";
			m_database.query(const_cast<char *> (strQuery.str().c_str()));
		}

		//SELECT
		std::vector< std::vector<std::string> > DBMediator::selectRecords(std::string table, std::string columns, std::string extraConditions){
			std::ostringstream strQuery;
			strQuery << "SELECT " << columns <<  " FROM " << table << " " << extraConditions  << ";";
			std::vector< std::vector<std::string> > results = m_database.query(const_cast<char *> (strQuery.str().c_str()));
			return results;
		}

		//PARSE SELECT INTO DATA STRUCTURE BY DATA TYPES
		std::vector<ElementsRecord> DBMediator::parseSelectRecords( std::vector< std::vector<std::string> >  selectResult){
			std::vector<ElementsRecord> records;
			for( std::vector< std::vector<std::string> > ::iterator it = selectResult.begin(); it<selectResult.end(); ++it){
				ElementsRecord record;
				record.id 				= atoi((*it).at(0).c_str());
				record.projectID 	= atoi((*it).at(1).c_str());
				record.groupID 		=	atoi((*it).at(2).c_str());
				record.type 			= (*it).at(3);
				record.typeNum 		=	(eObjType)atoi((*it).at(4).c_str());
				record.objID 			=	atoi((*it).at(5).c_str());
				record.objNameID 	= (*it).at(6);
				record.xyz.push_back( atof((*it).at(7).c_str())  );
				record.xyz.push_back( atof((*it).at(8).c_str())  );
				record.xyz.push_back( atof((*it).at(9).c_str())  );
				record.xyz.push_back( atof((*it).at(10).c_str()) );
				record.xyz.push_back( atof((*it).at(11).c_str()) );
				record.xyz.push_back( atof((*it).at(12).c_str()) );

				records.push_back(record);
			}

			return records;
		}

		//CREATE TABLE
		void DBMediator::createTable(std::string table, std::string columns, std::string extraConditions){
			std::ostringstream strQuery;
			strQuery << "CREATE TABLE " << table << "(" << columns << extraConditions << ");";
			m_database.query(const_cast<char *> (strQuery.str().c_str())); //MAKING 'const char *' a 'char *'
	
		}