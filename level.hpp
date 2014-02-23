/****************************************************************************/
/* C++ library for creating a level (i.e., strongly connected component)    */
/* Written by SCHULZ Quentin, quentin.schulz@utbm.fr , Nov. 2013            */
/****************************************************************************/

#ifndef LEVEL_H
#define LEVEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "vertex.hpp"

using namespace std;

class Level{
	private:
		/*All vertices contained in this strongly connected component*/
		vector<Vertex*> lvl;
		/*Distance between two different strongly connected components*/
		int distance;
		/*Allow a strongly connected components to be marked (useful when traversing a game)*/
		bool marked;
	public:
		Level();
		Level(Level& l);
		~Level();
		/*Look for vertex in the level
		**vertex is the vertex to be searched for
		**return true if in otherwise return false*/
		bool contains(Vertex* vertex);
		/*Set the list of vertices in the level
		**stack is the whole set of vertices in the game
		**current is the vertex from which we apply the algorithm*/
		void getLevel(vector<Vertex*>& stack, Vertex* current);
		/*Return the strongly connected component with all of its vertices*/
		vector<Vertex*> getLevel();
		friend ostream& operator<<(ostream& o, Level const& level);
		/*Set distance between two strongly connected components*/
		void setDistance(int dis);
		int getDistance();
		/*Allow a strongly connected components to be marked (useful when traversing a game)*/
		void setMarked(bool _marked);
		bool isMarked();		
};

#endif
