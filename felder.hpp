/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * felder.hh
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
 
#ifndef FELDER_H
#define FELDER_H

#include "common.hpp"
#include "land.hpp"
#include "edge.hpp"

class Felder{
	public:
		Felder();
		~Felder();

		//Code für die Arbeit mit dem Dijkstra-Algorythmus
		bool setNode(Land* land);
		bool setNode(string id);
		bool setEdge(Edge* edge);
		bool setEdge(Land* land1, Land* land2, int distance);
		bool setEdge(int land1, int land2, int distance);
		bool setEdge(int land1, int land2);
		Land* getNode(int i) const;
		Land* getNode(int i, bool orig) const;
		Edge* getEdge(int i) const;
		int getNumNodes() const;
		int getNumEdges() const;
		int runDijkstra(int source, int dest);
		stack<Land*> printDijkstraWay(Land* destination);
		stack<Land*> printDijkstraWay(int destination);
		void PrintShortestRouteTo(Land* destination);

	private:
		//Code für die Arbeit mit dem Dijkstra-Algorythmus
		vector<Land*> lands;
		vector<Edge*> edges;
		
		vector<Land*> lands_orig;
		vector<Edge*> edges_orig;
		
		vector<Land*>* AdjacentRemainingNodes(Land* land);
		Land* ExtractSmallest(vector<Land*>& lands);
		int Distance(Land* land1, Land* land2);
		bool Contains(vector<Land*>& lands, Land* land);
};
#endif
