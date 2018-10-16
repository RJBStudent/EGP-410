#include "AStarPathfinding.h"
#include "GridGraph.h"
#include "Node.h"
#include "PerformanceTracker.h"
#include "Game.h"
#include "Path.h"
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

AStarPathfinding::AStarPathfinding(Graph* pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
#ifdef VISUALIZE_PATH
	mpPath = NULL;
#endif

}


AStarPathfinding::~AStarPathfinding()
{
#ifdef VISUALIZE_PATH
	delete mpPath;
#endif
}

Path* AStarPathfinding::findPath(Node* pFrom, Node* pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it
	list<Node*> nodesToVisit;
	nodesToVisit.push_front(pFrom);

#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	//create Path
	Path* pPath = new Path();

	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;

#ifdef VISUALIZE_PATH
	mpPath = pPath;
#endif
	return pPath;

}