#pragma once
#include <iostream>
#include <string>
using namespace std;


class Song
{
	static int ID_Static;
	string Title;
	float Duration;
	string Artist;
	bool Like;

public:
	Song(string Title = "", float Duration = 0, string Artist = "", bool Like = false);
	Song(const std::string& t, int d, string c, bool l) : Title(t), Duration(d), Artist(c), Like(l) {}

	Song(Song* N);

	//-----Setters-----
	void set_Title(string n);
	void set_Duration(float n);
	void set_Artist(string n);
	void set_Like(bool n);
	void set_ID_Static(static int n);

	//-----Getters-----
	string get_Title();
	float get_Duration();
	string get_Artist();
	bool get_Like();
	static int get_ID_Static();

	void set_Everything(string Title, float Duration, string Artist , bool Like);
	void display();

};