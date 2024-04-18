#include "Node.h"

class BTree {
    Node* root; // Pointer to root node
    int t; // Minimum degree
public:

    BTree(int _t);

    //Insertion & Removal
    void insert(Song* k);
    bool remove(string k);

    //Display Functions
    void Display();
    void DisplayLiked();
    
    Node* PlaySong(string k);
    Node* LikeSong(string k);

};