
#ifndef	__BOX_H__
#define	__BOX_H__

#include "BaseObject.h"

/**********************************************************************************************/
/*	Class Box																																									*/
/*  Derived from BaseObject it has same properties and uses them to create Box type objects		*/
/*																																														*/
/*																																														*/
/**********************************************************************************************/

class Box : public BaseObject {
	
	public:
		Box(int id, int typeID, int groupID, int projectID, std::vector<double> xyz, eObjType type=eBOX);
		~Box();


		virtual double 	getPerimeter();
		virtual double 	getArea();
		virtual double 	getVolume();



};

#endif