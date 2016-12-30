
#ifndef __PROJECT_H__
#define	__PROJECT_H__

#include "BaseObject.h"
#include "BoundingBox.h"
#include "Box.h"
#include "Cylinder.h"
#include "DBMediator.h"
#include "GeometryValidator.h"

#include <map> 

/**********************************************************************************************/
/*	Class Project 																																						*/
/*	Requires m_title a TITLE for the project																									*/
/*	Requires m_id an ID which MUST BE UNIQUE FOR EACH PROJECT																	*/
/*	m_elements is a map (tree) that contains all elements of the current project							*/
/*	m_elementsTypeID is a map that contains the ID's to use for groups and objects						*/
/*	m_DBmediator is the object that allows a project to instance the Database									*/
/*	m_geomValidator is the object that allows the project to instance the geometryValidator 	*/
/*		that allows to check groups(BoundingBoxes) are not overlapped										      	*/
/**********************************************************************************************/

class Project {
	
	public:
		std::string												m_title;		// Project's name
		int																m_id;				//project's ID MUST BE UNIQUE FOR EACH PROJECT 
		//int																m_groupsid; //keeps count of latest group id
		// m_elements - map serves to know if repeated items, number of items to give ID of general element in project
		std::map<std::string,BaseObject*> m_elements;
		// m_elementsTypeID  - counts the elements types to give ID's based on element types, allows to have Box_1, Cylinder_1
		std::map<eObjType, int> 					m_elementsTypeID; 
		//m_DBmediator - object to access database functions to query and parse the queries/to open projects
		DBMediator 												m_DBmediator;
		//m_geomValidator - helps the project to know if two groups overlap
		GeometryValidator									m_geomValidator;

		Project(int id, std::string title, std::string DBname);
		~Project();

		//creates group (bounding box)
		bool createGroup(std::vector<BaseObject*> objects = std::vector<BaseObject*>() );
		//add object to current project and DB
		bool createObject(std::vector<double> xyz, eObjType type, int group=-1 );
		//modifies object and object in DB group property
		bool addObjectToGroup(BaseObject* baseObj, int group);
		//deletes an object from database and current project
		bool deleteObject(BaseObject* baseObj);
		//deletes an object from a group
		bool deleteObjectFromGroup(BaseObject* baseObj);
		//retrieve all data/elemets related to the specified ProjectID Project.m_id
		bool open(int projectIDtoOpen);


	private:
		//load from DB the data of a project ID
		bool loadProjectData(int projectIDtoOpen);
		//restores the objects stored in DB into current Project during loading
		void loadObject(ElementsRecord record);

		//ideas to do's:
		// add a bool in BaseObject named 'available' to know if an object was removed from current project
		// but not saved the change
		// add a bool in BaseObject named 'modified' to know if an object was modified in the current project
		// This will lead to ading a 'saveProject' method that uses all flags (avaiable, modified) in every element 
		// of the project
		// if the elements were 'removed' it deletes them from the database; o deleteObject is a temporary remove
		// in the current project
		// if the elements were 'modified' it modifies their records in the DB for future use
		//FOR NOW WE WILL ASSUME ALL OBJECTS NEVER CHANGE AFTER CREATION AND ARE NEVER DELETED

		//In the future a TABLE for the projects can be created. It will store:
		// -Project's ID    //PrimaryKey
		// -Project's Title //PrimaryKey
		// -Number of elements in the project
		// -Number of latest group id

};

#endif