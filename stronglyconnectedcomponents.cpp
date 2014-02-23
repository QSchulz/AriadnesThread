/****************************************************************************/
/* C++ library for creating a game (i.e., set of all strongly connected     */
/* components) 								    */
/* Written by SCHULZ Quentin, quentin.schulz@utbm.fr , Nov. 2013            */
/****************************************************************************/

#include "stronglyconnectedcomponents.hpp"

StronglyConnectedComponents::StronglyConnectedComponents()
{}

StronglyConnectedComponents::StronglyConnectedComponents(StronglyConnectedComponents& scc):levels(scc.levels)
{}

StronglyConnectedComponents::~StronglyConnectedComponents()
{levels.clear();}

/*Set the list of levels (i.e., strongly connected components in a game)
**stack is the whole set of vertices in the game
**return a set of all strongly connected components contained in a game*/
vector<Level*> StronglyConnectedComponents::getStronglyConnectedComponents(vector<Vertex*>& stack)
{
	Level* temp = new Level();
	while(stack.size()>0)
	{
		temp->getLevel(stack, stack[stack.size()-1]);
		levels.push_back(temp);
		temp = new Level();
	}
	return levels;
}

ostream& operator<<(ostream& o, StronglyConnectedComponents const& scc){
	o<<"Strongly Connected Components"<<endl;
	for (int i(0); i<scc.levels.size(); ++i)
	{
		o << i+1 << ": ";
		o << *scc.levels[i] << endl;
	}
	if (!scc.reducedMatrix.size())
		return o;
	o<<endl<<"Reduced Matrix"<<endl;
	for (int i(0); i<scc.reducedMatrix.size(); ++i)
	{
		for (int k(0); k<scc.reducedMatrix.size(); ++k)
			o << scc.reducedMatrix[i][k];
		o << endl;
	}
	return o;
}

/*Create the reduced matrix (i.e., the matrix containing the number of direct passages between strongly
**connected components)*/
void StronglyConnectedComponents::createReducedMatrix()
{
	vector<int> temp;
	int tempValue(0);
	for (int i(0); i<levels.size(); ++i)
	{
		temp.clear();
		for (int j(0); j<levels.size(); ++j)
		{
			tempValue=0;
			if (j!=i)
				for (int k(0); k<levels[i]->getLevel().size(); ++k)
					for(int h(0); h<levels[j]->getLevel().size(); ++h)
						if (levels[i]->getLevel()[k]->isParentOf(levels[j]->getLevel()[h]))
							++tempValue;
			temp.push_back(tempValue);
		}
		reducedMatrix.push_back(temp);
	}			
}

/*Set maximal distance for each vertex on the way from startLevel to endLevel
**startLevel is the index of the level where the longest path should begin
**endLevel is the index of the level where the longest path should end
**count is the current distance of the path (number of strongly connected components visited)*/
void StronglyConnectedComponents::createLongestPath(int startLevel, int endLevel, int count)
{
	vector<Level*> temp;
	if(startLevel<reducedMatrix.size() && endLevel<reducedMatrix.size())
	{
		if(levels[startLevel]->getDistance()!=0)
		{
			if (count==0)
			{
				levels[startLevel]->setDistance(0);
				levels[startLevel]->setMarked(true);
				if(startLevel!=endLevel)
				{
					for (int i(0); i<reducedMatrix.size(); ++i)
						/*If there exists a direct path between startLevel and i levels and i level is not marked as visited*/
						if(reducedMatrix[startLevel][i]!=0 && !levels[i]->isMarked())
							createLongestPath(i, endLevel, count+1);
				}		
			}
			else
			{
				if(levels[startLevel]->getDistance()<count)
				{
					levels[startLevel]->setDistance(count);
					levels[startLevel]->setMarked(true);
					if(startLevel!=endLevel)
					{
						for (int i(0); i<reducedMatrix.size(); ++i)
							if(reducedMatrix[startLevel][i]!=0 && !levels[i]->isMarked())
								createLongestPath(i, endLevel, count+1);
					}		
				}
			}		
		}		
		levels[startLevel]->setMarked(false);
	}
	else
		cout << "Out of bounds !";
}

/*Print the longest path thanks to a queue starting from endLevel index
**endLevel is the end level from which we should retrieve the whole longest path to the beginning of the game*/
void StronglyConnectedComponents::printLongestPath(int endLevel)
{
	vector<int> longestPath;
	int current(levels[endLevel]->getDistance()), i(0);
	while(current>=0)
	{
		i=0;
		while(i<levels.size() && current!=levels[i]->getDistance())
			++i;
		longestPath.insert(longestPath.begin(), i+1);
		--current;
	}
	cout<<"\nLongest Path from beginning to end of the game\n";
	for (int i(0); i<longestPath.size(); ++i)
	{
		if (i!=longestPath.size()-1)	
			cout << longestPath[i]<<"-->";
		else
			cout << longestPath[i];
	}
	cout << endl;
	
}

vector<vector<int> >& StronglyConnectedComponents::getReducedMatrix()
{return reducedMatrix;}

vector<Level*>& StronglyConnectedComponents::getLevels()
{return levels;}

