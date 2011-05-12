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
#include <QProcess>

class Ramdisk {
    public:
        Ramdisk();
        Ramdisk(string filename);
        ~Ramdisk();

        bool storefile(string filename, string data);
        bool readfile(string filename, string& data);
        bool copyfile(string filenameto, string filenamefrom);

        string getDir() const;

        bool clear();
    private:
        //static string dirname="ramdisk/";
};

class Spieler {
    public:
        Spieler(string command,int sid, Ramdisk* ramd);
        ~Spieler();
        bool actionStart(string& ret);
        bool actionAngreifen(string& ret);
        bool actionVerteidigen(string& ret);
        bool actionVerstaerkung(string& ret);
        bool actionBewegung(string& ret);
        int getTroops() const;
        string doLog() const;
        int getID() const;

        void add(const int t1);
        void sub(const int t1);
    private:
        string command;
        int id;

        Ramdisk* rd;
        int freieTruppen;

};

#endif
