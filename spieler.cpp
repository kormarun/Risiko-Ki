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

char* itoa(int id)
{
    char* i;
    sprintf(i,"%d",id);
    return i;
}

/* Ramdisk
 * Initialisierung einer Ramdisk
 * @TODO: Code für WINDOWS
 */
Ramdisk::Ramdisk()
{
#ifdef __linux__ || __unix || __unix__

    int i;
    if((i=system("test -d ramdisk || mkdir ramdisk/"))!=0)
    {
        cerr << "Konnte Ramdisk-Verzeichnis nicht anlegen: mkdir-Fehlercode: " << i << endl;
        exit(1);
    }

    if(getenv("USER")=="root")
    {
        if((i=system("mount -t tmpfs -o size=30M tmpfs ramdisk/"))!=0)
        {
            cerr << "Konnte Ramdisk-Verzeichnis nicht mounten: mount-Fehlercode: " << i << endl;
            exit(1);
        }
    }
    else
    {
        cerr << "Konnte Ramdisk-Verzeichnis nicht mounten: Diese Aktion benötigt Root-Rechte" << endl << "Sie können (wenn auch langsamer) fortfahren" << endl;
    }

    //dirname="ramdisk/";
#elif __WIN32__ || _MSC_VER
/*KP*/
#endif
};

Ramdisk::~Ramdisk()
{
    this->clear();
#ifdef __linux__ || __unix || __unix__
    if(getenv("USER")=="root")
    {
        system("umount ramdisk/");
        system("rmdir ramdisk/");
    }
    else
    {
        system("rmdir ramdisk/");
    }
#elif __WIN32__ || _MSC_VER
/*KP*/
#endif
};

bool Ramdisk::clear()
{
#ifdef __linux__ || __unix || __unix__
    string s="rm -rf ramdisk/*";
    int i = system(s.c_str());
    if(i!=0)
    {
        return false;
    }
    else
    {
        return true;
    }
#elif __WIN32__ || _MSC_VER
/*KP*/
#endif
}

bool Ramdisk::storefile(string filename, string data)
{
    filename.insert(0,"ramdisk/");//dirname);
    cout <<filename<<endl;

    ofstream datei;
    datei.open(filename.c_str(),ios::out);

    if(datei.is_open())
    {
        datei << data;
        if(datei.fail())
        {
            datei.close();
            return false;
        }
        datei.close();
        return true;
    }
    return false;

}

bool Ramdisk::readfile(string filename, string& data)
{
    filename.insert(0,"ramdisk/");//dirname);

    ifstream datei;
    datei.open(filename.c_str(), ios::in);
    if(datei.is_open())
    {
        char buffer[512];
        while(datei.good())
        {
            datei.getline(buffer,512);
            if(datei.fail())
            {
                datei.close();
                return false;
            }
            data.append(buffer);
        }
        datei.close();
        return true;
    }
    return false;
}

bool Ramdisk::copyfile(string filenameto, string filenamefrom)
{

    filenameto.insert(0,"ramdisk/");//dirname);

    ifstream dateiin;
    dateiin.open(filenamefrom.c_str(), ios::in);
    if(dateiin.is_open())
    {
        string buffer;
        while(dateiin)
        {
            dateiin >> buffer;
        }
        if(dateiin.fail())
        {
            dateiin.close();
            return false;
        }
        dateiin.close();

        ofstream dateiout;
        dateiout.open(filenameto.c_str(), ios::out);
        if(dateiout.is_open())
        {
            dateiout << buffer;
            if(dateiout.fail())
            {
                dateiout.close();
                return false;
            }
            dateiout.close();
            return true;
        }
        return false;
    }
    return false;
}


string Ramdisk::getDir() const
{
    return "ramdisk/";//dirname;
}

Spieler::Spieler(string command, int sid, Ramdisk* ramd)
{
    this->command = command;
    id = sid;

    rd = ramd;
    freieTruppen = 35;
}

Spieler::~Spieler()
{
}

int Spieler::getTroops() const
{
    return freieTruppen;
}

void Spieler::add(const int t1)
{
    this->freieTruppen+=t1;
}
void Spieler::sub(const int t1)
{
    this->freieTruppen-=t1;
}

bool Spieler::actionAngreifen(string& ret)
{

    QProcess* process = new QProcess();
    process->setWorkingDirectory("ramdisk/");

    stringstream befehl;
    befehl << id << endl << "ATTACK";

    rd->storefile("action",befehl.str());
    process->start(command.c_str());
    bool b = process->waitForFinished(5000);
    process->close();
    delete process;
    b && rd->readfile("action",ret);

    return !b;
}

bool Spieler::actionVerteidigen(string& ret)
{
    QProcess* process = new QProcess();
    process->setWorkingDirectory("ramdisk/");

    stringstream befehl;
    befehl << id << endl << "VERTEIDIGEN";

    rd->storefile("action",befehl.str());
    process->start(command.c_str());
    bool b = process->waitForFinished(5000);
    process->close();
    delete process;
    b && rd->readfile("action",ret);
    return !b;
}

bool Spieler::actionStart(string& ret){
    QProcess* process = new QProcess();
    process->setWorkingDirectory("ramdisk/");


    stringstream befehl;
    befehl << id << endl << "GEBIETSBESETZEN NEU";

    rd->storefile("action",befehl.str());
    process->start(command.c_str());
    bool b;
    b= process->waitForFinished(5000);
    process->close();
    delete process;
    //if(b)
    sleep(1);
        rd->readfile("action",ret);
    cout << b<<endl;
    return true;//b;
}

bool Spieler::actionVerstaerkung(string& ret){
    QProcess* process = new QProcess();
    process->setWorkingDirectory("ramdisk/");


    stringstream befehl;
    befehl << id << endl << "VERSTAERKEN";

    if(!rd->storefile("action",befehl.str()))
    {
        return false;
    }
    process->start(command.c_str());
    bool b = process->waitForFinished(5000);
    process->close();
    delete process;

    b && rd->readfile("action",ret);
    return !b;
}

bool Spieler::actionBewegung(string& ret){
    QProcess* process = new QProcess();
    process->setWorkingDirectory("ramdisk/");


    stringstream befehl;
    befehl << id << endl << "BEWEGEN";

    if(!rd->storefile("action",befehl.str()))
    {
        return false;
    }
    process->start(command.c_str());
    bool b = process->waitForFinished(5000);
    process->close();
    delete process;

    b && rd->readfile("action",ret);
    return !b;
}

int Spieler::getID() const
{
    return id;
}

string Spieler::doLog() const {}
