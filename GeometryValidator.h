#ifndef	__GEOMETRYVALIDATOR_H__
#define	__GEOMETRYVALIDATOR_H__

#include "BaseObject.h"

/**********************************************************************************************/
/*	Class GeometryValidator																																		*/
/*  Checks for the overlaps and find MIN,MAX bounduries of groups															*/
/*																																														*/
/*																																														*/
/**********************************************************************************************/

class GeometryValidator {
	
	public:
		GeometryValidator();
		~GeometryValidator();

		//Not implemented yet, but should use an interval tree to check for N rectangles overlaps (intervalQuery)
		bool checkOverlap(std::vector<BaseObject*> baseObjects, BaseObject* b);

		//Checks for overlaps between two 3D objects (so checks for overlaps in XY, YZ and XZ planes)
		bool check2ObjectsOverlap(BaseObject* b1, BaseObject* b2); 

		//Finds MIN and MAX (x,y,z) of a group by comparing the whole MIN and MAX of the objects it contains
		std::vector<double> findMinMaxPoints(std::vector<BaseObject*> baseObjects);

	private:
		//Checks if rectangles overlap by using 2D dimension comparing using 2 point from each rectangle
		bool checkRectangleOverlap(Point b1leftTop, Point b1rightBottom, Point b2leftTop, Point b2rightBottom);


};

#endif