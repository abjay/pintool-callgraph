// Honor Pledge:
//
// I pledge that I have neither given nor receieved any help
// on this assignment.

#include "Call_Graph.h"
#include "Node.h"

//
//Call_Graph
//
Call_Graph::Call_Graph() {}

//
//insert(Node *v)
//
void Call_Graph::insert(Node *v)
{
	vertices.push_back(v);
}

//
//printGraph(std::ofstream& myfile)
//
void Call_Graph::printGraph(std::ofstream& myfile)
{
	myfile << "digraph G {" << std::endl;
	for (size_t i = 0; i < vertices.size(); i++)
	{
		vertices[i]->printEdges(myfile);
	}
	myfile << "}" << std::endl;
}

//
//vertsize()
//
int Call_Graph::vertsize()
{
	return vertices.size();
}