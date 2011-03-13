/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * spieler.cpp
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

#include "spieler.hpp"
#include "common.hpp"

/* Ramdisk
 * Initialisierung einer Ramdisk
 * @TODO: Code für LINUX + WINDOWS + Ersatzcode wenn keine Adminrechte -> Ersatzort für Ramdisk(~/tmp/)
 */
Ramdisk::Ramdisk()
{
#ifdef __linux__ || __unix || __unix__
    system('')
#elif __WIN32__ || _MSC_VER

#endif
};

Spieler::Spieler(string name):filename(name){};

bool Spieler::actionAngreifen(){}

bool Spieler::actionStart(){}

bool Spieler::actionVerstaerkung(){}

string Spieler::doLog() const {}
