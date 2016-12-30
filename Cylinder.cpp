
#include "Cylinder.h"

Cylinder::Cylinder(int id, int typeID, int groupID, int projectID, std::vector<double> xyz, eObjType type) :
										 BaseObject(id, typeID, groupID, projectID, xyz, type){}

Cylinder::~Cylinder(){}

double 	Cylinder::getPerimeter(){
	m_dperimeter = 0.0;
	return m_dperimeter;
}

double 	Cylinder::getArea(){
	m_darea = 100.0 * 3.1416 + 100.0;
	return m_darea;
}

double 	Cylinder::getVolume(){
	m_dvolume = fabs(m_dmaxX - m_dminX) * fabs(m_dmaxY - m_dminY) * fabs(m_dmaxZ - m_dminZ);
	return m_dvolume;
}
