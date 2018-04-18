// Honor Pledge:
//
// I pledge that I have neither given nor receieved any help
// on this assignment.

#include "pin++/Callback.h"
#include "pin++/Routine_Instrument.h"
#include "pin++/Routine.h"
#include "pin++/Pintool.h"
#include "pin++/Symbol.h"
#include "Node.h"
#include "Edge.h"
#include "Call_Graph.h"
#include <fstream>
#include <stack> 
#include <string>

/**
* @class Arg1_Before
*/
class Arg1_Before :
	public OASIS::Pin::Callback <Arg1_Before (OASIS::Pin::ARG_FUNCARG_ENTRYPOINT_VALUE)>
{
public:
	//
	//Arg1_Before()
	//
	Arg1_Before()
	{

	}

	//
	//setRoutineName(std::string name)
	//
	void setRoutineName(std::string name)
	{
		this->function_name_ = name;
	}

	//
	//setOutFileName(std::ofstream * file)
	//
	void setOutFileName(std::ofstream * file)
	{
		this->file_ = file;
	}

	//
	//setOutStack(std::stack<std::string> * mystack_)
	//
	void setOutStack(std::stack<std::string> * mystack_)
	{
		this->mystack_ = mystack_;
	}

	//
	//handle_analyze (ADDRINT ip)
	//
	void handle_analyze (ADDRINT ip)
	{
		std::string functionName = this->function_name_;
		mystack_->push(functionName);
		*this->file_ << "Push into stack: " << functionName << std::endl;	
	}

private:
	std::ofstream * file_;
	std::string function_name_;
	std::stack<std::string> * mystack_;
};

/**
* @class Arg1__After
*/
class Arg1_After :
	public OASIS::Pin::Callback <Arg1_After (OASIS::Pin::ARG_FUNCRET_EXITPOINT_VALUE)>
{
public:
	//
	//Arg1_After (Call_Graph & g_, std::ofstream & gvfile_, std::vector<Edge> edges_)
	//
	Arg1_After (Call_Graph & g_, std::ofstream & gvfile_)
		:g(g_),
		gvfile(gvfile_)
	{
	}

	//
	//setOutFileName(std::ofstream * file)
	//
	void setOutFileName(std::ofstream * file)
	{
		this->file_ = file;
	}

	//
	//setRoutineName(std::string name)
	//
	void setRoutineName(std::string name)
	{
		this->function_name_ = name;
	}

	//
	//setOutStack(std::stack<std::string> * mystack)
	//
	void setOutStack(std::stack<std::string> * mystack)
	{
		this->mystack_ = mystack;
	}

	//
	//handle_analyze (ADDRINT ip)
	//
	void handle_analyze (ADDRINT ip)
	{
		if(!(mystack_->empty()))
		{
			std::string myFunction  = mystack_->top();
			n2 = new Node(mystack_->top());
			n1_flag = 0;
			mystack_->pop();
			if(!(mystack_->empty()))
			{
				n1 = new Node(mystack_->top()); 
				n1_flag = 1;
			}
			*this->file_ << "Pop from stack: " << myFunction << std::endl;
			if(n1_flag == 1)
			{
				n1->addEdge(n2);
				g.insert(n1);	
			}
		}
	}


private:
	std::ofstream * file_;
	std::string function_name_;
	std::stack<std::string> * mystack_;
	Node *n1;
	Node *n2;
	Call_Graph & g;
	std::ofstream & gvfile;
	int n1_flag;
};

/**
* @class Instruction
*/
class Instruction : public OASIS::Pin::Routine_Instrument <Instruction>
{
public:
	//
	//Instruction (std::ofstream & file, std::stack<std::string> & mystack_, Call_Graph & g_, std::ofstream & gvfile_, std::vector<Edge> & edges_)
	//
	Instruction (std::ofstream & file, std::stack<std::string> & mystack_, Call_Graph & g_, std::ofstream & gvfile_)
		: file_ (file),
		mystack_ (mystack_),
		g(g_),
		gvfile(gvfile_),
		arg1_After(g_, gvfile_)
	{

	}

	//
	//handle_instrument (const OASIS::Pin::Routine & rtn)
	//
	void handle_instrument (const OASIS::Pin::Routine & rtn)
	{
		std::string myRtnName = OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_NAME_ONLY);
		OASIS::Pin::Routine_Guard guard (rtn);
		Arg1_Before * arg1_Before=new Arg1_Before();
		arg1_Before->setOutFileName(&file_);
		arg1_Before->setRoutineName(myRtnName);
		arg1_Before->setOutStack(&mystack_);
		arg1_Before->insert (IPOINT_BEFORE,rtn,0);
		Arg1_After * arg1_After=new Arg1_After(g, gvfile);
		arg1_After->setOutFileName(&file_);
		arg1_After->setOutStack(&mystack_);
		arg1_After->insert (IPOINT_AFTER,rtn);
	}

private:
	std::ofstream & file_;
	std::stack<std::string> & mystack_;
	Arg1_Before arg1_Before;
	Arg1_After arg1_After;
	Call_Graph & g;
	std::ofstream & gvfile;
};

/**
* @class My_Callgraph
*/
class My_Callgraph : public OASIS::Pin::Tool <My_Callgraph>
{
public:
	//
	//My_Callgraph (void)
	//
	My_Callgraph (void)
		: file_ ("My_Callgraph.out"),
		inst_ (file_, mystack_, g_, gvfile_)
	{
		this->init_symbols ();
		this->enable_fini_callback ();
	}

	//
	//handle_fini (INT32)
	//
	void handle_fini (INT32)
	{
		gvfile_.open("Function_Graph.gv");
		g_.printGraph(gvfile_);
		this->file_.close ();
		this->gvfile_.close();
	}

private:
	std::ofstream file_;
	std::stack<std::string> mystack_;
	Instruction inst_;
	Call_Graph g_;
	std::ofstream gvfile_;
};

DECLARE_PINTOOL (My_Callgraph);