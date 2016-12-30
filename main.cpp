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
	// 1. Implement LoadProjectData (build the map from the query and construct all objects) MAYBE THIS FUNCTION SHOULD 
	// BE INSIDE Project class. This makes a query and gets vector<vector<string>> and populates its own map and 
	// the map for ELEMENTS ID. 
	//
	// 1.b. While the map is created make sure that the bounding boxes contain the elements they had
	//
	// 1.c. VERIFY THE BOUNDING BOXES AND ALL OBJECTS HAVE THE RIGHT NUMBER (IDS) THEY USED TO HAVE  
	//
	// 2. Perform overlap checks of bounding boxes after retrieving them from DB
	//
	// 3. Create a store function to store values in DB (MAYBE NOT UPDATE CAN BE DONE YET, ONLY NEW OBJECTS ACCEPTED) 
	//
	// 4. Create Menu and options to allow people to load project or create new one
	//

}
