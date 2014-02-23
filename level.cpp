/****************************************************************************/
/* C++ library for creating a level (i.e., strongly connected component)    */
/* Written by SCHULZ Quentin, quentin.schulz@utbm.fr , Nov. 2013            */
/****************************************************************************/

#include "level.hpp"
/*Set distance to -1 (represents INFINITY)*/
Level::Level():distance(-1)
{}

Level::Level(Level& l):lvl(l.lvl), distance(-1)
{}

Level::~Level()
{lvl.clear();}
/*Look for vertex in the level
**vertex is the vertex to be searched for
**return true if in otherwise return false*/
bool Level::contains(Vertex* vertex)
{
	int i(0);
	while(i<lvl.size() && !(vertex==lvl[i]))
		++i;
	if (i<lvl.size())
		return true;
	return false;
}
/*Set the list of vertices in the level
**stack is the whole set of vertices in the game
**current is the vertex from which we apply the algorithm*/
void Level::getLevel(vector<Vertex*>& stack, Vertex* current)
{
	Vertex* temp(0);
	int j(0);
	vector<Vertex*>::iterator it;
	/*Check if the level already contains vertices (if not, first occurence of the recursive loop)*/
	if (lvl.size()==0)
	{
		/*Looking for the first unmarked vertex in the game set*/
		do{
			temp = stack.back();
			stack.pop_back();
		}while(temp->isMarked() && stack.size()!=0);
		/*Add the found vertex to the level set*/
		lvl.push_back(temp);
	}
	else
	{
		/*Add the current vertex to the level set*/
		lvl.push_back(current);
		temp = current;
		j=0;
		it = stack.begin();
		/*Delete current vertex from the stack*/
		while (j<stack.size() && !(stack[j]==current))
		{
			++j;
			++it;
		}
		stack.erase(it);
	}
	temp->setMarked(true);
	/*Going on the process of searching for vertices in this strongly connected component*/
	for (int i(0); i<temp->getParent().size(); ++i)
	{
		if (!temp->getParent()[i]->isMarked())
			getLevel(stack, temp->getParent()[i]);
	}
}
/*Return the strongly connected component with all of its vertices*/
vector<Vertex*> Level::getLevel()
{return lvl;}

ostream& operator<<(ostream& o, Level const& level){
	for (int i(0); i<level.lvl.size(); ++i)
		o << *level.lvl[i];
	return o;
}

/*Set distance between two strongly connected components*/
void Level::setDistance(int dis)
{distance = dis;}

int Level::getDistance()
{return distance;}

/*Allow a strongly connected components to be marked (useful when traversing a game)*/
void Level::setMarked(bool _marked)
{marked = _marked;}

bool Level::isMarked()
{return marked;}
