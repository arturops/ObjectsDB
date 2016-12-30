
#ifndef	__CYLINDER_H__
#define	__CYLINDER_H__

#include "BaseObject.h"

/**********************************************************************************************/
/*	Class Cylinder																																						*/
/*  Derived from BaseObject it has same properties and uses them to create Cylinder 					*/
/*	type objects																																							*/
/*																																														*/
/**********************************************************************************************/

class Cylinder : public BaseObject {
	
	public:
		Cylinder(int id, int typeID, int groupID, int projectID, std::vector<double> xyz, eObjType type=eCYLINDER);
		~Cylinder();


		virtual double 	getPerimeter();
		virtual double 	getArea();
		virtual double 	getVolume();



};

#endif