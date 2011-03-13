/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * land.cpp
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

#include "land.hpp"

Land::Land(string i)
{
	id=i;
	previous=NULL;
	distanceFromStart = INT_MAX;
	cout << "Land " << i << " erzeugt" <<endl;
}

Land::~Land()
{
}

string Land::getId() const
{
	return id;
}

Land* Land::getPrevious() const
{
	return previous;
}

int Land::getDistance() const
{
	return distanceFromStart;
}

bool Land::setID(string id)
{
	this->id=id;
}

bool Land::setPrevious(Land* previous)
{
	this->previous=previous;
}

bool Land::setDistance(int distance)
{
	distanceFromStart=distance;
}
