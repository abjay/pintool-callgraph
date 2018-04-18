//==============================================================================
/**
* @file       Edge.h
*
* $Id: Edge.h
*
* Honor Pledge:
*
* I pledge that I have neither given nor received any help
* on this assignment.
*/
//==============================================================================

#ifndef EDGE_H_
#define EDGE_H_

#include <vector>
#include <iostream>
#include <string>

class Node;

/**
* @class Edge
*
* Implementation of Edge algorithm
*/
class Edge
{
public:
	//Constructor
	Edge(Node *org, Node *dest, int weight);

	/**
	* Get origin
	*
	* return origin node
	*/
	Node* getOrigin();

	/**
	* Get destination
	*
	* return destination node
	*/
	Node* getDestination();

	/**
	* Get weight
	*
	* return weight of node
	*/
	int getWeight();

	/**
	* Set weight
	*
	* @param[in]       wt		weight to be set
	*/
	void setWeight(int wt);
	
private:
	Node* origin;
	Node* destination;
	int weight;
};

#endif