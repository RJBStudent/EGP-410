#include "AStarPathfinding.h"
#include "GridGraph.h"
#include "Node.h"
#include "PerformanceTracker.h"
#include "Game.h"
#include "GameApp.h"
#include "Path.h"
#include <list>
#include <vector>
#include <algorithm>
#include "Vector2D.h"
#include "Grid.h"
#include "Connection.h"

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
	mpLastFrom = pFrom;
	mpLastTo = pTo;

	if (!mpLastFrom || !mpLastTo)
	{
		return NULL;
	}

	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it

	NodeRecord startRecord;
	startRecord.mpNode = pFrom;
	startRecord.mpConnection = NULL;
	startRecord.mCostSoFar = 0;
	startRecord.mEstimateCost = getHeuristic(pFrom, pTo);

	list<NodeRecord> nodesToVisit;
	list<NodeRecord> visitedNodes;

	nodesToVisit.push_front(startRecord);

#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	//create Path
	Path* pPath = new Path();

	NodeRecord currentNode;
	bool toNodeAdded = false;


	while (/*pCurrentNode != pTo &&*/ nodesToVisit.size() > 0)
	{

		currentNode = getSmallestElement(nodesToVisit);	//Get shortest node in open list


		//remove node from list
		if (currentNode.mpNode == pTo)
		{
			break;
		}
		nodesToVisit.pop_front();


		//get the Connections for the current node
		vector<Connection*> connections = mpGraph->getConnections(currentNode.mpNode->getId());



		for (unsigned int i = 0; i < connections.size(); i++)
		{
			NodeRecord endNodeRecord = NodeRecord();
			Connection* pConnection = connections[i];
			Node* pEndNode = connections[i]->getToNode();
			float endNodeCost = currentNode.mCostSoFar + connections[i]->getCost() +getHeuristic(pEndNode, pTo);
			bool isVisited = false;
			bool hasntVisited = false;
			float endNodeHeuristic = getHeuristic(pEndNode, pTo);

			//Find out if the current node has been visited in the Member data of visited nodes
			bool isVisitedMember = false;
			vector<Node*>::iterator visitedMemberLocation;
			for (visitedMemberLocation = mVisitedNodes.begin(); visitedMemberLocation != mVisitedNodes.end(); ++visitedMemberLocation)
			{
				if ((*visitedMemberLocation) == pEndNode)
				{
					isVisitedMember = true;
					break;
				}
			}
			
			//Find out if the current has been found in the Node Record
			list<NodeRecord>::iterator closedLocation;
			for (closedLocation = visitedNodes.begin(); closedLocation != visitedNodes.end(); ++closedLocation)
			{
				if (closedLocation->mpNode == pEndNode)
				{
					isVisited = true;
					break;
				}
			}

			//Find out if the Node is in the open list
			list<NodeRecord>::iterator iterLocation;
			for (list<NodeRecord>::iterator iter = nodesToVisit.begin(); iter != nodesToVisit.end(); ++iter)
			{

				if (iter->mpNode == pEndNode)
				{
					iterLocation = iter;
					hasntVisited = true;
					break;
				}
			}

			//If it has been in the closed list take it out and check the cost with the current node.
			if (isVisited) 
			{
				//Find where end node is in Visited and set it to endNodeRecord
				endNodeRecord = (*closedLocation);

				//if the cost is shorter continue
				if (endNodeRecord.mCostSoFar <= endNodeCost)
				{
					continue;
				}

				//remove it from the closed list
				mVisitedNodes.erase(visitedMemberLocation);
				visitedNodes.erase(closedLocation);

				//set a float that is enNodeHeuristic to a new heuristic
				endNodeHeuristic = getHeuristic(pEndNode, pTo);
			}
			else if (hasntVisited)	//if the current node is in the open list set the new NodeRecord to that and set the hueristic from it to the end
			{
				endNodeRecord = (*iterLocation);
				if (endNodeRecord.mCostSoFar <= endNodeCost)
				{
					continue;
				}
				endNodeHeuristic = getHeuristic(pEndNode, pTo);
			}
			else //create a new node record with the current connection node as the node.
			{
				endNodeRecord = NodeRecord();
				endNodeRecord.mpNode = pEndNode;
				endNodeHeuristic = getHeuristic(pEndNode, pTo);
				
			}

			//Set the leftover data to what it was set to in the if statements.
			endNodeRecord.mCostSoFar = endNodeCost;
			endNodeRecord.mpConnection = pConnection;
			endNodeRecord.mEstimateCost = endNodeCost + endNodeHeuristic;

			//if it wasn't in the closed list or open list, add it to the open lost and check if it is the end
			if (!hasntVisited && !toNodeAdded)
			{
				nodesToVisit.push_back(endNodeRecord);
				if (endNodeRecord.mpNode == pTo)
				{
					toNodeAdded = true;
				}
				//Also add it to the closed list
#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(endNodeRecord.mpNode);
#endif
				visitedNodes.push_back(endNodeRecord);
			}
		}

		//remove the current node from the open list.
		for (list<NodeRecord>::iterator iter = nodesToVisit.begin(); iter != nodesToVisit.end(); ++iter)
		{
			if (iter->mpNode == currentNode.mpNode)
			{
				nodesToVisit.erase(iter);
				break;
			}
		}

		//Add the current node to the closed list.
#ifdef VISUALIZE_PATH
		mVisitedNodes.push_back(currentNode.mpNode);
#endif		
		visitedNodes.push_back(currentNode);
	}


	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");
	
	//Return the path from the visited nodes.
	if (currentNode.mpNode != pTo)
	{
		return NULL;
	}
	else{
		while (currentNode.mpNode != pFrom)
		{
			pPath->addNode(currentNode.mpNode);
			currentNode.mpNode = currentNode.mpConnection->getFromNode();

			for (list<NodeRecord>::iterator iter = visitedNodes.begin(); iter != visitedNodes.end(); ++iter)
			{
				if (iter->mpNode == currentNode.mpNode)
				{
					currentNode.mpConnection = iter->mpConnection;
					break;
				}
			}
		}
	}

#ifdef VISUALIZE_PATH
	mpPath = pPath;
#endif

	return pPath;


}

float AStarPathfinding::getHeuristic(Node* pFrom, Node* pTo)
{
	Grid* pGrid = dynamic_cast<GameApp*>(gpGame)->getGrid();
	Vector2D diff;
	diff = pGrid->getULCornerOfSquare(pFrom->getId()) - pGrid->getULCornerOfSquare(pTo->getId());
	return diff.getLength();
}


AStarPathfinding::NodeRecord AStarPathfinding::getSmallestElement(list<NodeRecord> openList)
{
	float lowestCost = INFINITY;
	list<NodeRecord>::iterator iterLocation = openList.begin();
	for (list<NodeRecord>::iterator iter = openList.begin(); iter != openList.end(); ++iter)
	{
		if (iter->mEstimateCost < lowestCost)
		{
			lowestCost = iter->mEstimateCost;
			iterLocation = iter;
		}
	}
	return (*iterLocation);
}