//==============================================================================
/**
* @file       Call_Graph.h
*
* $Id: Call_Graph.h
*
* Honor Pledge:
*
* I pledge that I have neither given nor received any help
* on this assignment.
*/
//==============================================================================

#ifndef CALL_GRAPH_H_
#define CALL_GRAPH_H_

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Edge.h"

class Node;

/**
* @class Call_Graph
*
* Implementation of Call_Graph algorithm
*/
class Call_Graph
{
public:
	//Constructor
	Call_Graph();

	/**
	* insert node
	*
	* @param[in]       v		Node
	*/
	void insert(Node *v);

	/**
	* Print the graph
	*
	* @param[in]       myfile		file to be output in
	*/
	void printGraph(std::ofstream& myfile);

	/**
	* insert node
	*
	* return int size
	*/
	int vertsize();

private:
	std::vector<Node*> vertices;
};

#endif