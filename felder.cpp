/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Felder.cpp
 * Copyright (C) Niels Bernlöhr 2011 <niels@jrn1>
 * 
 * Risiko is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Risiko is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "felder.hpp"
#include "common.hpp"

Felder::Felder()
{
}

Felder::~Felder()
{
}

int Felder::runDijkstra(int source, int dest)
{
	if(lands!=lands_orig)
	  lands=lands_orig;
	if(edges!=edges_orig)
	  edges=edges_orig;
	
	getNode(source)->setDistance(0); // set start node

	while (lands.size() > 0)
	{
		Land* smallest = ExtractSmallest(lands);
		vector<Land*>* adjacentNodes = 
			AdjacentRemainingNodes(smallest);

		const int size = adjacentNodes->size();
		for (int i=0; i<size; ++i)
		{
			Land* adjacent = adjacentNodes->at(i);
			int distance = Distance(smallest, adjacent) +
				smallest->getDistance();
			
			if (distance < adjacent->getDistance())
			{
				adjacent->setDistance(distance);
				adjacent->setPrevious(smallest);
			}
		}
		delete adjacentNodes;
	}
	return getNode(dest,true)->getDistance();
}

stack<Land*> Felder::printDijkstraWay (int destination)
{
	return printDijkstraWay(getNode (destination,true));
}

stack<Land*> Felder::printDijkstraWay (Land* destination)
{
	stack<Land*> ret;
	Land* previous = destination;
	while (previous)
	{
		ret.push(previous);
		previous = previous->getPrevious();
	}
	return ret;
}

bool Felder::setNode(Land* land)
{
	lands.push_back(land);
	lands_orig.push_back(land);
}

bool Felder::setNode(string id)
{
	setNode(new Land(id));
}

bool Felder::setEdge(Edge* edge)
{
	edges.push_back(edge);
	edges_orig.push_back(edge);
}

bool Felder::setEdge(Land* land1, Land* land2, int distance)
{
	setEdge(new Edge(land1,land2, distance));
}

bool Felder::setEdge(int land1, int land2, int distance)
{
	setEdge(new Edge(getNode(land1),getNode(land2), distance));
}

bool Felder::setEdge(int land1, int land2)
{
	setEdge(new Edge(getNode(land1),getNode(land2), 1));
}

Land* Felder::getNode(int i) const
{
    return lands.at(i);
}

Land* Felder::getNode(int i, bool orig) const
{
	if(orig)
		return lands_orig.at(i);
	return lands.at(i);
}

Edge* Felder::getEdge(int i) const
{
      return edges.at(i);
}

int Felder::getNumNodes() const
{
	return lands_orig.size()-1;
}

int Felder::getNumEdges() const
{
	return edges_orig.size()-1;
}

vector<Land*>* Felder::AdjacentRemainingNodes(Land* land)
{
	vector<Land*>* adjacentNodes = new vector<Land*>();
	const int size = edges.size();
	for(int i=0; i<size; ++i)
	{
		Edge* edge = edges.at(i);
		Land* adjacent = NULL;
		if (edge->node1 == land)
		{
			adjacent = edge->node2;
		}
		else if (edge->node2 == land)
		{
			adjacent = edge->node1;
		}
		if (adjacent && Contains(lands, adjacent))
		{
			adjacentNodes->push_back(adjacent);
		}
	}
	return adjacentNodes;
}
Land* Felder::ExtractSmallest(vector<Land*>& lands)
{
	int size = lands.size();
	if (size == 0) return NULL;
	int smallestPosition = 0;
	Land* smallest = lands.at(0);
	for (int i=1; i<size; ++i)
	{
		Land* current = lands.at(i);
		if (current->getDistance() <
			smallest->getDistance())
		{
			smallest = current;
			smallestPosition = i;
		}
	}
	lands.erase(lands.begin() + smallestPosition);
	return smallest;
}
int Felder::Distance(Land* land1, Land* land2)
{
	const int size = edges.size();
	for(int i=0; i<size; ++i)
	{
		Edge* edge = edges.at(i);
		if (edge->Connects(land1, land2))
		{
			return edge->distance;
		}
	}
	return -1; // should never happen
}
bool Felder::Contains(vector<Land*>& lands, Land* land)
{
	const int size = lands.size();
	for(int i=0; i<size; ++i)
	{
		if (land == lands.at(i))
		{
			return true;
		}
	}
	return false;
}
void Felder::PrintShortestRouteTo(Land* destination)
{
	Land* previous = destination;
	cout << "Distance from start: " 
		<< destination->getDistance() << endl;
	while (previous)
	{
		cout << previous->getId() << " ";
		previous = previous->getPrevious();
	}
	cout << endl;
}
