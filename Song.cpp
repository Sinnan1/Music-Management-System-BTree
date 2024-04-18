#include "Song.h"

int Song::ID_Static = -1;

Song::Song(string Title, float Duration,string Artist, bool Like)
{
	this->Title = Title;
	this->Duration = Duration;
	this->Artist = Artist;
	this->Like = Like;

	ID_Static++;
}

Song::Song(Song* N)
{
	this->Title = N->Title;
	this->Duration = N->Duration;
	this->Artist = N->Artist;
	this->Like = N->Like;

	ID_Static++;
}

void Song::set_Title(string n)
{
	Title = n;
}
void Song::set_Duration(float n)
{
	Duration = n;
}
void Song::set_Artist(string n)
{
	Artist = n;
}
void Song::set_Like(bool n)
{
	Like = n;
}
void Song::set_ID_Static(int n)
{
	ID_Static = n;
}


string Song::get_Title()
{
	return Title;
}
float Song::get_Duration()
{
	return Duration;
}
string Song::get_Artist()
{
	return Artist;
}
bool Song::get_Like()
{
	return Like;
}
int Song::get_ID_Static()
{
	return ID_Static;
}

void Song::set_Everything(string Title, float Duration, string Artist, bool Like)
{
	this->Title = Title;
	this->Duration = Duration;
	this->Artist = Artist;
	this->Like = Like;

}

void Song::display()
{
	cout << "Title:\t\t" << Title << endl;
	cout << "Duration:\t" << Duration << endl;
	cout << "Artist:\t\t" << Artist << endl;
	cout << "Liked:\t\t";
	if (Like)
	{
		cout << "Liked" << endl;
	}
	else
	{
		cout << "Not Liked" << endl;
	}
	cout << endl;
}
