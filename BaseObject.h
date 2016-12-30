 
#ifndef		__BASEOBJ_H__
#define		__BASEOBJ_H__

#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>

#include <stdlib.h>

#include "definitions.h"

/****************************************************************************************************/
/*	Class BaseObject																																								*/
/*	This class is an interface for all objects that will be created in a project 										*/
/*	It describes the main characteristics every object has:																					*/
/*		m_id 					- ID to index objects in database 																							*/
/*		m_typeid			- ID to index objects of same type, in every group type is unique to each object*/
/*		m_group				- ID to gather objects in a group																								*/
/*										If equal to -1 group number is undefined.																			*/
/*    m_projectid		- ID to gather objects/groups in a project                                      */
/*		m_enType			- Enumeration number that describes the type of object:													*/
/*									0 = BoundingBox, 1 = Box, 2 = Cylinder, 3 = Unknown (not used)									*/
/*    m_stype				- String that describes the type of object/only for user experience             */
/*		m_nameid    	- Unique string for the object composed of m_stype + m_projectid +  m_typeid		*/
/*		m_dminX				- Min x-coordinate value of object in space																			*/
/*		m_dminY				- Min y-coordinate value of object in space																			*/
/*		m_dminZ				- Min z-coordinate value of object in space																			*/
/*		m_dmaxX				- Max x-coordinate value of object in space																			*/
/*		m_dmaxY				- Max x-coordinate value of object in space																			*/
/*		m_dmaxZ				- Max x-coordinate value of object in space																			*/
/*		m_dperimeter 	- Perimeter (not used/implemented)																							*/
/*		m_darea			 	- Area (not used/implemented)																										*/
/*		m_dvolume		 	- Volume (not used/implemented)																									*/
/*																																																	*/
/*																																																	*/
/****************************************************************************************************/
class BaseObject{
	
	public:
		//constructors
		BaseObject();
		BaseObject(int id, int typeID, int groupID, int projectID, eObjType type);
		BaseObject(int id, int typeID, int groupID, int projectID, std::vector<double> xyzpoints, eObjType type);
		
		//virtual destructor in case it needs to be implemented for all objects
		virtual ~BaseObject();

		//Not implemented methods that also maybe not need to be virtual
		//virtual void setMinX(double x);
		//virtual void setMinY(double y);
		//virtual void setMinZ(double z); 

		//Not needed to be virtual
		// getPoints -  returns the current min (x,y,z)  and max (x,y,z) of an object
		virtual std::vector<double> getPoints();
		
		// setPoints - sets the points of an object to the given xyz vector:
		// xyz[0] = minX, xyz[1] = minY, xyz[2] = minZ
		// xyz[3] = maxX, xyz[4] = maxY, xyz[5] = maxZ
		virtual void 		setPoints(std::vector<double> xyz);


		//virtual 
		
		// addObject - inserts an object in a container (BoundingBox) - However, only implemented by containers classes 
		virtual void 		addObject(BaseObject* baseObj);    
		
		// deleteObject - removes an object from a container (BoundingBox) - However, only implemented by containers classes 
		virtual bool 		deleteObject(BaseObject* baseObj); 
		
		//Pure virtual
		//All objects have them declared. However, none of these is implemented
		virtual double 	getPerimeter() = 0;
		virtual double 	getArea() = 0;
		virtual double 	getVolume() = 0;

		//member variables
		std::string m_nameid; 		//ID of object (Name)
		std::string m_stype;			//TYPE of object (Name)
		int					m_group;			//ID of an objects group (if one or more in same group means bounding box = groupID)
		int					m_projectid;	//ID to identify to which project an object belongs
		double 			m_dminX;
		double 			m_dminY;
		double 			m_dminZ;
		double 			m_dmaxX;
		double 			m_dmaxY;
		double 			m_dmaxZ;
		double 			m_dperimeter;	//Perimeter of 2D figure (plane xy, xz, yz)
		double 			m_darea;			//Area of 2D figure (plane xy, xz, yz)
		double 			m_dvolume;		//Volume ocuppied by object (can be 0 if 2D)
		int					m_typeid;			//ID of object (type related) in the project. Can be same as m_id in some cases
		int					m_id; 				//ID of object (not type related) in the project(Number)
		eObjType 		m_enType;			//TYPE of object (Number)
		

		/*****************************************************/
		/*	Sets the object type string using the int number */
		/*	that determines the enum TYPE 									 */
		/*****************************************************/
		virtual void		setObjType(/*ObjType type*/);

		/***************************************************/
		/* Sets the name ID of object using it ID and Type */
		/***************************************************/
		virtual void		setObjNameID();


};

#endif