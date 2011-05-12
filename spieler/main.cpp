#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>


using namespace std;

struct Land
{
	int spieler;
	int kontinent;
	string name;
};

int main()
{
	ifstream mapStream("map");
	srand(time(0));
	vector<Land> laender;
	vector<vector<int> > adjacency;
	string s;
	getline(mapStream,s);
	cout<<s<<endl;
	while(true)
	{
		mapStream>>s;
		//cout<<s<<endl;
		if(s=="[Grenzen]")
			break;
		Land l;
		l.name = s;
		mapStream>>l.kontinent;
		mapStream>>l.spieler;
	//	cout<<l.name<<" "<<l.kontinent<<" "<<l.spieler<<endl;
		laender.push_back(l);
	}
	adjacency.resize(laender.size());
	while(mapStream.good())
	{
		getline(mapStream,s);
		if(mapStream.eof())
			break;
		stringstream ss(s);
		int from;
		ss>>from;
		while(true)
		{
			int to;
			ss>>to;
			if(ss.eof())
				break;
			adjacency[from].push_back(to);
		}
	}
	/*for(int i = 0; i < (int)laender.size(); i++)
	{
		cout<<i<<" "<<laender[i].name<<": ";
		for(int j = 0; j <(int)adjacency[i].size(); j++)
		{
			cout<<adjacency[i][j]<<" ";
		}
		cout<<endl;
	}*/

	ifstream commandStream("action");
	//while(!)
	//getline(commandStream,s);
	s.clear();
	while(commandStream)
	{
		string temp;
		commandStream>>temp;
		s+=temp+" ";
	}
	cout<<s<<endl;
	stringstream ss(s);
	string cmd;
	int spielernummer;
	ss>>spielernummer;
	cout<<spielernummer<<endl;
	ss>>cmd;
	cout<<cmd<<endl;
	if(cmd == "GEBIETSBESETZEN")
	{
		commandStream.close();
		ss>>cmd;
		if(cmd == "ALT")
		{
			int land;
			do
			{
				land= rand()%laender.size();
			}while(laender[land].spieler != spielernummer);
			ofstream actStream("action");
			actStream<<land;
			return 0;
		}
		else
		{
			int land;
			do
			{
				land= rand()%laender.size();
			}while(laender[land].spieler != -1);
			ofstream actStream("action");
			actStream<<land;
			actStream.close();
			return 0;
		}
	}
	else if(cmd == "VERSTAERKUNG")
	{
		commandStream.close();
		int anzahl;
		ss>>anzahl;
		ofstream actStream("action");
		actStream<<"[Karten]"<<endl;
		actStream<<"[Positionen]"<<endl;
		for(int i = 0; i< anzahl; i++)
		{
			int land;
			do
			{
				land= rand()%laender.size();
			}while(laender[land].spieler != spielernummer);
			actStream<<land<<endl;
		}
	}
	else if(cmd == "ANGREIFEN")
	{

		commandStream.close();
	}
	else if(cmd == "BESIEGT")
	{

		commandStream.close();
	}
	else if(cmd == "VERSCHIEBEN")
	{

		commandStream.close();
	}
	return 0;
}
