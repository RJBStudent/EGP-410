#pragma once

#include "Pathfinder.h"
class GridGraph;
class GridVisualizer;
class GraphicsBuffer;
class PathfindingDebugContent;

class GridPathfinder:public Pathfinder
{
public:
	friend class PathfindingDebugContent;

	GridPathfinder( GridGraph* pGraph );
	virtual ~GridPathfinder();

	virtual Path* findPath( Node* pFrom, Node* pTo ) = 0;


	//Accessors and Setters for when the pathfinding changes
	virtual	void setLastFrom(Node* last) { mpLastFrom = last; }
	virtual void setLastTo(Node* to) { mpLastTo = to; }
	virtual Node* getLastFrom() { return mpLastFrom; }
	virtual Node* getLastTo() { return mpLastTo; }
	
#ifdef VISUALIZE_PATH
	//just for visualization
public:
	void drawVisualization( Grid* pGrid, GraphicsBuffer* pDest );
protected:
	std::vector<Node*> mVisitedNodes;
	Path* mpPath;
	GridVisualizer* mpVisualizer;
	
#endif
	Node * mpLastFrom;
	Node * mpLastTo;

	double mTimeElapsed;
};