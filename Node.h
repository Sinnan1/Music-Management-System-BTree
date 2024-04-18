#include "Song.h"

class Node
{
    Song** songs;
    int minDegree;
    Node** children;
    int numKeys;
    bool isLeaf;

public:
    Node(int minDegree, bool isLeaf);

    //-----Getters-----
    Song* get_Song(int index) { return songs[index]; }
    int get_MinDegree() const { return minDegree; }
    Node* get_Child(int index) const { return children[index]; }
    int get_NumKeys() const { return numKeys; }
    bool get_IsLeaf() const { return isLeaf; }

    //-----Setters-----
    void set_Song(int index, Song* song) { songs[index] = song; }
    void set_MinDegree(int minDegree) { this->minDegree = minDegree; }
    void set_Child(int index, Node* child) { children[index] = child; }
    void set_NumKeys(int numKeys) { this->numKeys = numKeys; }
    void set_IsLeaf(bool isLeaf) { this->isLeaf = isLeaf; }

    //Inserting Functions
    void insert_NonFull(Song* song);
    void split_Child(int index, Node* child);

    //Deleting Functions
    int find_Key(string song);

    bool remove(string song);
    void remove_FromLeaf(int index);
    void remove_FromNonLeaf(int index);

    Song* get_Predecessor(int index);
    Song* get_Successor(int index);
    void fill(int index);
    void borrow_FromPrev(int index);
    void borrow_FromNext(int index);
    void merge(int index);

    //Display Functions
    void Display();
    void DisplayLiked();
    Node* PlaySong(string k);
    Node* LikeSong(string k);

};
