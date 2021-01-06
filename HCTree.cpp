// Feel free to implement the HCTree class here
#include "HCTree.hpp"
#include "HCNode.hpp"
#include<stack>
#include <queue>

using namespace std; 

/*
 * Destructor for Tree
 */

void HCTree::deleteTree(HCNode* node){
    if(node == nullptr){
        return; 
    }

    deleteTree(node->c0); 
    deleteTree(node->c1); 
    delete node;
}

HCTree::~HCTree(){
    this->deleteTree(this->root); 
    this->root = nullptr;
    this->leaves = vector<HCNode*>(256, (HCNode*) 0);
}


/**
 * Use the Huffman algorithm to build a Huffman coding trie.
 * PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 * the frequency of occurrence of byte i in the message.
 * POSTCONDITION: root points to the root of the trie,
 * and leaves[i] points to the leaf node containing byte i.
 */

void HCTree::build(const vector<int>& freqs){
    //leaves always have 256 size. 
    //make the priority queue and also initlize the leaves
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    for(int i = 0; i < freqs.size(); i++){
        if(freqs[i] != 0){
            HCNode* newNodePtr = new HCNode(freqs[i], (byte)i);  
            (this->leaves)[i] = newNodePtr; 
            pq.push(newNodePtr); 
        }
        //nodes with the least count is gonna keep going up 
    }


    //need to popback to create the tree

    while(pq.size() != 1){
        //get the smallest two 
        HCNode* first = pq.top(); 
        pq.pop(); 
        HCNode* second = pq.top(); 
        pq.pop();

        //make a parent node with the counts added 
        HCNode* parentPtr = new HCNode(first->count + second->count, 0);
        //set childrens as smaller one on the left 
        parentPtr->c0 = first; 
        parentPtr->c1 = second; 

        //set child's parent pointers
        first->p = parentPtr; 
        second->p = parentPtr; 

        //add back the node to the pq
        pq.push(parentPtr); 
    }

    //when pq just has one node, then that node is the root, so set
    this->root = pq.top(); 
}

void HCTree::testBuild(){
    cout << this->root->count << endl; 

    //prints 7,10
    cout << this->root->c0->count << endl;
    cout << this->root->c1->count << endl;

    //should print 3,4
    cout << this->root->c0->c0->count << endl;
    cout << this->root->c0->c1->count << endl;

    //should print 1,2
    cout << this->root->c0->c0->c0->count << endl;
    cout << this->root->c0->c0->c1->count << endl;

    //should print 4,6
    cout << this->root->c1->c0->count << endl;
    cout << this->root->c1->c1->count << endl;


    cout << this->leaves[0]->count << endl; 
}

/**
 * Write to the given BitOutputStream
 * the sequence of bits coding the given symbol.
 * PRECONDITION: build() has been called, to create the coding
 * tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const{
    stack<int> st;
    //find the symbol among the leaves 
    HCNode* actual = nullptr; 
    //dont actually have to look for the symbol here.
    actual = leaves[symbol]; 
    //traverse up to the parent

    while(actual != this->root){
        HCNode* saved = actual;
        actual = actual->p; 
        if(actual->c0 == saved){
            //means that it was on the left 
            st.push(0);
        }else{
            //means that it was on the right 
            st.push(1); 
        }
    }


    while(st.empty() == false){
        out.writeBit(st.top()); 
        st.pop();
    }

    //cannot flush here actually. because not done yet 
    //and constantly flush after encoding one byte 
    //which is wrong
    //done 
}


/**
 * Return symbol coded in the next sequence of bits from the stream.
 * PRECONDITION: build() has been called, to create the coding
 * tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const{
    HCNode* tracker = this->root; 
    while(tracker->c0 != nullptr && tracker->c1 != nullptr){
        int i = in.readBit();
        if(i == 0){
            tracker = tracker->c0; 
        }else{
            tracker = tracker->c1; 
        }
    }
    return tracker->symbol; 
}
