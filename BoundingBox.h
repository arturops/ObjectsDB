#ifndef	__BOUNDINGBOX_H__
#define	__BOUNDINGBOX_H__

#include "BaseObject.h"
#include "GeometryValidator.h"
#include <algorithm>

/**********************************************************************************************/
/*	Class BoundingBox																																					*/
/*  Derived from BaseObject it has same properties and uses them to create groups contained in*/
/*	BoundingBoxes objects																																			*/
/*	It has more function than Box and Cylinder since it needs to contain them (m_boundedObj)	*/
/*	It has a GeometryValidator object to get capability to check for overlaps									*/
/**********************************************************************************************/

class BoundingBox : public BaseObject {
	
	public:
		BoundingBox(int id, int typeID, int groupID, int projectID, std::vector<BaseObject*> baseObjects, eObjType type=eBOUNDINGBOX); //each bounding BOX is a groupID
		BoundingBox(int id, int typeID, int groupID, int projectID, eObjType type=eBOUNDINGBOX); //can create and then fit to selected objects(added using method addObject) later
		~BoundingBox();

		std::vector<BaseObject*> m_boundedObj;
		GeometryValidator 			 m_geomVal;

		virtual double 	getPerimeter(); 
		virtual double 	getArea(); 
		virtual double 	getVolume();

		//recalculates the min and max x,y,z of the bounding box using the contained objects in m_boundedObj
		void fitBoundingBox();//uses m_boundedObj vector and sets MinMaxXYZ bounds
		
		//adds an object to the BoundingBox by storing it in m_boundedObj, then call fitBoundingBox
		virtual void addObject(BaseObject* baseObj);

		//deletes object using its unique nameID to find it
		void deleteObject(std::string nameID);

		//deletes object using its memory location to find it
		virtual bool deleteObject(BaseObject* baseObj);
			
		//finds an object given its unique nameID
		std::vector<BaseObject*>::iterator findObject(std::string nameID);
		
};

#endif