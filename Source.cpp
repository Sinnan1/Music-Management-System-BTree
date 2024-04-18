#include "BTree.h"

void Menu() {
    cout << endl;
    cout << "\t\t-----------------------------------------------------------------------------------------" << endl;
    cout << "\t\t|\t\t\t\t\t\t\t\t\t\t\t|" << endl;
    cout << "\t\t\t\t\t\t  MUSIC MANAGEMENT SYSTEM" << endl;
    cout << "\t\t|\t\t\t\t\t\t\t\t\t\t\t|" << endl;
    cout << "\t\t-----------------------------------------------------------------------------------------" << endl;

}

void displayPlaylist(BTree& b) {
    system("cls");
    cout << "Current Playlist:" << endl << endl;
    b.Display();
    cout << endl;
    system("pause");
    system("cls");
}

void addSong(BTree& b) {
    cout << endl;
    string song_name, artist_name;
    float duration;
    cout << "Enter the Name of the Song: ";
    getline(cin, song_name);
    cout << endl;
    cout << "Enter the Artist Name: ";
    getline(cin, artist_name);
    cout << endl;
    cout << "Enter the Duration of the Song: ";
    cin >> duration;
    cin.ignore();
    cout << endl;

    Song* newSong = new Song(song_name, duration, artist_name);
    b.insert(newSong);

    system("cls");
    cout << endl;
    cout << "\tNew Song Has been Added to the Playlist." << endl;
    cout << endl;
    cout << "\tTitle:\t\t" << song_name << endl;
    cout << "\tDuration:\t" << duration << endl;
    cout << "\tArtist:\t\t" << artist_name << endl;
    cout << endl;
    system("pause");
    system("cls");
}

void deleteSong(BTree& b) {
    cout << endl << endl;
    string name;
    cout << "Enter the song name to delete: ";
    getline(cin, name);
    cout << endl;

    bool flag = b.remove(name);
    if (flag)
    {
        cout << "Song '" << name << "' has been removed from the Playlist." << endl << endl;
    }

    system("pause");
    system("cls");
}

void updateSong(BTree& b) {
    cout << endl << endl;
    string name;
    cout << "Enter the song name to Update its Data: ";
    getline(cin, name);
    cout << endl;
    bool flag = b.remove(name);

    if (flag)
    {
        string song_name, artist_name;
        float duration;
        cout << "Enter the Updated-Name of the Song: ";
        getline(cin, song_name);
        cout << endl;
        cout << "Enter the Updated-Artist Name: ";
        getline(cin, artist_name);
        cout << endl;
        cout << "Enter the Updated-Duration of the Song: ";
        cin >> duration;
        cin.ignore();
        cout << endl;

        Song* newSong = new Song(song_name, duration, artist_name);
        b.insert(newSong);

        system("cls");
        cout << endl;
        cout << "\tSong Details has been Updated to:" << endl;
        cout << endl;
        cout << "\tTitle:\t\t" << song_name << endl;
        cout << "\tDuration:\t" << duration << endl;
        cout << "\tArtist:\t\t" << artist_name << endl;
        cout << endl;
    }
    system("pause");
    system("cls");
}

void playSong(BTree& b) {
    cout << endl << endl;
    string name;
    cout << "Enter the Song Name to Play: ";
    getline(cin, name);
    cout << endl;
    Node* node = b.PlaySong(name);
    if (node == NULL)
    {
        cout << "Song Not Found in the Playlist." << endl << endl;
    }

    system("pause");
    system("cls");
}

void displayLiked(BTree& b) {
    system("cls");
    cout << "Liked Songs From the Playlist:" << endl << endl;
    b.DisplayLiked();
    cout << endl;
    system("pause");
    system("cls");
}

void LikeaSong(BTree& b) {
    cout << endl << endl;
    string name;
    cout << "Enter the Song Name to Like: ";
    getline(cin, name);
    Node* node = b.LikeSong(name);
    if (node == NULL)
    {
        cout << "Song Not Found in the Playlist." << endl << endl;
    }

    system("pause");
    system("cls");
}

int main() {
    BTree t(3); // A B-Tree with minimum degree 3
    bool flag = true;

    while (true) {
        Menu();

        cout << endl << endl << endl;
        cout << "\tSelect From the Following Available Operations: [0 - 7]" << endl << endl;
        cout << "\t[Press 1]\t Add Song To the Playlist." << endl;
        cout << "\t[Press 2]\t Delete Song From the Playlist." << endl;
        cout << "\t[Press 3]\t Update Song From the Current Playlist." << endl;
        cout << "\t[Press 4]\t To Play (WINK ;) ) a Song." << endl;
        cout << "\t[Press 5]\t To Like a Song." << endl;
        cout << "\t[Press 6]\t Display All the Songs From the Playlist." << endl;
        cout << "\t[Press 7]\t To Display Songs That are Liked." << endl;
        cout << "\t[Press 0]\t Quit" << endl << endl;

        if (!flag)
        {
            cout << "\tInvalid choice. Please try again." << endl << endl;
            flag = true;
        }
        cout << "\tEnter your choice (0 - 7): ";
        string choice;
        getline(cin, choice);

        if (choice == "1") {
            addSong(t);
        }
        else if (choice == "2") {
            deleteSong(t);
        }
        else if (choice == "3") {
            updateSong(t);
        }
        else if (choice == "4") {
            playSong(t);
        }
        else if (choice == "5") {
            LikeaSong(t);
        }
        else if (choice == "6") {
            displayPlaylist(t);
        }
        else if (choice == "7") {
            displayLiked(t);
        }
        else if (choice == "0") {
            cout << endl << "Goodbye!" << endl;
            break;
        }
        else {
            flag = false;
            system("cls");
        }
    }

    return 0;
}