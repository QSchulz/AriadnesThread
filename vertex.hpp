/*****************************************************************************/
/* C++ library for creating a vertex with children, parents and DFS abilities*/
/* Written by SCHULZ Quentin, quentin.schulz@utbm.fr , Nov. 2013             */
/*****************************************************************************/

#ifndef VERTEX_H
#define VERTEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Vertex{
	private:
		vector<Vertex*> children;
		vector<Vertex*> parent;
		int _vertex_number;
		bool marked;

	public:
		Vertex();
		Vertex(int vertex_number=0);
		~Vertex();
		friend ostream& operator<<(ostream& o, Vertex const& vertex);
		void addChild(Vertex* vertex);
		void addParent(Vertex* vertex);
		Vertex& operator=(Vertex const& vertex);
		bool operator==(Vertex const& vertex);
		vector<Vertex*>& getChildren();
		vector<Vertex*>& getParent();
		Vertex* firstUnmarkedChild();
		Vertex* firstUnmarkedParent();
		void setMarked(bool marked);
		bool isMarked();
		bool isParentOf(Vertex* vertex);
		/*Traverse the whole stack by a DFS algorithm from current vertex, update flags of visited vertices and remove them from the stack*/
		void DFS(vector<Vertex*>& stack);
};
#endif
