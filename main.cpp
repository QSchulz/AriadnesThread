/****************************************************************************/
/* C++ library for finding strongly connected components, reduced matrix and*/
/* longest path between 						    */
/* Written by SCHULZ Quentin, quentin.schulz@utbm.fr , Nov. 2013            */
/****************************************************************************/

#include "stronglyconnectedcomponents.hpp"
#include "vertex.hpp"
#include "level.hpp"

int main(int argv, char** argc){
	ifstream matrixFile((argv==2)? argc[1]: "");
	vector<Vertex> matrixAdjacency;
	vector<Vertex*> stack, stack_cpy;
	vector<vector<int> > reducedMatrix;
	StronglyConnectedComponents reducedGraph;
	int number(0), size(0), start(-1), end(-1), k(0), i(0);
	
	
	/*Test if we succeeded to open the file*/
	if (!matrixFile)
	{
		/*If not, let the user knowing it and quit the program*/
		cout << "Error while opening file. Be sure to give an existing file as first argument of the program\n";
		exit(0);
	}
	/*The first line of the file indicates the number of vertices*/
	matrixFile >> size;
	/*Create the needed number of vertices*/
	for (int i(0); i<size; ++i)
	{
		matrixAdjacency.push_back(Vertex(i+1));
	}
	/*Matrix traversal*/
	for (int j(0); j<size; ++j)
	{
		for (int i(0); i<size; ++i)
		{
			/*Number of edges store*/
			matrixFile >> number;
			/*If number of edges = 1 then it means that these vertices
			 **are linked by an edge then we add the vertex i to the
			 **adjacency list of vertex j and the vertex j to the
			 **undirect adjacency list of vertex i*/
			if (number==1)
			{
				matrixAdjacency[j].addChild(&matrixAdjacency[i]);
				matrixAdjacency[i].addParent(&matrixAdjacency[j]);
			}
		}
	}
	/*To be sure that each vertex is visited
	** For example: 2+ vertices which have children but no parent*/
	while(stack.size()!=matrixAdjacency.size())
	{
		while(i<matrixAdjacency.size() && matrixAdjacency[i].isMarked())
			++i;
		matrixAdjacency[i].DFS(stack);
	}
	/*Save of the stack*/
	stack_cpy = stack;
	/*Unmark all vertices*/
	for (int i(0); i<matrixAdjacency.size(); ++i)
		matrixAdjacency[i].setMarked(false);
	/*Get all strongly connected components*/
	reducedGraph.getStronglyConnectedComponents(stack);
	reducedGraph.createReducedMatrix();
	/*Place 1 to last place via longest path between scc*/
	/*Looking for the index of levels containing the first place and the
	**last place of the game*/
	while(k<reducedGraph.getLevels().size() && (start==-1 || end==-1))
	{
		if (reducedGraph.getLevels()[k]->contains(&matrixAdjacency[0]))
			start = k;
		if (reducedGraph.getLevels()[k]->contains(&matrixAdjacency[size-1]))
			end = k;
		++k;
	}

	reducedGraph.createLongestPath(start,end,0);
	
	/*Print results*/
	cout<<"DFS Post order:\n";
	for (int i(0); i<stack_cpy.size(); ++i)
		cout << *stack_cpy[i];
	cout << endl << endl << reducedGraph;
	reducedGraph.printLongestPath(end);
	return EXIT_SUCCESS;
}
