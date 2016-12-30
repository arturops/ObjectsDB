
#ifndef	__DEFINITIONS_H__
#define __DEFINITIONS_H__

#include <string>
#include <utility> //pair,make_pair

/**********************************************************************************************/
/*	definition.h																																							*/
/*	Contains the default values to initialize the program, the enumerations of type of objects*/
/*	and some types definitions																																*/
/*																																														*/
/**********************************************************************************************/


//Enumeration should match static array fo strings, they correlate to each other
//Unknow type MUST be at the end
enum 	eObjType { eBOUNDINGBOX, eBOX, eCYLINDER, eOBJ_UNKNOWN };
static std::string sObjTypes [eOBJ_UNKNOWN+1] = {"BoundingBox", "Box", "Cylinder", "Unknown"};
static std::string DefaultDatabase = "ObjectsDB.db";
static std::string DefaultElementsTable = "STORED_OBJECTS";
static std::string DefaultProjectsTable = "PROJECTS_LIST"; 

static std::string DefaultColumnElementsTable = 
			"ID 						INT 		NOT NULL,"
		  "PROJECT_ID			INT 		NOT NULL,"
		  "GROUP_ID	  	  INT			NOT NULL,"
		  "TYPE					  TEXT		NOT NULL,"
		  "TYPE_NUM				INT     NOT NULL,"
		  "OBJ_ID 				INT     NOT NULL,"	
		  "OBJNAME_ID		  TEXT		NOT NULL,"	
			"MIN_X					FLOAT		NOT NULL,"
		  "MIN_Y					FLOAT		NOT NULL,"
		  "MIN_Z					FLOAT		NOT NULL,"
		  "MAX_X					FLOAT		NOT NULL,"
		  "MAX_Y					FLOAT		NOT NULL,"
		  "MAX_Z					FLOAT		NOT NULL,"
		  "PRIMARY KEY (PROJECT_ID, OBJNAME_ID)" ;

typedef std::pair<double,double> Point;

/**********************************************************************************************/
/*	Class ElementsRecord																																		  */
/*  Describes a record used in the DefaultElementsTable.																			*/
/*																																														*/
/*																																														*/
/**********************************************************************************************/

class ElementsRecord {

	public:
		int 				id;
		int 				projectID;
		int 				groupID;
		std::string type;
		eObjType 		typeNum;
		int 				objID;
		std::string objNameID;
		std::vector<double> xyz; // 0-minX, 1-minY, 2-minZ, 3-maxX, 4-maxY, 5-maxZ

};


#endif