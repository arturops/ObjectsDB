
#include "Project.h"


Project::Project(int id, std::string title, std::string DBname) : m_id(id), m_title(title), m_DBmediator (DBname){
	//open();
}

Project::~Project(){
	//deallocates memory to avoid memory leaks after a project is closed
	if(!m_elements.empty()){
		std::map<std::string,BaseObject*>::iterator it;
		for(it = m_elements.begin(); it!=m_elements.end();it++){
			delete it->second; //deallocates the BaseObject pointers
		}
	}
}

bool Project::createGroup(std::vector<BaseObject*> objects){
	bool bSucc = false;
	BaseObject * baseObj = nullptr;
	//int id, int typeID, int groupID, int projectID, std::vector<BaseObject*> baseObjects, eObjType type)
	if(!objects.empty())
		baseObj =  new BoundingBox(m_elements.size(), m_elementsTypeID[eBOUNDINGBOX], m_elementsTypeID[eBOUNDINGBOX], m_id, objects);	
	else
		baseObj =  new BoundingBox(m_elements.size(), m_elementsTypeID[eBOUNDINGBOX], m_elementsTypeID[eBOUNDINGBOX], m_id);	

	if(baseObj){
		m_elementsTypeID[eBOUNDINGBOX]++;
		bSucc = true;
		m_elements[baseObj->m_nameid] = baseObj;
	}

	return bSucc;
}


bool Project::createObject(std::vector<double> xyz, eObjType type, int group){
	bool bSucc = false;
	BaseObject * baseObj = nullptr;

	//keep m_elementsTypeID[eBOUNDINGBOX] as the groupsID counter
	if(group > m_elementsTypeID[eBOUNDINGBOX]){
		std::cout << "\nGroup number not found!" << std::endl;
		group = -1; //objects that do not need to be in a bounding box need to be group -1
	}

	switch(type){
			//case eBOUNDINGBOX:
			//	baseObj = &BoundingBox(m_groupsid, m_id, type);
			//	break;

			case eBOX:
				baseObj = new Box(m_elements.size(), m_elementsTypeID[eBOX]++, group, m_id, xyz);
				break;

			case eCYLINDER:
			//int id, int typeID, int groupID, int projectID, std::vector<double> xyz, eObjType
				baseObj = new Cylinder(m_elements.size(), m_elementsTypeID[eCYLINDER]++, group, m_id, xyz);
				break;

			case eBOUNDINGBOX:
			case eOBJ_UNKNOWN:
			default:
				break;

	}//end switch

	
	
	if(baseObj){
		bSucc = true;
		if(group != -1)//add element to a group if element has group
			bSucc = addObjectToGroup(baseObj, group);	
		m_elements[baseObj->m_nameid] = baseObj;
	}

/* //IN THEORY I CANT NEVER CREATE A REPEATED OBJECT SINCE 
	 // THE PROGRAM WILL BE CREATING ID'S INCREMENTALLY - IF NEED TO REUSE THEM THEN 
	 // A NEW IMPLEMENTATION WILL BE NEEDED
	std::map<std::string,BaseObject*>::iterator it;
	//create the possible nameID for the object to be created
	std::ostringstream strNameID;
	strNameID << sObjTypes[type] <<"_"<< type;
	std::string nameid =  strNameID.str();
	//find in the map the name ID
	it = m_elements.find(nameid);
	//if not found create a new object else return false
  if (it == mymap.end()){
		switch(type){
			//case eBOUNDINGBOX:
			//	baseObj = &BoundingBox(m_groupsid, m_id, type);
			//	break;

			case eBOX:
				//int id, int typeID, int groupID, int projectID, std::vector<double> xyz, eObjType
				if(group <= m_groupsid){
					baseObj = &Box(m_elements.size(), m_elementsTypeID[eBOX]++, group, m_id);
					bSucc = addObjectToGroup(baseObj);
				}
				else{
					std::cout << "\nGROUP " << group << " NOT AVAILABLE, DEFAULTING TO GROUP " << m_groupsid << std::endl;
					bSucc = createGroup();
					baseObj = &Box(m_elements.size(), m_elementsTypeID[eBOX]++, m_groupsid, m_id);
				}


		}
	}
	else{
		std::cout << "\nOBJECT ALREADY EXISTS" << std::endl;
	}
*/
	return bSucc;
}

//OBJECTS CAN ONLY EXIST IN ONE GROUP
//Add objects to one group and removes it from another if it already exists there
bool Project::addObjectToGroup(BaseObject* baseObj, int group){
	bool bSucc = true;
	if(group == -1 || group > m_elementsTypeID[eBOUNDINGBOX]){
		std::cout << "\nGroup number not found!" << std::endl;
		bSucc = false;
		//return bSucc; //
	}

	//if object existed already and was in another group. Object needs to be removed from old group
	if(baseObj->m_group > -1 && baseObj->m_group <= m_elementsTypeID[eBOUNDINGBOX] &&  baseObj->m_group != group){
		bSucc = deleteObjectFromGroup(baseObj);
	}
	
	if(bSucc){
		std::map<std::string,BaseObject*>::iterator it;
		//create the possible nameID of the group that will contain the object
		std::ostringstream strGroupID;
		strGroupID << sObjTypes[eBOUNDINGBOX] << "_" << group ;
		std::string groupid =  strGroupID.str();
		//find in the map the name ID of the group
		it = m_elements.find(groupid);
		//if found add object to group else return false
		if (it != m_elements.end()){
			baseObj->m_group = it->second->m_group;
			it->second->addObject(baseObj);//assume we add it successfully (NEED TO ADD RETURN BOOL TYPE)
		}
 	}

  return bSucc;
}


bool Project::deleteObject(BaseObject* baseObj){
	bool bSucc = false;
	std::map<std::string,BaseObject*>::iterator it;
	//create the possible nameID of the group that may contain the object
	std::ostringstream strGroupID;
	strGroupID << sObjTypes[eBOUNDINGBOX] <<"_"<< baseObj->m_group;
	std::string groupid =  strGroupID.str();
	it = m_elements.find(groupid);
	if(it != m_elements.end()){
		m_elements.erase(it); //removes from Project's map
		bSucc = it->second->deleteObject(baseObj); //removes from group
		m_DBmediator.deleteRecord(DefaultElementsTable, baseObj); //removes from DB
	}

	return bSucc;

}


bool Project::deleteObjectFromGroup(BaseObject* baseObj){
	bool bSucc = false;
	std::map<std::string,BaseObject*>::iterator it;
	//create the possible nameID of the group that may contain the object
	std::ostringstream strGroupID;
	strGroupID << sObjTypes[eBOUNDINGBOX] <<"_"<< baseObj->m_group;
	std::string groupid =  strGroupID.str();
	it = m_elements.find(groupid);
	if(it != m_elements.end()){
		bSucc = it->second->deleteObject(baseObj);
	}

	return bSucc;
}


bool Project::open(int projectIDtoOpen){
	m_id = projectIDtoOpen;
	return loadProjectData(projectIDtoOpen);
	//return true;
}

void Project::loadObject(ElementsRecord r){
	
	BaseObject * baseObj = nullptr;
	/*	int 				id;
		int 				projectID;
		int 				groupID;
		std::string type;
		int 				typeNum;
		int 				objID;
		std::string objNameID;
		std::vector<double> xyz; */

	switch(r.typeNum){

			case eBOUNDINGBOX:
			//int id, int typeID, int groupID, int projectID, std::vector<BaseObject*> baseObjects, eObjType type)
				baseObj = new BoundingBox(r.id, r.objID, r.groupID,r.projectID);
				m_elementsTypeID[eBOUNDINGBOX]++;
				break;

			//int id, int typeID, int groupID, int projectID, std::vector<double> xyz, eObjType
			case eBOX:
				baseObj = new Box(r.id, r.objID, r.groupID, r.projectID,r.xyz);
				m_elementsTypeID[eBOX]++;
				break;

			case eCYLINDER:
				baseObj = new Cylinder (r.id, r.objID, r.groupID, r.projectID,r.xyz);
				m_elementsTypeID[eCYLINDER]++;
				break;

			case eOBJ_UNKNOWN:
			default:
				break;

	}//end switch

	
	if(baseObj){
		//bSucc = true;
		std::cout << baseObj->m_id <<". " << baseObj->m_nameid << " LOADED SUCCESSFULLY!" <<std::endl;
		if(baseObj->m_group != -1 && baseObj->m_enType != eBOUNDINGBOX)//add element to a group if element has group
			/*bSucc =*/ addObjectToGroup(baseObj, baseObj->m_group);	
		m_elements[baseObj->m_nameid] = baseObj;
	}

}


bool Project::loadProjectData(int projectIDtoOpen){
	
	//clearing project maps before loading new ones
	m_elements.clear();
	m_elementsTypeID.clear();

	std::vector< std::vector <std::string> > result;
	std::ostringstream strExtraConditions;
	strExtraConditions << " WHERE PROJECT_ID = " << projectIDtoOpen << " ORDER BY GROUP_ID";
	result = m_DBmediator.selectRecords(DefaultElementsTable,"*", strExtraConditions.str());

	std::vector<ElementsRecord> records = m_DBmediator.parseSelectRecords(result);
	//m_id = records[0].projectID;
	//populate maps of the project
	
	//create groups first
	//create objects into its respective group

	//create groups first and store the records left in a vector
	std::vector<ElementsRecord> objects;
	for(int r =0; r<records.size(); r++){
		if(records[r].typeNum == eBOUNDINGBOX){
			m_elementsTypeID[eBOUNDINGBOX] = records[r].groupID;
			loadObject(records[r]);
		}
		else{
			objects.push_back(records[r]);
		}
	}

	for(int r =0; r<objects.size(); r++){
		m_elementsTypeID[objects[r].typeNum] = objects[r].objID;
		loadObject(objects[r]);
	}

	//adding one to all elements of m_elementsTypeID since the load only gives the latest used, but
	//this variables stores the next value to use to create groups and objects
	//std::map<eObjType, int>::iterator it;
	//for(it=m_elementsTypeID.begin(); it!=m_elementsTypeID.end(); it++){
	//	it->second++;
	//}
	//m_elementsTypeID[eOBJ_UNKNOWN]--;

  std::cout << "Loaded Data:\n-" << m_elementsTypeID[eBOUNDINGBOX] << " Groups\n-"
  					<< m_elementsTypeID[eBOX] << " Boxes\n-" << m_elementsTypeID[eCYLINDER] << " Cylinders" 
  					<< std::endl;

	if(m_elements.empty())
		return false;
	return true;
}

