
#include "Box.h"


Box::Box(int id, int typeID, int groupID, int projectID, std::vector<double> xyz, eObjType type) :
				 BaseObject(id, typeID, groupID, projectID, xyz, type){}

Box::~Box(){}

double 	Box::getPerimeter(){
	m_dperimeter = 10.0;
	return m_dperimeter;
}

double 	Box::getArea(){
	m_darea = 100.0;
	return m_darea;
}

double 	Box::getVolume(){
	m_dvolume = fabs(m_dmaxX - m_dminX) * fabs(m_dmaxY - m_dminY) * fabs(m_dmaxZ - m_dminZ);
	return m_dvolume;
}