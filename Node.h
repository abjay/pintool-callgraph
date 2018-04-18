//==============================================================================
/**
* @file       Node.h
*
* $Id: Node.h
*
* Honor Pledge:
*
* I pledge that I have neither given nor received any help
* on this assignment.
*/
//==============================================================================

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <iostream>
#include <string>
#include <fstream>

class Edge;

/**
* @class Node
*
* Implementation of Node algorithm
*/
class Node
{
public:
	//Constructor
	Node(std::string id);

	/**
	* Add the edge
	*
	* @param[in]       v		Node whose edge has to be added
	*/
	void addEdge(Node *v);

	/**
	* Print the edges
	*
	* @param[in]       myfile		File in which output has to be printed
	*/
	void printEdges(std::ofstream& myfile);

	/**
	* Get the name of node
	*
	* return weight of node
	*/
	std::string getName();

	/**
	* Get the edges
	*
	* return edges of node
	*/
	std::vector<Edge> getEdges();

private:
	std::string name;
	std::vector<Edge> edges;
	int wt;
};

#endif