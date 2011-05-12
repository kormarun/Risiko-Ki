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

/*int Felder::runDijkstra(int source, int dest)
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
*/
bool Felder::setNode(Land* land)
{
	lands.push_back(land);
	lands_orig.push_back(land);
}

bool Felder::setNode(string id,int k)
{
        setNode(new Land(id,k,getNumNodes()+1));
}
/*
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
*/
bool Felder::setEdge(int land1, int land2)
{
        //setEdge(new Edge(getNode(land1),getNode(land2), 1));
        Land* i=getNode(land1);
        Land* j=getNode(land2);

        i->setNext(j);
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
/*
Edge* Felder::getEdge(int i) const
{
      return edges.at(i);
}
*/
int Felder::getNumNodes() const
{
	return lands_orig.size()-1;
}

int Felder::getNumEdges() const
{
	return edges_orig.size()-1;
}

bool Felder::hasFreeFields()
{
    for(int i=0;i<lands_orig.size();i++)
    {
        if(lands_orig.at(i)->getSpielerID()==-1)
            return true;
    }
    return false;
}

bool Felder::isReachable(int source, int dest)
{
    vector<Land*> known;
    Land* start=this->getNode(source,true);
    Spieler* sp=start->getSpieler();
    Land* ende=this->getNode(dest,true);
    return this->isReachableRecursive(start,ende,sp);
}

bool Felder::isReachableRecursive(Land* source, Land* dest, Spieler* sp)
{
    if(source->getSpieler()!=sp)
    {
        if(source==dest)
        {
            return true;
        }
        return false;
    }

    vector<Land*> next = source->getNext();
    for(int i=0;i<next.size();i++)
    {
        if(this->isReachableRecursive(next.at(i),dest,sp))
            return true;
    }
    return false;
}

bool Felder::isInVector(vector<Land*> vec ,Land* l)
{
    for(int i=0;i<vec.size();i++)
    {
        if(vec.at(i)==l)
            return true;
    }
    return false;
}
/*
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
*/
string Felder::getMap() const
{
    stringstream s;

    s << "[Land]" << endl;
    for(int i=0;i<lands_orig.size();i++)
    {
        s << lands_orig.at(i)->getId() << "\t"<< lands_orig.at(i)->getKontinent() <<"\t"<<lands_orig.at(i)->getSpielerID()<<endl;
    }
    s << endl << "[Grenzen]" << endl;
    for(int i=0;i<lands_orig.size();i++)
    {
        s << i << "\t";
        vector<Land*> next=lands_orig.at(i)->getNext();
        for(int j=0;j<next.size();j++)
        {
            s << next.at(j)->getNummer() << "\t";
        }
        s<<endl;
    }
    return s.str();
}


bool Felder::checkStart(string s)
{
    //int i=atoi(s.c_str());
}

bool Felder::checkAngreifen(string s){}
bool Felder::checkVerteidigen(string s){}
bool Felder::checkVerstaerken(string s){}
bool Felder::checkBewegung(string s){}
