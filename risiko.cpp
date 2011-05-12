/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * risiko.cpp
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

#include "common.hpp"
#include "main.hpp"
#include "risiko.hpp"


// Argumente:
// str        : String der zerlegt werden soll
// vals       : Vector wo die Teilstrings gespeichert werden
// sep        : Trennzeichen wodurch zerlegt wird
// max_tokens : Max. Teilstrings - 0 == beliebig  
unsigned int splitString(
   const string& str, vector<string>& vals,
   const char *sep, unsigned int max_tokens ) {
   // Ist der String leer?         
   if (!str.length())
      return 0;

   // Führende Whitespaces, Newlines und Tabs entfernen
   string::size_type start = str.find_first_not_of(" \n\t");
   if (start == string::npos)
      return 0; // Nichts zu machen ...

   string::size_type stop;
   unsigned int tokens = 0;

   for ( unsigned int i = 0;
         (max_tokens == 0) || (i < max_tokens); ++i ) {
      if (max_tokens && ((i + 1) == max_tokens)) {
         stop = str.size();
      }
      else {
         stop = str.find_first_of(sep, start);
      }

      if (stop != string::npos) {
         // Sicher gehen ob ein Token vorhanden
         if (stop > start) {
            vals.push_back(str.substr(start, stop - start));
            ++tokens;
         }
      } 
      else if (start < str.size()) {
        vals.push_back(str.substr(start, str.size()-start));
        ++tokens;
        break;
      } 
      else {
         break;
      }
      start = str.find_first_not_of(sep, stop);
   }
   return tokens;
}


bool trim(string& str)
{
	if(!str.size())
	{
		return false;
	}
	str.erase(0,str.find_first_not_of (" \r\n\t"));

	if(!str.size())
	{
		return false;
	}	
	size_t ws=str.find_first_of ("#");
	if(ws<=str.size())
		str.erase(ws,str.npos);

	if(!str.length())
	{
		return false;
	}
	size_t ws_s=str.find_last_not_of (" \r\n\t");
	if(ws_s<=str.size())
		str.erase(ws_s+1,str.npos);


	if(str.length())
		return true;
	return false;
}

Risiko::Risiko()
{
    rd=new Ramdisk();
}

Risiko::~Risiko()
{
    delete rd;
}

bool Risiko::createFromFile(char* file)
{
	string filename="felder/";
	filename.append(file);

	ifstream datei;
	datei.open(filename.c_str(),ios::in);

	if(datei.is_open())
	{
		bool inhalt=false;
		bool grenzen=false;

		string inhaltzeile;
		char buffer[512];
		while(datei.getline(buffer,sizeof(buffer)))
		{
			inhaltzeile=buffer;
			buffer[0]='\0';

			if(!trim(inhaltzeile)) //Wenn nach Kürzen nurnoch leere Zeile
				continue;

                        //cout << "String: " << inhaltzeile << " ,Länge: " <<inhaltzeile.size() << endl;

			if(inhaltzeile == "[Land]")
			{
				inhalt=true;
				grenzen=false;
				continue;
			}
			else if(inhaltzeile == "[Grenzen]")
			{
				inhalt=false;
				grenzen=true;
				continue;
			}

			if(inhalt)
			{
				vector<string> p;
                                if(splitString(inhaltzeile, p, " \t",0)==2)
				{
                                        string s= p[0];//Name des Lands
                               //         replace (s.begin(),s.end(),'_',' ');
                                        int i = atoi(p[1].c_str()); //Nummer des Kontinents
                                        felder.setNode(s,i);

                                        //cout << "Erstelle Land:" << p[0] <<" Index:" << felder.getNumNodes () << endl;
					continue;
				}
			}
			else if(grenzen)
			{
				vector<string> p;
                                int c;
                                if((c=splitString(inhaltzeile, p, " \t",0))!=0)
				{
                                        int i=atoi(p[0].c_str());

                                        while(p.size()>1)
                                        {
                                            string s = p.at(p.size()-1);

                                            felder.setEdge(i,atoi(s.c_str()));
                                            p.pop_back();
                                        }
//					cout << "Setze Grenze zwischen Land " << felder.getNode(i)->getId() << " und " << felder.getNode(j)->getId() <<endl;
					continue;
				}
			}
			
			if(datei.eof() || datei.fail())
			{
				break;
			}
                }
                cout << felder.getMap()<<endl;
                if(rd->storefile("map",felder.getMap()))
                    return true;
                return false;
	}
	else
	{
		cerr << "Konnte Map-File: " <<filename << " nicht öffnen" << endl;
                return false;
	}
}

bool Risiko::createDefault()
{
        createFromFile("default.dat");

        Spieler* spieler1 = new Spieler("spieler/spieler1",0,rd);
        Spieler* spieler2 = new Spieler("spieler/spieler2",1,rd);
        Spieler* spieler3 = new Spieler("spieler/spieler3",2,rd);

        vector<Spieler*> spieler;
        spieler.push_back(spieler1);
        spieler.push_back(spieler2);
        spieler.push_back(spieler3);

        int spielerIt = 0;
        string actionReturn;

        stringstream log;
        log << spieler.size() << endl;
        log << 35 << endl;

        int aktionsnummer=0;

        while(felder.hasFreeFields())
        {
            if(spielerIt>=spieler.size())
                spielerIt=0;
            if(spieler.at(spielerIt)->actionStart(actionReturn)==true)
            {
                cout<<"ret:" << actionReturn << endl;
                if(actionReturn=="")
                    exit(3);
                if(felder.checkStart(actionReturn))
                    rd->storefile("map",felder.getMap());
            }
            else
            {
                cout << "Spieler " <<spieler1->getID()<<" antwortet nicht mehr"<<endl;
                exit(2); //Spieler antwortet nicht innerhalb von 5 sec.
            }
            actionReturn.clear();
           spielerIt++;
        }/*
        if(spieler1->actionAngreifen(s))
        {
            cout << s << endl;
        }
        else
        {

        }*/


        //delete (rd);
	
/*	cout << felder.runDijkstra(41,27) << endl; //Argentinien - Australien=>8
	stack<Land*> llist = felder.printDijkstraWay (27);
	while(!llist.empty())
	{
		cout <<llist.top()->getId()<<endl;
		llist.pop();
        }*/
}
