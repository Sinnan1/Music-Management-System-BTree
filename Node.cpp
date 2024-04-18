#include "Node.h"

Node::Node(int t, bool leaf)
{
    minDegree = t;
    isLeaf = leaf;

    songs = new Song * [2 * minDegree - 1];
    children = new Node * [2 * minDegree];

    numKeys = 0;
}

void Node::Display()
{
    int i;
    for (i = 0; i < numKeys; i++) {
        if (isLeaf == false)
            children[i]->Display();

        songs[i]->display();
        cout << endl;
    }

    if (isLeaf == false)
        children[i]->Display();
}

void Node::DisplayLiked()
{
    int i;
    for (i = 0; i < numKeys; i++) {
        if (isLeaf == false)
            children[i]->Display();

        if (songs[i]->get_Like())
        {
            songs[i]->display();
            cout << endl;
        }
    }

    if (isLeaf == false)
        children[i]->Display();
}

/*This function searches for a given key k in the B-tree. It returns the node that contains the key or NULL if the key is not found.*/
Node* Node::PlaySong(string k)
{
    int i = 0;
    while (i < numKeys && k > songs[i]->get_Title())
        i++;

    if (songs[i]->get_Title() == k) {
        cout << "Song Is Playing. PLEASE ENJOY!!!" << endl << endl;
        cout << "\t[Press 1]\t If You Want to Like this Song." << endl;
        int ch;
        cin >> ch;
        cin.ignore();
        if (ch == 1)
        {
            songs[i]->set_Like(true);
            cout << endl << "Song Has Been Liked." << endl << endl;
        }
       
        return this;
    }

    if (isLeaf == true)
        return NULL;

    return children[i]->PlaySong(k);
}

Node* Node::LikeSong(string k)
{
    int i = 0;
    while (i < numKeys && k > songs[i]->get_Title())
        i++;

    if (songs[i]->get_Title() == k) {
        songs[i]->set_Like(true);
        cout << endl << "Song Has Been Liked." << endl << endl;

        return this;
    }

    if (isLeaf == true)
        return NULL;

    return children[i]->LikeSong(k);
}

/*This function finds the index of a given key k in the node's array of songs.*/
int Node::find_Key(string k)
{
    int index = 0;
    while (index < numKeys && songs[index]->get_Title() < k)
        ++index;
    return index;
}

/*This function inserts a new key k into a non-full node. If the node is a leaf, it inserts the key directly.
Otherwise, it finds the appropriate child node and recursively inserts the key.*/
void Node::insert_NonFull(Song* k)
{
    int i = numKeys - 1;

    if (isLeaf == true)
    {
        while (i >= 0 && songs[i]->get_Title() > k->get_Title())
        {
            songs[i + 1] = songs[i];
            i--;
        }

        songs[i + 1] = k;
        numKeys = numKeys + 1;
    }
    else
    {
        while (i >= 0 && songs[i]->get_Title() > k->get_Title())
            i--;

        if (children[i + 1]->numKeys == 2 * minDegree - 1)
        {
            split_Child(i + 1, children[i + 1]);

            if (songs[i + 1]->get_Title() < k->get_Title())
                i++;
        }
        children[i + 1]->insert_NonFull(k);
    }
}

/*This function splits a full child node y of the current node at index i. 
It creates a new node z, moves the appropriate keys and children to z, and updates the current node accordingly.*/
void Node::split_Child(int i, Node* root)
{
    Node* z = new Node(root->minDegree, root->isLeaf);
    z->numKeys = minDegree - 1;

    for (int j = 0; j < minDegree - 1; j++)
        z->songs[j] = root->songs[j + minDegree];

    if (root->isLeaf == false)
    {
        for (int j = 0; j < minDegree; j++)
            z->children[j] = root->children[j + minDegree];
    }

    root->numKeys = minDegree - 1;

    for (int j = numKeys; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = z;

    for (int j = numKeys - 1; j >= i; j--)
        songs[j + 1] = songs[j];

    songs[i] = root->songs[minDegree - 1];

    numKeys = numKeys + 1;
}

/*This function removes a key k from the B-tree. 
It searches for the key in the node and handles different cases depending on whether the key is in a leaf or non-leaf node.*/
bool Node::remove(string k)
{
    int index = this->find_Key(k);

    if (index < numKeys && songs[index]->get_Title() == k)
    {
        if (isLeaf) {
            remove_FromLeaf(index);
        }
        else {
            remove_FromNonLeaf(index);
        }

        return true;
    }
    else
    {
        if (isLeaf)
        {
            cout << "\tSong '" << k << "' Doesn't Exist in the Playlist (Tree)." << endl << endl;
            return false;
        }

        bool flag;
        if (index == numKeys) {
            flag = true;
        }
        else {
            flag = false;
        }

        if (children[index]->numKeys < minDegree)
            fill(index);

        if (flag && index > numKeys)
            children[index - 1]->remove(k);
        else
            children[index]->remove(k);
    }
    return false;
}

/*This function removes a key from a leaf node at the given index. It shifts the remaining keys to fill the gap.*/
void Node::remove_FromLeaf(int index)
{
    for (int i = index + 1; i < numKeys; ++i)
        songs[i - 1] = songs[i];

    numKeys--;
    return;
}

/*This function removes a key from a non-leaf node at the given index. 
It handles different cases depending on the availability of predecessor and successor keys.*/
void Node::remove_FromNonLeaf(int index)
{
    Song* k = songs[index];

    if (children[index]->numKeys >= minDegree)
    {
        Song* pred = get_Predecessor(index);
        songs[index] = pred;
        children[index]->remove(pred->get_Title());
    }
    else if (children[index + 1]->numKeys >= minDegree)
    {
        Song* succ = get_Successor(index);
        songs[index] = succ;
        children[index + 1]->remove(succ->get_Title());
    }
    else
    {
        merge(index);
        children[index]->remove(k->get_Title());
    }
    return;
}

/*This function returns the predecessor key of the key at the given index in a non-leaf node.
It recursively searches for the rightmost leaf in the subtree.*/
Song* Node::get_Predecessor(int index)
{
    Node* cur = children[index];
    while (!cur->isLeaf)
        cur = cur->children[cur->numKeys];

    return cur->songs[cur->numKeys - 1];
}

/*This function returns the successor key of the key at the given index in a non-leaf node.
It recursively searches for the leftmost leaf in the subtree.*/
Song* Node::get_Successor(int index)
{
    Node* cur = children[index + 1];
    while (!cur->isLeaf)
        cur = cur->children[0];

    return cur->songs[0];
}

/*This function handles the underflow case in a node by borrowing a key from the previous sibling or the next sibling.
If borrowing is not possible, it merges the node with its sibling.*/
void Node::fill(int index)
{
    if (index != 0 && children[index - 1]->numKeys >= minDegree)
        borrow_FromPrev(index);
    else if (index != numKeys && children[index + 1]->numKeys >= minDegree)
        borrow_FromNext(index);
    else
    {
        if (index != numKeys)
            merge(index);
        else
            merge(index - 1);
    }
    return;
}

/*This function borrows a key from the previous sibling of the node at the given index. It adjusts the keys and children arrays accordingly.*/
void Node::borrow_FromPrev(int index)
{
    Node* child = children[index];
    Node* sibling = children[index - 1];

    for (int i = child->numKeys - 1; i >= 0; --i)
        child->songs[i + 1] = child->songs[i];

    if (!child->isLeaf)
    {
        for (int i = child->numKeys; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }

    child->songs[0] = songs[index - 1];

    if (!child->isLeaf)
        child->children[0] = sibling->children[sibling->numKeys];

    songs[index - 1] = sibling->songs[sibling->numKeys - 1];

    child->numKeys += 1;
    sibling->numKeys -= 1;

    return;
}

/*This function borrows a key from the next sibling of the node at the given index. It adjusts the keys and children arrays accordingly.*/
void Node::borrow_FromNext(int index)
{
    Node* child = children[index];
    Node* sibling = children[index + 1];

    child->songs[(child->numKeys)] = songs[index];

    if (!(child->isLeaf))
        child->children[(child->numKeys) + 1] = sibling->children[0];

    songs[index] = sibling->songs[0];

    for (int i = 1; i < sibling->numKeys; ++i)
        sibling->songs[i - 1] = sibling->songs[i];

    if (!sibling->isLeaf)
    {
        for (int i = 1; i <= sibling->numKeys; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->numKeys += 1;
    sibling->numKeys -= 1;

    return;
}

/*This function merges the node at the given index with its next sibling. 
It moves the keys and children from the sibling to the current node and updates the key count. The sibling is then deleted.*/
void Node::merge(int index)
{
    Node* child = children[index];
    Node* sibling = children[index + 1];

    child->songs[minDegree - 1] = songs[index];

    for (int i = 0; i < sibling->numKeys; ++i)
        child->songs[i + minDegree] = sibling->songs[i];

    if (!child->isLeaf)
    {
        for (int i = 0; i <= sibling->numKeys; ++i)
            child->children[i + minDegree] = sibling->children[i];
    }

    for (int i = index + 1; i < numKeys; ++i)
        songs[i - 1] = songs[i];

    for (int i = index + 2; i <= numKeys; ++i)
        children[i - 1] = children[i];

    child->numKeys += sibling->numKeys + 1;
    numKeys--;

    delete(sibling);
    return;
}
