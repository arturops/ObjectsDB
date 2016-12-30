
#include "Test.h"

//starts a database, creates a project and stores objects in DB
void Test::doCreateTest(int projectID){

	std::cout << "\n------------- TEST TO CREATE, COMPARE, STORE AND QUERY DATA --------------\n";

	std::vector<double> xyz,xyz2;
	for(int i=1; i < 7; i++)
		xyz.push_back(i);

	//min
	xyz2.push_back(2);
	xyz2.push_back(1);
	xyz2.push_back(1);
	//max
	xyz2.push_back(6); 
	xyz2.push_back(5);
	xyz2.push_back(4);

	//create Project 0
	std::cout << "-------------Create Project " << projectID <<" --------------\n";
	Project p = Project(projectID,"Project", DefaultDatabase);

	//create the default Table to stoe elements
	p.m_DBmediator.createTable(DefaultElementsTable, DefaultColumnElementsTable);



	//Test to try to create an object in a group that doesn't exist
	std::cout << "-------------Create a 'Box' object in a group that doesn't exist--------------\n";
	p.createObject(xyz, eBOX, 2);

	//create GROUP 0
	p.createGroup();

	std::cout << "\n-------------Check how group's dimensions change to fit contained objects--------------\n";
	std::cout << "\n-Initial bounds";
	std::cout << "\nMIN= "<< p.m_elements["BoundingBox_0"]->m_dminX << ","
												<< p.m_elements["BoundingBox_0"]->m_dminY << ","
												<< p.m_elements["BoundingBox_0"]->m_dminZ	
						<< "\tMAX= "<< p.m_elements["BoundingBox_0"]->m_dmaxX << ","
												<< p.m_elements["BoundingBox_0"]->m_dmaxY << ","
												<< p.m_elements["BoundingBox_0"]->m_dmaxZ
												<< std::endl;

 	std::cout << "\n--Adding the previously created 'Box' to group 0\n";
	p.addObjectToGroup(p.m_elements["Box_0"], 0);
	std::cout << "MIN= "<< p.m_elements["BoundingBox_0"]->m_dminX << ","
												<< p.m_elements["BoundingBox_0"]->m_dminY << ","
												<< p.m_elements["BoundingBox_0"]->m_dminZ	
						<< "\tMAX= "<< p.m_elements["BoundingBox_0"]->m_dmaxX << ","
												<< p.m_elements["BoundingBox_0"]->m_dmaxY << ","
												<< p.m_elements["BoundingBox_0"]->m_dmaxZ
												<< std::endl;

	
	std::cout << "\n--Adding a new 'Cylinder' to group 0\n";
	p.createObject(xyz2, eCYLINDER, 0);
	std::cout << "MIN= "<< p.m_elements["BoundingBox_0"]->m_dminX << ","
												<< p.m_elements["BoundingBox_0"]->m_dminY << ","
												<< p.m_elements["BoundingBox_0"]->m_dminZ	
						<< "\tMAX= "<< p.m_elements["BoundingBox_0"]->m_dmaxX << ","
												<< p.m_elements["BoundingBox_0"]->m_dmaxY << ","
												<< p.m_elements["BoundingBox_0"]->m_dmaxZ
												<< std::endl;

	//creating new groups
	std::cout << "-----------------Creating new groups and objects contained on them------------\n";
	
	//ALL FOLLOWING GROUPS COMPARE INTERSECTION AGAINST GROUP 0
	std::cout << "\n-Group 1\n";
	//GROUP 1 - NO OVERLAPS
	//min
	xyz2[0] = 7; // X
	xyz2[1] = 1; // Y
	xyz2[2] = 8; // Z
	//max
	xyz2[3] = 9; // X 
	xyz2[4] = 3; // Y
	xyz2[5] = 10;// Z
	p.createGroup();
	p.createObject(xyz2, eBOX, 1);
	
	std::cout << "\n-Group 2\n";
	//GROUP 2 - OVERLAPS (ONE BOX CONTAINED INTO ANOTHER)
	xyz2[0] = 2; // X
	xyz2[1] = 2; // Y
	xyz2[2] = 3; // Z
	//max
	xyz2[3] = 4; // X 
	xyz2[4] = 4; // Y
	xyz2[5] = 4; // Z
	p.createGroup();
	p.createObject(xyz2, eBOX, 2);

	std::cout << "\n-Group 3\n";
	//GROUP 3 - ONLY ONE PLANE OVERLAP (SO NO OVERLAP)
	xyz2[0] = 7; // X
	xyz2[1] = 1; // Y
	xyz2[2] = 4; // Z -OVERLAPS
	//max
	xyz2[3] = 9; // X 
	xyz2[4] = 3; // Y
	xyz2[5] = 10;// Z
	p.createGroup();
	p.createObject(xyz2, eBOX, 3);

	std::cout << "\n-Group 4\n";
	//GROUP 4 - OVERLAP (ONE BOX NOT CONTAINED INTO ANOTHER)
	xyz2[0] = 2; // X
	xyz2[1] = 2; // Y
	xyz2[2] = 3; // Z -OVERLAPS
	//max
	xyz2[3] = 4; // X 
	xyz2[4] = 8; // Y
	xyz2[5] = 8; // Z
	p.createGroup();
	p.createObject(xyz2, eBOX, 4);


	//Checking overlapping of all groups agains group 0
	std::cout << "-----------------Checking overlapping of groups 1-4 against group 0 (one by one)------------\n";
	std::cout << "-------CHECK OVERLAP GROUP 0 VS GROUP 1----------" << std::endl;
	if( p.m_geomValidator.check2ObjectsOverlap(p.m_elements["BoundingBox_0"], p.m_elements["BoundingBox_1"]) )
		std::cout << "- OVERLAP -\n" << std::endl;
	else
		std::cout << "- NO OVERLAP -\n" << std::endl;
	
	std::cout << "-------CHECK OVERLAP GROUP 0 VS GROUP 2----------" << std::endl;
	if( p.m_geomValidator.check2ObjectsOverlap(p.m_elements["BoundingBox_0"], p.m_elements["BoundingBox_2"]) )
		std::cout << "- OVERLAP -\n" << std::endl;
	else
		std::cout << "- NO OVERLAP -\n" << std::endl;

	std::cout << "-------CHECK OVERLAP GROUP 0 VS GROUP 3----------" << std::endl;
	if( p.m_geomValidator.check2ObjectsOverlap(p.m_elements["BoundingBox_0"], p.m_elements["BoundingBox_3"]) )
		std::cout << "- OVERLAP -\n" << std::endl;
	else
		std::cout << "- NO OVERLAP -\n" << std::endl;

	std::cout << "-------CHECK OVERLAP GROUP 0 VS GROUP 4----------" << std::endl;
	if( p.m_geomValidator.check2ObjectsOverlap(p.m_elements["BoundingBox_0"], p.m_elements["BoundingBox_4"]) )
		std::cout << "- OVERLAP -\n" << std::endl;
	else
		std::cout << "- NO OVERLAP -\n" << std::endl;


	//Store all elements in DB
	std::cout << "\n-----------------Store all elements in DB------------\n";

	p.m_DBmediator.insertRecords(DefaultElementsTable, p.m_elements["Box_0"]);
	p.m_DBmediator.insertRecords(DefaultElementsTable, p.m_elements["Cylinder_0"]);
	p.m_DBmediator.insertRecords(DefaultElementsTable, p.m_elements["BoundingBox_0"]);

	p.m_DBmediator.insertRecords(DefaultElementsTable, p.m_elements["Box_1"]);
	p.m_DBmediator.insertRecords(DefaultElementsTable, p.m_elements["BoundingBox_1"]);

	p.m_DBmediator.insertRecords(DefaultElementsTable, p.m_elements["Box_2"]);
	p.m_DBmediator.insertRecords(DefaultElementsTable, p.m_elements["BoundingBox_2"]);

	p.m_DBmediator.insertRecords(DefaultElementsTable, p.m_elements["Box_3"]);
	p.m_DBmediator.insertRecords(DefaultElementsTable, p.m_elements["BoundingBox_3"]);

	p.m_DBmediator.insertRecords(DefaultElementsTable, p.m_elements["Box_4"]);
	p.m_DBmediator.insertRecords(DefaultElementsTable, p.m_elements["BoundingBox_4"]);


	std::cout << "\n-----------------Query ALL elements in DB (not only this project) ------------\n";

	std::vector< std::vector<std::string> > result = p.m_DBmediator.selectRecords(DefaultElementsTable);
	for(std::vector< std::vector<std::string> >::iterator it = result.begin(); it<result.end(); ++it){
			std::vector<std::string> row = *it;
			std::cout << "\nValues: ID=" << row.at(0) << 
									 "\tPROJECT_ID=" << row.at(1) << 
									 "\tGROUP_ID=" << row.at(2) <<
									 "\nTYPE=" << row.at(3) << 
									 "\tTYPE_NUM=" << row.at(4) <<
									 "\tOBJ_ID=" << row.at(5) << 
									 "\tOBJNAME_ID=" << row.at(6) << 
									 "\nMIN(X,Y,Z)= ( " << row.at(7) << " , " << row.at(8) <<" , " << row.at(9) << " )"	<<
									 "\nMAX(X,Y,Z)= ( " << row.at(10) << " , " << row.at(11) <<" , " << row.at(12) << " )" <<
									 std::endl;

			
		}


	std::cout << "\n-----------------Query FOR A SPECIFIC GROUP in DB------------\n";
	//Query only for group 4
	result = p.m_DBmediator.selectRecords(DefaultElementsTable,"*"," WHERE OBJNAME_ID like '\%_4'" );
	std::cout << "\nDATABASE MEDIATOR SPECIFIC QUERY" << std::endl;
	for(vector<vector<string> >::iterator it = result.begin(); it<result.end(); ++it){
		vector<string> row = *it;
		std::cout << "\nValues: ID=" << row.at(0) << 
										 "\tPROJECT_ID=" << row.at(1) << 
										 "\tGROUP_ID=" << row.at(2) <<
										 "\nTYPE=" << row.at(3) << 
										 "\tTYPE_NUM=" << row.at(4) <<
										 "\tOBJ_ID=" << row.at(5) << 
										 "\tOBJNAME_ID=" << row.at(6) << 
										 "\nMIN(X,Y,Z)= ( " << row.at(7) << " , " << row.at(8) <<" , " << row.at(9) << " )"	<<
										 "\nMAX(X,Y,Z)= ( " << row.at(10) << " , " << row.at(11) <<" , " << row.at(12) << " )" <<
										 std::endl;
	}

	//closing DB
	std::cout << "\n-----------------Closing DB------------\n";
	p.m_DBmediator.closeDB();

	std::cout << "--------------TEST TO CREATE, COMPARE, STORE AND QUERY DATA COMPLETED!!------------\n";

}

//opens a previously created DB and uses its objects to checks if two groups overlap
void Test::doCheckTest(int projectID){
	
	std::cout << "\n\n===== TEST TO LOAD A PROJECT FROM DB, BUILD ON IT, STORE ONLY NEW DATA AND COMPARE ELEMENTS ======\n";

	std::cout << "\n===== Open Project "<< projectID <<" =====\n"; //created by doCreateTest

	Project p = Project(projectID,"Project", DefaultDatabase);

	if(p.open(p.m_id)) //open project 0 (even if in project 1) - However, current project will be replaced
		std::cout << "----- Opened Project "<< p.m_id <<" SUCCESSFULLY! -----\n";
	else
		std::cout << "----- Opened Project "<< p.m_id <<" FAILED! -----\n";

	//Checking overlapping of all groups agains group 0
	std::cout << "\n============ CONFIRM correct data by checking overlapping of groups 1-4 against group 0 (one by one) ===========\n";
	std::cout << "-------CHECK OVERLAP GROUP 0 VS GROUP 1----------" << std::endl;
	if( p.m_geomValidator.check2ObjectsOverlap(p.m_elements["BoundingBox_0"], p.m_elements["BoundingBox_1"]) )
		std::cout << "- OVERLAP -\n" << std::endl;
	else
		std::cout << "- NO OVERLAP -\n" << std::endl;
	
	std::cout << "-------CHECK OVERLAP GROUP 0 VS GROUP 2----------" << std::endl;
	if( p.m_geomValidator.check2ObjectsOverlap(p.m_elements["BoundingBox_0"], p.m_elements["BoundingBox_2"]) )
		std::cout << "- OVERLAP -\n" << std::endl;
	else
		std::cout << "- NO OVERLAP -\n" << std::endl;

	std::cout << "-------CHECK OVERLAP GROUP 0 VS GROUP 3----------" << std::endl;
	if( p.m_geomValidator.check2ObjectsOverlap(p.m_elements["BoundingBox_0"], p.m_elements["BoundingBox_3"]) )
		std::cout << "- OVERLAP -\n" << std::endl;
	else
		std::cout << "- NO OVERLAP -\n" << std::endl;

	std::cout << "-------CHECK OVERLAP GROUP 0 VS GROUP 4----------" << std::endl;
	if( p.m_geomValidator.check2ObjectsOverlap(p.m_elements["BoundingBox_0"], p.m_elements["BoundingBox_4"]) )
		std::cout << "- OVERLAP -\n" << std::endl;
	else
		std::cout << "- NO OVERLAP -\n" << std::endl;


	std::cout << "===== Create a new group and object with same min,max xyz as group 4=====\n";
	std::vector<double> xyz;
	//min
	xyz.push_back(2); // X
	xyz.push_back(2); // Y
	xyz.push_back(3); // Z 
	//max
	xyz.push_back(4); // X
	xyz.push_back(8); // Y
	xyz.push_back(8); // Z

	p.createGroup();
	p.createObject(xyz, eBOX, p.m_elementsTypeID[eBOUNDINGBOX]-1);


	std::cout << "===== Verifying created group " << p.m_elementsTypeID[eBOUNDINGBOX]-1 << " gives same overlap result as group 4 since they have same bounds ====\n";
	std::cout << "-------CHECK OVERLAP GROUP 0 VS GROUP " << p.m_elementsTypeID[eBOUNDINGBOX]-1 << "----------" << std::endl;
	
	//create the possible nameID of the group that will contain the object
	std::ostringstream strGroupID;
	strGroupID << sObjTypes[eBOUNDINGBOX] << "_" << p.m_elementsTypeID[eBOUNDINGBOX]-1 ;
	std::string nameid =  strGroupID.str();
	//find in the map the name ID of the group
	std::map<std::string,BaseObject*>::iterator it;
	it = p.m_elements.find(nameid);
	if(it!=p.m_elements.end()){
		if( p.m_geomValidator.check2ObjectsOverlap(p.m_elements["BoundingBox_0"], p.m_elements[ nameid]) ) //"BoundingBox_5"]) )
			std::cout << "- OVERLAP -\n" << std::endl;
		else
			std::cout << "- NO OVERLAP -\n" << std::endl;
	}
	else{
		std::cout << "Group '" << p.m_elementsTypeID[eBOUNDINGBOX]-1 << "' not found!\n";
	}


	std::cout << "========== Storing group "<< p.m_elementsTypeID[eBOUNDINGBOX]-1 <<" and its box in DB ==============\n";
	
	if(it!=p.m_elements.end())
		p.m_DBmediator.insertRecords(DefaultElementsTable, p.m_elements[ nameid]); //"Box_5"]);
	else
		std::cout << "Object '" << nameid << "' couldn't be stored, might be already in DB\n";

	std::ostringstream strNameID;
	strNameID << sObjTypes[eBOX] << "_" << p.m_elementsTypeID[eBOUNDINGBOX]-1 ;
	nameid =  strNameID.str();
	it = p.m_elements.find(nameid);
	if(it!=p.m_elements.end())
		p.m_DBmediator.insertRecords(DefaultElementsTable, p.m_elements[nameid]); //"BoundingBox_5"]);
	else
		std::cout << "Object '" << nameid << "' couldn't be stored, might be already in DB\n";

	std::cout << "========== Query ALL elements in DB =======================\n";

	std::ostringstream strProjectID;
	strProjectID << " WHERE PROJECT_ID = " << p.m_id;
	std::string strProjectQuery = strProjectID.str();
	std::vector< std::vector<std::string> > result = p.m_DBmediator.selectRecords(DefaultElementsTable,"*",strProjectQuery);
	for(std::vector< std::vector<std::string> >::iterator it = result.begin(); it<result.end(); ++it){
			std::vector<std::string> row = *it;
			std::cout << "\nValues: ID=" << row.at(0) << 
									 "\tPROJECT_ID=" << row.at(1) << 
									 "\tGROUP_ID=" << row.at(2) <<
									 "\nTYPE=" << row.at(3) << 
									 "\tTYPE_NUM=" << row.at(4) <<
									 "\tOBJ_ID=" << row.at(5) << 
									 "\tOBJNAME_ID=" << row.at(6) << 
									 "\nMIN(X,Y,Z)= ( " << row.at(7) << " , " << row.at(8) <<" , " << row.at(9) << " )"	<<
									 "\nMAX(X,Y,Z)= ( " << row.at(10) << " , " << row.at(11) <<" , " << row.at(12) << " )" <<
									 std::endl;		
	}

	//closing DB
	std::cout << "\n================ Closing DB =================\n";
	p.m_DBmediator.closeDB();

	std::cout << "\n============= TEST TO LOAD A DB PROJECT, KEEP CREATING, COMPARE, STORE AND QUERY DATA COMPLETED!! ============\n";

}

