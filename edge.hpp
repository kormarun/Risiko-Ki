/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * edge.hh
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

#ifndef EDGE_H
#define EDGE_H

#include "common.hpp"
#include "land.hpp"

class Edge
{
	public:
		Edge(Land* node1, Land* node2, int distance) : node1(node1), node2(node2), distance(distance)
		{
			cout << "Setze Grenze zwischen den Ländern " << node1->getId () << " und " << node2->getId () << " mit der Entfernung " << distance<<endl;
		}
		bool Connects(Land* node1, Land* node2)
		{
			return (
				(node1 == this->node1 &&
				node2 == this->node2) ||
				(node1 == this->node2 && 
				node2 == this->node1));
		}
		Land* node1;
		Land* node2;
		int distance;
};

#endif
