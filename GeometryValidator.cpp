
#include "GeometryValidator.h"

GeometryValidator::GeometryValidator(){};
GeometryValidator::~GeometryValidator(){};


bool GeometryValidator::checkOverlap(std::vector<BaseObject*> baseObjects, BaseObject* b){ 
	//Future Implementation to find overlaps of N rectangles 
	// + This requires an BS INTERVAL TREE and the implementation of a SWEEPING LINE ALGORITHM (modified to do 
	// intervalSearch instead of rangeSearch)
	// STEPS
	// + Build a BST that contains intervals, use the lowebound of an interval as the key of the tree
	// + Try that the tree is balanced (AVL tree or RedBlack to ensure this) so that interval query is O(nlogn + Rlogn)
	// R = number of intersections
	// + The inserts and deletes are similar to a BST. It takes time to complete a full RB tree. Maybe use array sort it
	// then build the three using middle of the array as root. Then query for interval intersection and do not mantain tree
	// should be around O(nlogn) to build tree and the interval query still takes O(nlogn + Rlogn) thus this is an option
	// to avoid RB tree in this case (tree will be balanced since array sorted and median will be the root)
	// + The augmented BST (made interval tree) needs to store the max high bound of its subtree in every node. This,
	// to help decide wether is left or right the path to follow during the interval query.
	// + This approach helps to have a data structure that can add intervals of many rectangles and query for intersections.
	// MOST LIKELY we only care about first intersection and then return true for intersection happened. the figure
	// that wants to be added is rejected

	return false;//if true objects overlap
}
		


/******************************************************************/
/* OVERLAP CHECK USING 2D POINTS AND PLANES XY,XZ,YZ						 	*/
/*																															 	*/
/*     B1-LT																										 	*/
/*						X-----------------+															 		*/
/*						|         B2-LT   |																	*/
/*						|            X----|-------+													*/
/*						|						 |		|				|													*/
/*						|						 |		|				|													*/
/*						|						 +----|-------X B2-RB										*/
/*						|									|																	*/
/*						+-----------------X B1-RB														*/
/*																																*/
/* B1-LT : BaseObject 1, Left Top side point 							 				*/
/* B1-RB : BaseObject 1, Right Bottom side point									*/
/* B2-LT : BaseObject 2, Left Top side point	 						 				*/
/* B2-RB : BaseObject 2, Right Bottom side point									*/
/*																																*/
/* if (B2-LT x-coordinate < B1-RB x-coordinate) &&	 							*/
/* B2-LT y-coordinate >= B1-RB y-coordinate && 										*/
/* B2-LT y-coord  <= B1-LT y-coordinate then we have an overlap.  */
/******************************************************************/
	//bool checkRectangleOverlap(std::pair<double,double> b1leftTop, std::pair<double,double> b1rightBottom, std::pair<double,double> b2leftTop, std::pair<double,double> b2rightBottom){
	bool GeometryValidator::checkRectangleOverlap(Point b1leftTop, Point b1rightBottom, Point b2leftTop, Point b2rightBottom){
		bool boverlap = true;

		// If one rectangle is on left side of other
    if (b1leftTop.first > b2rightBottom.first || b2leftTop.first > b1rightBottom.first) 
        return false;
 
    // If one rectangle is above other
    if (b1leftTop.second < b2rightBottom.second || b2leftTop.second < b1rightBottom.second)
        return false;

		return boverlap;
	}

bool GeometryValidator::check2ObjectsOverlap(BaseObject* b1, BaseObject* b2){

bool bxy = false;

Point b1leftXY 	= std::make_pair(b1->m_dminX,b1->m_dmaxY); //top left rectangle 1
Point b1rightXY = std::make_pair(b1->m_dmaxX,b1->m_dminY); //bottom right rectangle 1
Point b2leftXY 	= std::make_pair(b2->m_dminX,b2->m_dmaxY); //top left rectangle 2
Point b2rightXY = std::make_pair(b2->m_dmaxX,b2->m_dminY); //bottom right rectangle 2

bxy = checkRectangleOverlap(b1leftXY,b1rightXY,b2leftXY,b2rightXY);
if(!bxy)
	return false; //overlap wont exist MUTS OVERLAP IN THE THREE PLANES

bool byz = false;

Point b1leftYZ 	= std::make_pair(b1->m_dminY,b1->m_dmaxZ); //top left rectangle 1
Point b1rightYZ = std::make_pair(b1->m_dmaxY,b1->m_dminZ); //bottom right rectangle 1
Point b2leftYZ 	= std::make_pair(b2->m_dminY,b2->m_dmaxZ); //top left rectangle 2
Point b2rightYZ = std::make_pair(b2->m_dmaxY,b2->m_dminZ); //bottom right  rectangle 2

byz = checkRectangleOverlap(b1leftYZ,b1rightYZ,b2leftYZ,b2rightYZ);

if(!byz)
	return false; //overlap wont exist MUTS OVERLAP IN THE THREE PLANES

bool	bxz = false;

Point b1leftXZ 	= std::make_pair(b1->m_dminX,b1->m_dmaxZ); //top left rectangle 1
Point b1rightXZ = std::make_pair(b1->m_dmaxX,b1->m_dminZ); //bottom right rectangle 1
Point b2leftXZ 	= std::make_pair(b2->m_dminX,b2->m_dmaxZ); //top left rectangle 2
Point b2rightXZ = std::make_pair(b2->m_dmaxX,b2->m_dminZ); //bottom right  rectangle 2

bxz = checkRectangleOverlap(b1leftXZ,b1rightXZ,b2leftXZ,b2rightXZ);

	return bxy & byz & bxz; // if an object overlaps in 3D imposible to only overlap in 2 planes.MUST OVERLAP IN ALL 3 PLANES //false;//if true objects overlap
}
		
std::vector<double> GeometryValidator::findMinMaxPoints(std::vector<BaseObject*> baseObjects){
	
	double 	minX = 99999.9,
					minY = 99999.9,
					minZ = 99999.9,
					maxX = -99999.9,
					maxY = -99999.9,
					maxZ = -99999.9;

	for(int obj=0; obj < baseObjects.size(); obj++){
			if(minX > baseObjects[obj]->m_dminX)
				minX = baseObjects[obj]->m_dminX;

			if(minY > baseObjects[obj]->m_dminY)
				minY = baseObjects[obj]->m_dminY;

			if(minZ > baseObjects[obj]->m_dminZ)
				minZ = baseObjects[obj]->m_dminZ;

			if(maxX < baseObjects[obj]->m_dmaxX)
				maxX = baseObjects[obj]->m_dmaxX;

			if(maxY < baseObjects[obj]->m_dmaxY)
				maxY = baseObjects[obj]->m_dmaxY;

			if(maxZ < baseObjects[obj]->m_dmaxZ)
				maxZ = baseObjects[obj]->m_dmaxZ;
	}

	std::vector<double> xyz(6,0.0);

	xyz[0] = minX;//.push_back(minX);
	xyz[1] = minY;//.push_back(minY);
	xyz[2] = minZ;//.push_back(minZ);
	xyz[3] = maxX;//.push_back(maxX);
	xyz[4] = maxY;//.push_back(maxY);
	xyz[5] = maxZ;//.push_back(maxZ);

	return xyz;

}