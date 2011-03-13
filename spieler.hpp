/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * spieler.hpp
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
#ifndef SPIELER_H
#define SPIELER_H

#include "common.hpp"

class Ramdisk {
    public:
        Ramdisk();
        Ramdisk(string filename);
        bool clear();
    private:
};

class Spieler {
    public:
        Spieler(string name);
        bool actionStart();
        bool actionAngreifen();
        bool actionVerstaerkung();
        string doLog() const;
    private:
        string name;
        bool write(string data);
        bool read(string& data);

};

#endif
