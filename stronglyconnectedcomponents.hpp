/****************************************************************************/
/* C++ library for creating a game (i.e., set of all strongly connected     */
/* components) 								    */
/* Written by SCHULZ Quentin, quentin.schulz@utbm.fr , Nov. 2013            */
/****************************************************************************/

#ifndef STRONGLY_CONNECTED_COMPONENTS_H
#define STRONGLY_CONNECTED_COMPONENTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "vertex.hpp"
#include "level.hpp"

using namespace std;

class StronglyConnectedComponents{
	private:
		/*All strongly connected components in the game*/
		vector<Level*> levels;
		/*Reduced matrix (i.e., number of direct passages between strongly connected components)*/
		vector<vector<int> > reducedMatrix;
	public:
		StronglyConnectedComponents();
		StronglyConnectedComponents(StronglyConnectedComponents& scc);
		~StronglyConnectedComponents();
		/*Set the list of levels (i.e., strongly connected components in a game)
		**stack is the whole set of vertices in the game
		**return a set of all strongly connected components contained in a game*/
		vector<Level*> getStronglyConnectedComponents(vector<Vertex*>& stack);
		friend ostream& operator<<(ostream& o, StronglyConnectedComponents const& scc);
		/*Create the reduced matrix (i.e., the matrix containing the number of direct passages between strongly
		**connected components)*/
		void createReducedMatrix();
		/*Set maximal distance for each vertex on the way from startLevel to endLevel
		**startLevel is the index of the level where the longest path should begin
		**endLevel is the index of the level where the longest path should end
		**count is the current distance of the path (number of strongly connected components visited)*/
		void createLongestPath(int level1, int level2, int count);
		/*Print the longest path thanks to a queue starting from endLevel index
		**endLevel is the end level from which we should retrieve the whole longest path to the beginning of the game*/
		void printLongestPath(int endLevel);
		vector<vector<int> >& getReducedMatrix();
		vector<Level*>& getLevels();
		
};

#endif
