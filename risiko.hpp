/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * risiko.hh
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
#ifndef RISIKO_H
#define RISIKO_H

#include "common.hpp"
#include "felder.hpp"
#include "land.hpp"

class Risiko {
	public:
		Risiko();
		bool createDefault();
		bool createFromFile(char* filename);

		bool exportStandings();
		
		bool checkAction();
		bool moveTroops(short start, short stop, int num);
		
	private:
		Felder felder;
};


#endif
