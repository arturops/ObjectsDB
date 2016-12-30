#include <iostream>
#include "Database.h"
#include "BaseObject.h"
#include "Box.h"
#include "Cylinder.h"
#include "BoundingBox.h"
#include "definitions.h"
#include "DBMediator.h"

#include "Project.h"

#include "Test.h"

/**********************************************************************************************/
/*	NOTES																																											*/
/* 	This program currently																																		*/
/*  + Does NOT delete objects from database	(function is implemented, but not used)						*/
/*	+ Does NOT resuses previous ID's of deleted Objects (no point deleting objects yet). If	  */
/*		 an object want to be removed from a group permanently and do not add it to another 		*/
/*		 group, addObjectToGroup: -1 = groupID																									*/
/*	+ Does NOT update records in database of objects previously stored												*/
/*	+ Stores in and retrieves records from Database																						*/
/*	+ Verifies overlapping between two objects using a simple comparison 1 to 1 of rectangles */
/*  + Uses a SQlite Database 																																	*/
/*																																														*/

/**********************************************************************************************/


int main(int argc, char** argv)
{

	Test t = Test();
	if(argc != 2){
		std::cout << "USE: ~$./ObjectDB [number of Project to Create and Open]" <<std::endl;
		return 0;
	}
	int projectID = atoi(argv[1]);
	t.doCreateTest(projectID);
	t.doCheckTest(projectID);

	//TO DO'S 
	// 1. Create a store function to store values in DB (MAYBE NOT UPDATE CAN BE DONE YET, ONLY NEW OBJECTS ACCEPTED) 
	//
	// 2. Create Menu and options to allow people to load project or create new one
	//

}
