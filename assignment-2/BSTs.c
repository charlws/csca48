/*
  CSC A48 - Assignment 2 - BSTs, Traversals, a tiny Sequencer

  For this assignment you will be implementing a fully working
  BST. The goal is for you to gain practice with one of the most
  common and more useful data structures you can find.

  The data we will store in the BST corresponds to musical notes
  from a little song, and we have provided (in a separate .c
  file) a very small implementation of a program to making
  sounds from each of these musical notes.

  ** YOU DO NOT NEED TO look at that code
  ** Everything in 'NoteSynth.c' is provided
  ** just so you can listen to the data in your
  ** BST - but you do not need to look at it for
  ** this assignment, and you're not expected
  ** to learn or understand that code.

  You can, however, learn from it if you're curious about how
  sound can be synthesized. Don't spend time on that unless you
  have completed everything else.

  Read carefully the comments and descriptions in this starter
  code, as they constitute the specification of what you need
  to do to complete the assignment.

  - Like A1, we will provide a test driver for you to test your
    code. Also like A1, that test driver contains a subset of the
    tests we will be running. You are responsible for running
    additional tests to ensure your BST works properly!

    (c) F. Estrada
*/

#include <stdio.h>
#include <stdlib.h>

#include "NoteSynth.c"

typedef struct BST_Node_Struct {
    // This compound type stores all data for one node of the
    // BST. Since the BST is used to store musical notes,
    // the data contained here represents one note from a
    // musical score:
    // freq: A double-precision floating point value,
    //       corresponding to the frequency (pitch) of the note
    // bar: Musical scores are divided into 'bars' (which you can
    //      see are actually separated by a vertical bar!). This
    //      value indicates which bar the note happens in. The
    //      first bar in the musical score is 0
    // index: Position of the note within the bar, from 0 (at the
    //        beginning of the bar) to 1 (at the end of the bar)
    // key: A unique identifier (remember we discussed BST nodes
    //      should have unique keys to identify each node). We
    //      want our nodes to store notes in the order in which
    //      they occur in the song. So, the key identifier is
    //      created as: key = (10.0*bar)+index
    //      NOTE: This means only one note can have a specific
    //            bar,index value. If two notes should happen
    //            at the same time in the song, we make the
    //            index of one of them a tiny bit bigger or
    //            a tiny bit smaller than the other one so
    //            their keys are very close, but not identical.

    double key;
    double freq;
    int bar;
    double index;

    struct BST_Node_Struct *left;
    struct BST_Node_Struct *right;

} BST_Node;

BST_Node *newBST_Node(double freq, int bar, double index) {
    /*
     * This function creates and initializes a new BST_Node
     * for a note with the given position (bar:index) and
     * the specified frequency. The key value for the node
     * is computed here as
     *
     * 		(10.0*bar)+index
     */

    /*** TO DO:
     * Complete this function to allocate and initialize a
     * new BST_Node. You should make sure the function sets
     * initial values for the data correctly.
     ****/

    BST_Node *new_node = NULL;
    new_node = (BST_Node *)calloc(1, sizeof(BST_Node));
    if (new_node == NULL) {
        printf("newBST_Node(): Out of Memory!, are you trying to load a Great Symphony???\n");
        return NULL;
    }

    new_node->key = (10.0 * bar) + index;
    new_node->freq = freq;
    new_node->bar = bar;
    new_node->index = index;

    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

BST_Node *BST_insert(BST_Node *root, BST_Node *new_node) {
    /*
     * This function inserts a new node into the BST. The
     * node must already have been initialized with valid
     * note data, and must have its unique key.
     *
     * The insert function must check that no other node
     * exists in the BST with the same key. If a node with
     * the same key exists, it must print out a message
     * using the following format string
     *
     * printf("Duplicate node requested (bar:index)=%d,%lf, it was ignored\n",....);
     * (of course you need to provide the relevant variables to print)
     *
     * And it must return without inserting anyting in the
     * BST.
     */

    /*** TO DO:
     * Implement the insert function so we can add notes to the tree!
     ****/

    if (root == NULL) {
        return new_node;
    }

    if (root->key == new_node->key) {
        // per piazza clarification, we shift the key a bit until a find a valid key
        // per piazza update, we should update index as well
        new_node->key = new_node->key + 0.0001;
        new_node->index = new_node->index + 0.0001;
        return BST_insert(root, new_node);
        // printf("Duplicate node requested (bar:index)=%d,%lf, it was ignored\n", new_node->bar, new_node->index);
        // return root;
    }

    if (new_node->key < root->key) {
        root->left = BST_insert(root->left, new_node);
    } else {
        root->right = BST_insert(root->right, new_node);
    }

    return root;
}

BST_Node *BST_search(BST_Node *root, int bar, double index) {
    /*
     * This function searches the BST for a note at the
     * specified position. If found, it must return a
     * pointer to the node that contains it.
     * Search has to happen according to the BST search
     * process - so you need to figure out what value to
     * use during the search process to decide which branch
     * of the tree to search next.
     */

    /*** TO DO:
     * Implement this function
     ****/

    if (root == NULL) return NULL;

    double key = (10.0 * bar) + index;
    if (root->key == key) return root;

    if (key < root->key)
        return BST_search(root->left, bar, index);
    else
        return BST_search(root->right, bar, index);
}

BST_Node *find_successor(BST_Node *right_child_node) {
    /*
     * This function finds the successor of a node by
     * searching the right subtree for the node that
     * is most to the left (that will be the node
     * with the smallest key in that subtree)
     */

    /*** TO DO:
     * Implement this function
     ****/

    BST_Node *cur = right_child_node;
    while (cur->left != NULL) cur = cur->left;
    return cur;
}

BST_Node *BST_delete(BST_Node *root, int bar, double index) {
    /*
     * Deletes from the BST a note at the specified position.
     * You must implement the three cases of BST deletion
     * we discussed in class. Make sure the function can
     * remove a note at any position without breaking the
     * tree!
     */

    /*** TO DO:
     * Implement this function
     ****/

    double key = (10.0 * bar) + index;
    if (root->key == key) {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left != NULL && root->right == NULL) {
            BST_Node *new_root = root->left;
            free(root);
            return new_root;
        } else if (root->left == NULL && root->right != NULL) {
            BST_Node *new_root = root->right;
            free(root);
            return new_root;
        } else {
            BST_Node *successor = find_successor(root->right);
            root->key = successor->key;
            root->freq = successor->freq;
            root->bar = successor->bar;
            root->index = successor->index;
            root->right = BST_delete(root->right, successor->bar, successor->index);
            return root;
        }
    } else if (key < root->key) {
        root->left = BST_delete(root->left, bar, index);
    } else {
        root->right = BST_delete(root->right, bar, index);
    }

    return root;
}

void BST_makePlayList(BST_Node *root) {
    /*
     * This function does an in-order traversal of the BST to
     * generate an ordered list of notes to be played. Each
     * note is added to a linked-list (already implemented,
     * you only need to call the insert function) and the
     * play list is then playable using the code in NoteSynth.c
     *
     * To insert a note, you need to call the function provided
     * in NoteSynth.c:
     *
     * playlist_head=playlist_insert(playlist_head,freq,bar,index);
     *
     * playlist_head is a GLOBAL variable declared in NoteSynth.c
     * precisely for this purpose. Don't worry about initializing
     * it. It's set to NULL.
     *
     * playlist_insert() takes the frequency, bar, and index, and
     * adds the note to the the *end* of the list - so notes
     * have to be added in order - hence the in-order traversal
     * this function has to do.
     */

    /**** TO DO:
     * Implement this function
     ****/

    if (root == NULL) return;

    if (root->left != NULL) BST_makePlayList(root->left);
    playlist_head = playlist_insert(playlist_head, root->freq, root->bar, root->index);
    if (root->right != NULL) BST_makePlayList(root->right);
}

void BST_inOrder(BST_Node *root, int depth) {
    /*
     * This function performs an in-order traversal of the BST
     * and prints out the note information for each note
     * using this print statement:
     *
     *  printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n",...);
     *
     * Obviously, you must provide the bar, index, and frequency
     * of the note that needs to be printed to complete the
     * statement - we're just giving you the formatting string.
     *
     * The depth value is increased by 1 for each recursive call
     * so when you print, you can see at what level each node
     * is located! (this should help you debug your code by
     * making it easier to check the shape of your BST).
     */

    /*** TO DO:
     * Implement this function
     ****/

    if (root == NULL) return;

    if (root->left != NULL) BST_inOrder(root->left, depth + 1);
    printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n", depth, root->bar, root->index, root->freq);
    if (root->right != NULL) BST_inOrder(root->right, depth + 1);
}

void BST_preOrder(BST_Node *root, int depth) {
    /*
     * This function performs an pre-order traversal of the BST
     * and prints out the note information for each note
     * using this print statement:
     *
     *  printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n",...);
     *
     * Obviously, you must provide the bar, index, and frequency
     * of the note that needs to be printed to complete the
     * statement - we're just giving you the formatting string.
     *
     * The depth value is increased by 1 for each recursive call
     * so when you print, you can see at what level each node
     * is located! (this should help you debug your code by
     * making it easier to check the shape of your BST).
     */

    /*** TO DO:
     * Implement this function
     ****/

    if (root == NULL) return;

    printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n", depth, root->bar, root->index, root->freq);
    if (root->left != NULL) BST_preOrder(root->left, depth + 1);
    if (root->right != NULL) BST_preOrder(root->right, depth + 1);
}

void BST_postOrder(BST_Node *root, int depth) {
    /*
     * This function performs an post-order traversal of the BST
     * and prints out the note information for each note
     * using this print statement:
     *
     *  printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n",...);
     *
     * Obviously, you must provide the bar, index, and frequency
     * of the note that needs to be printed to complete the
     * statement - we're just giving you the formatting string.
     *
     * The depth value is increased by 1 for each recursive call
     * so when you print, you can see at what level each node
     * is located! (this should help you debug your code by
     * making it easier to check the shape of your BST).
     */

    /*** TO DO:
     * Implement this function
     ****/

    if (root == NULL) return;

    if (root->left != NULL) BST_postOrder(root->left, depth + 1);
    if (root->right != NULL) BST_postOrder(root->right, depth + 1);
    printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n", depth, root->bar, root->index, root->freq);
}

void delete_BST(BST_Node *root) {
    /*
     * This function deletes the BST and frees all memory used for
     * nodes in it. Recall that there is a specific order in which
     * this needs to be done! (consult the Unit 4 notes as needed)
     */

    /**** TO DO:
     * Implement this function
     ****/

    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        free(root);
        return;
    }

    if (root->left != NULL) delete_BST(root->left);
    if (root->right != NULL) delete_BST(root->right);
    free(root);
}

BST_Node *reverseSwap(BST_Node *root, int min_bar, int max_bar) {
    if (root == NULL) return root;

    root->bar = max_bar - (root->bar - min_bar);
    root->index = 1.00 - root->index;
    root->key = (10.0 * root->bar) + root->index;

    BST_Node *temp = root->right;
    root->right = root->left;
    root->left = temp;
    reverseSwap(root->left, min_bar, max_bar);
    reverseSwap(root->right, min_bar, max_bar);

    return root;
}

BST_Node *reverseSong(BST_Node *root) {
    /*
     * This function will reverse the song currently stored in our
     * tree - that means the song will play *backwards*.
     *
     * For instance, if the song contains notes
     *
     *  A B C D E F G     in that order
     *
     *  after reversing it should play
     *
     *  G F E D C B A     in that order
     *
     *  In terms of the bar and index of each note in the input tree,
     *  here are some pieces of information you will need to figure
     *  out what the new bar and index of each note will be:
     *
     *  If the maximum bar for a note in the input tree is MAX_BAR
     *  and the minimum (smallest) bar for a note in the input tree
     *  is MIN_BAR
     *
     *  A note with bar=MIN_BAR will end up with bar=MAX_BAR
     *  A note with bar=MAX_BAR will end up with bar=MIN_BAR
     *
     *  The index for any note must be between 0 and 1. If the
     *  original note had index=0, it will end up with index=1
     *  if the original note had index=1, it will end up with index=0
     *
     *  That's all the information you need to figure out how to
     *  generate the notes for the backwards version of the song.
     *
     *  It's up to you how to modify the tree so that the resulting
     *  song plays backwards. *There's many different ways to do this*
     *  As ever, I recommend you solve this first *on paper* and
     *  only start coding once you know what you have to do to solve this
     *  part.
     *
     */

    /*** TO DO:
     * Implement this function! (Crunchy!)
     ****/

    if (root == NULL) return root;

    BST_Node *cur = root;
    int min_bar = -1, max_bar = -1;
    while (cur->left != NULL) cur = cur->left;
    min_bar = cur->bar;
    cur = root;
    while (cur->right != NULL) cur = cur->right;
    max_bar = cur->bar;

    reverseSwap(root, min_bar, max_bar);

    return root;
}

/********************************************************************************************
 *      Add any helper functions you need for implementing BST_harmonize() just below this
 * comment block, and above BST_Harmonize itself!
 * ******************************************************************************************/

int getFreqIndex(double freq) {
    for (int i = 0; i < 100; i++) {
        if (note_freq[i] == freq) return i;
    }
    return -1;
}

BST_Node *prepareNodes(BST_Node *root, BST_Node *newTreeRoot, int semitones, double time_shift) {
    if (root == NULL) return newTreeRoot;

    int newFreqIdx = getFreqIndex(root->freq) + semitones;
    double newIndex = root->index + time_shift;
    if (!(newFreqIdx < 0 || newFreqIdx > 99 || newIndex < 0 || newIndex >= 1)) {
        BST_Node *new_node = newBST_Node(note_freq[newFreqIdx], root->bar, newIndex);
        newTreeRoot = BST_insert(newTreeRoot, new_node);
    }

    newTreeRoot = prepareNodes(root->left, newTreeRoot, semitones, time_shift);
    newTreeRoot = prepareNodes(root->right, newTreeRoot, semitones, time_shift);

    return newTreeRoot;
}

void cloneNewTree(BST_Node *newTreeRoot, BST_Node *oldTreeRoot){
    // clone data from newTree (rooted at newTreeRoot) to tree (rooted at oldTreeRoot)
    if (newTreeRoot == NULL) return;

    if (newTreeRoot->left != NULL) cloneNewTree(newTreeRoot->left, oldTreeRoot);
    BST_Node *new_node = newBST_Node(newTreeRoot->freq, newTreeRoot->bar, newTreeRoot->index);
    oldTreeRoot = BST_insert(oldTreeRoot, new_node);
    if (newTreeRoot->right != NULL) cloneNewTree(newTreeRoot->right, oldTreeRoot);
}

BST_Node *BST_harmonize(BST_Node *root, int semitones, double time_shift) {
    /* Let's play with notes, because we can.
     *
     * This function traverses the BST, and for each existing
     * note, inserts a new, modified note (i.e. it will add sounds
     * to an already existing song, based on the notes it already has)
     *
     * The new note has the following properties:
     * - The frequency is shifted by the specified number of semitones
     *   (A semitone is the difference between one note and the
     *    immediately next one in the musical scale - ot what is the
     *    same, the difference in pitch between a white key and the
     *    black key immediately next to it in a piano)
     * - It plays in the same *bar* as the original note
     * - But its *index* is shifted by the specified time_shift
     *   (this value is between 0 and 1, but you have to check
     *    that the final index remains between 0 and 1)
     *
     * Both the 'semitones' and 'time_shift' parameter can be
     * positive or negative. A typical value for semitones
     * could be 4 or 7, corresponding to musical 3rds or
     * musical 5ths - this should produce some interesting
     * harmony! but you can play with this function and try
     * various things for fun.
     *
     * In practice, figuring out the frequency of the note
     * you have to insert is easy. For instance, suppose
     * you have an existing note in  the BST with
     *
     * freq=440.0, at bar=10, index=.25
     *
     * Now suppose the user specified
     *
     * semitones=4
     * time_shift=.1
     *
     * Then you go to the note_freq[] array, find the index
     * of the entry for frequency 440.0 (let's say it's
     * j), then go to note_freq[j+4] to find the frequency
     * of the note you need to add.
     *
     * NOTE: If the value of  j+semitones  is < 0 or > 99
     *       then there is no note with the frequency you
     *       want. In that case you don't insert a new
     *       note.
     *
     * You then add a new note with that frequency at
     * bar=10 (same bar!)
     * index=.25 + .1  (the original index plus the time_shift)
     *
     * NOTE: If the resulting index is less than 0, or >= 1,
     *       then you DO NOT insert the new note.
     *
     * This function is crunchy - and if you don't think it
     * through before you start implementing it you'll run into
     * all kinds of trouble.
     *
     * This is the problem solving exercise for A2, so don't
     * look for people on Piazza to give you answers, or tell you
     * what to do, or verify you're doing the right thing.
     *
     * It's up to you how to solve this, and if you want an opinion,
     * you can come to visit us during office hours!
     *
     * Expected result: The BST will have about twice as many notes
     *   as before, and the new notes are shifted in pitch and
     *   in time as specified by the parameters.
     */

    /*** TO DO:
     * Implement this function
     ****/

    if (root == NULL) return root;

    BST_Node *newTreeRoot = NULL;
    newTreeRoot = prepareNodes(root, newTreeRoot, semitones, time_shift);
    cloneNewTree(newTreeRoot, root);

    return root;
}
