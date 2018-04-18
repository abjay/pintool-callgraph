// Honor Pledge:
//
// I pledge that I have neither given nor receieved any help
// on this assignment.

#include "Node.h"
#include "Edge.h"

//
//Node(std::string id)
//
Node::Node(std::string id)
	{
		name = id;
		wt = 0;
	}

//
//addEdge(Node *v)
//
void Node::addEdge(Node *v)
	{
		this->wt++;
		Edge newEdge(this, v, this->wt);
		for (size_t i = 0; i < edges.size(); i++)
		{
			if ((newEdge.getOrigin() == edges[i].getOrigin()) && (newEdge.getDestination() == edges[i].getDestination()))
			{
				this->wt = edges[i].getWeight();
				this->wt++;
				edges[i].setWeight(this->wt);
				this->wt = 0;
				return;
			}

		}
		edges.push_back(newEdge);
		this->wt = 0;
	}

//
//printEdges(std::ofstream& myfile)
//
void Node::printEdges(std::ofstream& myfile)
{
	for (size_t i = 0; i < edges.size(); i++)
	{
		myfile << "\"" << name << "\"" << " -> ";
		Edge e = edges[i];
		myfile << "\"" << e.getDestination()->getName() << "\";" << std::endl;
	}
}

//
//getName()
//
std::string Node::getName()
{
	return name;
}

//
//getEdges()
//
std::vector<Edge> Node::getEdges()
{ 
	return edges;
}