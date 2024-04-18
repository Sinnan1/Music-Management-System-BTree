#include "BTree.h"

BTree::BTree(int _t)
{
    root = NULL;
    t = _t;
}

void BTree::Display()
{
    if (root != NULL)
        root->Display();
}

void BTree::DisplayLiked()
{
    if (root != NULL)
        root->DisplayLiked();
}

Node* BTree::PlaySong(string k)
{
    if (root == NULL) {
        return NULL;
    }
    else {
        return root->PlaySong(k);
    }
}

Node* BTree::LikeSong(string k)
{
    if (root == NULL) {
        return NULL;
    }
    else {
        return root->LikeSong(k);
    }
}

void BTree::insert(Song* k)
{
    if (root == NULL)
    {
        root = new Node(t, true);
        root->set_Song(0, k);
        root->set_NumKeys(1);
    }
    else 
    {
        if (root->get_NumKeys() == 2 * t - 1)
        {
            Node* s = new Node(t, false);

            s->set_Child(0, root);

            s->split_Child(0, root);

            int i = 0;

            if (s->get_Song(0)->get_Title() < k->get_Title())
                i++;

            s->get_Child(i)->insert_NonFull(k);

            root = s;
        }
        else  
            root->insert_NonFull(k);
    }
}

bool BTree::remove(string k)
{
    if (!root)
    {
        cout << "The Tree is Empty" << endl << endl;
        return false;
    }

    bool flag = true;
    flag = root->remove(k);

    if (root->get_NumKeys() == 0)
    {
        Node* tmp = root;
        if (root->get_IsLeaf())
            root = NULL;
        else
            root = root->get_Child(0);

        delete tmp;
    }
    return flag;
}