
#include "BoundingBox.h"

BoundingBox::BoundingBox(int id, int typeID, int groupID, int projectID, std::vector<BaseObject*> baseObjects, eObjType type) 
												: BaseObject(id, typeID, groupID, projectID, type), m_boundedObj(baseObjects){
													fitBoundingBox();
												}


BoundingBox::BoundingBox(int id, int typeID, int groupID, int projectID, eObjType type) :
												 BaseObject(id, typeID, groupID, projectID, type){} 


BoundingBox::~BoundingBox(){}


double 	BoundingBox::getPerimeter(){
	m_dperimeter = 10.0;
	return m_dperimeter;
}


double 	BoundingBox::getArea(){
	m_darea = 100.0;
	return m_darea;
}


double 	BoundingBox::getVolume(){
	m_dvolume = fabs(m_dmaxX - m_dminX) * fabs(m_dmaxY - m_dminY) * fabs(m_dmaxZ - m_dminZ);
	return m_dvolume;
}


void BoundingBox::fitBoundingBox(){
	std::cout << "ELEMENTS OF GROUP " << m_group <<" : ";
	for(int i=0; i < m_boundedObj.size();i++){
		std::cout << m_boundedObj[i]->m_nameid << std::endl;
	}
	std::cout << "\n";

	if(m_boundedObj.empty())
		return;

	std::vector<double> xyz = m_geomVal.findMinMaxPoints(m_boundedObj);

	m_dminX = xyz[0];
	m_dminY	= xyz[1];
	m_dminZ	= xyz[2];
	m_dmaxX = xyz[3];
	m_dmaxY = xyz[4];
	m_dmaxZ	= xyz[5];

}


void BoundingBox::addObject(BaseObject* baseObj){
//PROJECT CLASS WILL HAVE A MAP OF ALL OBJECTS AND WILL MODIFY OBJECTS' GROUP WHEN MOVED FROM A TO B
//INCLUDE REMOVING OBJECTS FROM ONE GROUP BEFORE PUTTING INTO ANOTHER
	//basically this function should be a single push_back
	

	if(findObject(baseObj->m_nameid) != m_boundedObj.end() || m_geomVal.checkOverlap(m_boundedObj,baseObj)){//only add obj if not already included and if not overlaps with others
		std::cout << "\nELEMENT ALREADY IN GROUP OR OVERLAPPED!! Number of current elements: " << m_boundedObj.size() << std::endl;
		return;
	}
	//if object belongs to same group already and is not being added to the bounding box yet
	
	if(baseObj->m_group == this->m_group)
		m_boundedObj.push_back(baseObj);
	else if(baseObj->m_group != this->m_group){
		//need to find object in other group and delete it to move it here
		baseObj->m_group = this->m_group; //SHOULD BE HANDLED IN PROJECT CLASS
		m_boundedObj.push_back(baseObj);
	}

	fitBoundingBox();

}


void BoundingBox::deleteObject(std::string nameID){
	std::vector<BaseObject*>::iterator it = findObject(nameID);
	if(it != m_boundedObj.end())
		m_boundedObj.erase(it);
}


bool BoundingBox::deleteObject(BaseObject* baseObj){
	bool bSucc = false;
	int groupSizeBefore = m_boundedObj.size();
	std::vector<BaseObject*>::iterator 	it = findObject(baseObj->m_nameid);
	if(it != m_boundedObj.end())
		m_boundedObj.erase(it);
	if(groupSizeBefore > m_boundedObj.size())
		bSucc = true;

	return bSucc;
}


std::vector<BaseObject*>::iterator BoundingBox::findObject(std::string nameID){
	
	std::vector<BaseObject*>::iterator firstObj = m_boundedObj.begin();
	std::vector<BaseObject*>::iterator lastObj  = m_boundedObj.end();

	if(m_boundedObj.empty())
		return lastObj;

	while (firstObj!=lastObj) {
    	if((*firstObj)->m_nameid == nameID)
    	return firstObj;
    ++firstObj;
  }
  return lastObj; //if not found return 0
}
