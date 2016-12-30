
#include "BaseObject.h"

BaseObject::BaseObject(){
	m_dminX				= 0;
	m_dminY				= 0;
	m_dminZ				= 0;
	m_dmaxX				= 0;
	m_dmaxY				= 0;
	m_dmaxZ				= 0;
	m_dperimeter	= 0;
	m_darea				= 0;
	m_dvolume			= 0;
	m_stype				= ""; 
	m_enType			= eOBJ_UNKNOWN;
	m_nameid			= "";
	m_id 					= 0;
	m_group				= -1; //undefined NOT GROUP
	m_typeid			= 0;
	m_projectid		= 0;
}

BaseObject::BaseObject(int id, int typeID, int groupID, int projectID, eObjType type) : 
						m_id(id), m_typeid(typeID), m_group(groupID), m_projectid(projectID), m_enType(type){
	m_dminX				= 99999.9;
	m_dminY				= 99999.9;
	m_dminZ				= 99999.9;
	m_dmaxX				= -99999.9;
	m_dmaxY				= -99999.9;
	m_dmaxZ				= -99999.9;
	m_dperimeter	= 0;
	m_darea				= 0;
	m_dvolume			= 0;
	setObjType();
	setObjNameID();
}

BaseObject::BaseObject(int id, int typeID, int groupID, int projectID, std::vector<double> xyz, eObjType type) : 
												m_id(id), m_typeid(typeID), m_group(groupID), m_projectid(projectID), m_enType(type) 
{
	if(xyz.size() >= 6){
		m_dminX = xyz[0];
		m_dminY = xyz[1];
		m_dminZ = xyz[2];
		m_dmaxX = xyz[3];
		m_dmaxY = xyz[4];
		m_dmaxZ = xyz[5];
	}
	else{
		m_dminX				= 0;
		m_dminY				= 0;
		m_dminZ				= 0;
		m_dmaxX				= 0;
		m_dmaxY				= 0;
		m_dmaxZ				= 0;
	}
	setObjType();
	setObjNameID();

}

BaseObject::~BaseObject(){}


void	BaseObject::setObjType(/*ObjType type*/){

	int enumType = (int) m_enType;
	if((int)m_enType > (int)eOBJ_UNKNOWN || (int)m_enType < 0)
		m_stype = "Unknown";
	else
		m_stype = sObjTypes[enumType];
	
}

void	BaseObject::setObjNameID(){

	std::ostringstream strNameID;
	strNameID << m_stype <<"_"<< m_typeid;
	m_nameid =  strNameID.str();

}


std::vector<double> BaseObject::getPoints(){
	std::vector<double> xyzpoints;

	xyzpoints.push_back(m_dminX);
	xyzpoints.push_back(m_dminY);
	xyzpoints.push_back(m_dminZ);
	xyzpoints.push_back(m_dmaxX);
	xyzpoints.push_back(m_dmaxY);
	xyzpoints.push_back(m_dmaxZ);

	return xyzpoints;
}

void BaseObject::setPoints(std::vector<double> xyz){
	
	m_dminX = xyz[0];
	m_dminY = xyz[1];
	m_dminZ = xyz[2];
	m_dmaxX = xyz[3];
	m_dmaxY = xyz[4];
	m_dmaxZ = xyz[5];

}


//------------------------------------------------------------------
//implemented only by BoundingBox (needed access from Base class)
void BaseObject::addObject(BaseObject* baseObj){};
bool BaseObject::deleteObject(BaseObject* baseObj){ return true; }; 