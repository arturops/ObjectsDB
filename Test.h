#ifndef __TEST_H__
#define __TEST_H__

#include <iostream>
#include "Database.h"
#include "BaseObject.h"
#include "Box.h"
#include "Cylinder.h"
#include "BoundingBox.h"
#include "definitions.h"
#include "DBMediator.h"

#include "Project.h"

/**********************************************************************************************/
/*	Class Test 																																								*/
/*	Class designed with the purpose of testing some events in the program											*/
/*	More functions can be added in order to test 																							*/
/*																																														*/
/*																																														*/
/*																																														*/
/**********************************************************************************************/

class Test {
	
	public:
		Test(){};
		~Test(){};

		//starts a database, creates a project and stores objects in DB
		void doCreateTest(int projectID);

		//opens a previously created DB, uses its objects to check if two groups overlap, creates a new object
		void doCheckTest(int projectID);


};

#endif