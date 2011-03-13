/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * land.hh
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
 
#ifndef LAND_H
#define LAND_H

#include "common.hpp"
#include "node.hpp"

class Land : public Node{
	public:
		Land(): Node('a'){};
		
		//Spieler getSpieler();
		int getTroops();
		string getName();
		int getNummer();
		int getKontinent();

		bool setSpieler();
		bool setTroops();
		bool setName();
		bool setNummer();
		bool setKontinent();
	private:
	//	Spieler spieler;//???
		int Armeen;
		string Feldname;
		int Feldnummer;
		int Kontinent;
};
#endif
