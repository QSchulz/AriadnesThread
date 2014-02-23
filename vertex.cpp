/*****************************************************************************/
/* C++ library for creating a vertex with children, parents and DFS abilities*/
/* Written by SCHULZ Quentin, quentin.schulz@utbm.fr , Nov. 2013             */
/*****************************************************************************/

#include "vertex.hpp"

Vertex::Vertex():_vertex_number(0), marked(false)
{}

Vertex::Vertex(int vertex_number):_vertex_number(vertex_number), marked(false)
{}

Vertex::~Vertex()
{children.clear();parent.clear();}

ostream& operator<<(ostream& o, Vertex const& vertex)
{
	o << vertex._vertex_number << " ";
	return o;
}

void Vertex::addChild(Vertex* vertex)
{children.push_back(vertex);}

void Vertex::addParent(Vertex* vertex)
{parent.push_back(vertex);}

Vertex& Vertex::operator=(Vertex const& vertex)
{
	children.clear();
	parent.clear();
	children = vertex.children;
	parent = vertex.parent;
	_vertex_number = vertex._vertex_number;
	return *this;
}

bool Vertex::operator==(Vertex const& vertex)
{return _vertex_number==vertex._vertex_number;}

vector<Vertex*>& Vertex::getChildren()
{return children;}

vector<Vertex*>& Vertex::getParent()
{return parent;}

Vertex* Vertex::firstUnmarkedChild()
{
	int i(0);
	while (i<children.size() && children[i]->marked)
		++i;
	if (i<children.size())
		return children[i];
	return NULL;
}

Vertex* Vertex::firstUnmarkedParent()
{
	int i(0);
	while (i<parent.size() && parent[i]->marked)
		++i;
	if (i<parent.size())
		return parent[i];
	return NULL;
}

void Vertex::setMarked(bool marked)
{this->marked = marked;}

bool Vertex::isMarked()
{return marked;}

bool Vertex::isParentOf(Vertex* vertex)
{
	int i(0);
	while (i<children.size())
	{
		if (*children[i]==*vertex)
			return true;
		++i;
	}
	return false;
}

/*Traverse the whole stack by a DFS algorithm from current vertex, update flags of visited vertices and remove them from the stack*/
void Vertex::DFS(vector<Vertex*>& stack)
{
	this->setMarked(true);
	while(this->firstUnmarkedChild()!=NULL)
		this->firstUnmarkedChild()->DFS(stack);
	stack.push_back(this);
}
