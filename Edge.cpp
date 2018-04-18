// Honor Pledge:
//
// I pledge that I have neither given nor receieved any help
// on this assignment.

#include "Edge.h"
#include "Node.h"

//
//Edge(Node *org, Node *dest, int weight)
//
Edge::Edge(Node *org, Node *dest, int weight)
	{
		origin = org;
		destination = dest;
		this->weight = weight;
	}

//
//getOrigin()
//
Node* Edge::getOrigin()
{ 
	return origin;
}

//
//getDestination()
//
Node* Edge::getDestination()
{ 
	return destination;
}

//
//getWeight()
//
int Edge::getWeight()
{ 
	return weight;
}

//
//setWeight(int wt)
//
void Edge::setWeight(int wt)
{ 
	this->weight = wt;
}