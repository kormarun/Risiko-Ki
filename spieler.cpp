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
 * @TODO: Code für LINUX + WINDOWS + Ersatzcode wenn keine Adminrechte -> Ersatzort für Ramdisk(~/tmp/)
 */
Ramdisk::Ramdisk()
{
#ifdef __linux__ || __unix || __unix__

    if(getenv("USER")=="root")
    {
        if(system("mkdir ramdisk/")!=0)
            exit(1);
        if(system("mount -t tmpfs -o size=30M tmpfs ramdisk/")!=0)
            exit(1);
    }
    else
    {
        if(system("mkdir ramdisk/")!=0)
            exit(1);
    }

    dir="ramdisk/";
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
        dir=system("rmdir ramdisk/");
    }
#elif __WIN32__ || _MSC_VER
/*KP*/
#endif
};

bool Ramdisk::clear()
{
#ifdef __linux__ || __unix || __unix__
    string s="rm -rf ";
    s.append(dir);
    s.append("/*");
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
    filename.insert(0,dir);
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
    filename.insert(0,dir);
    ifstream datei;
    datei.open(filename.c_str(), ios::in);
    if(datei.is_open())
    {
        string buffer;
        datei >> buffer;
        if(datei.fail())
        {
            datei.close();
            return false;
        }
        data = buffer;
        datei.close();
        return true;
    }
    return false;
}


string Ramdisk::getDir() const
{
    return dir;
}

Spieler::Spieler(string name, int sid, Ramdisk* ramd)
{
    filename = name;
    id = sid;
    process = new QProcess();

    list << " -sid " ;
    list << itoa(sid);

    rd = ramd;
}

Spieler::~Spieler()
{
    delete process;
}

bool Spieler::actionAngreifen(string& ret)
{
    rd->storefile(itoa(id),"Attack");
    process->start(filename.c_str(), list);
    bool b = process->waitForFinished(5000);
    if(b==false)
        process->close();
}

bool Spieler::actionStart(string& ret){
    if(!rd->storefile(itoa(id),"GEBIETSBESETZEN"))
    {
        return false;
    }
    cout << "Data to file" << endl;
    process->start(filename.c_str(), list);
    bool b = process->waitForFinished(5000);
    if(b==false)
        process->close();
    cout << "process stopped"<<endl;
    string s;
    if(!rd->readfile(itoa(id),s))
    {
        return false;
    }
    ret=s;
    return true;
}

bool Spieler::actionVerstaerkung(string& ret){}

string Spieler::doLog() const {}
