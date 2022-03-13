#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

#define INITIAL_ARRAY_CAPACITY 4


SortedMultiMap::SortedMultiMap(Relation r) : relation(r), treeRoot(nullptr), treeSize(0) {


}
// theta(1) constant only declaration for constructor
void SortedMultiMap::add(TKey c, TValue v) {
    // when the tree root is empty we need to set it
    if (this->treeRoot == nullptr) {
        auto node = new BSTNode();
        node->left = nullptr;
        node->right = nullptr;
        node->parent = nullptr;
        node->key = c;
        node->values = new TValue[INITIAL_ARRAY_CAPACITY]; // I used a default capacity with the aid of #define
        node->values[0] = v;
        node->capacity = INITIAL_ARRAY_CAPACITY;
        node->size = 1;
        this->treeRoot = node;
        this->treeSize += 1;
    }
    else {
        auto currentNode = this->treeRoot;
        auto previousNode = this->treeRoot;
        // loop until we find a null node or we find the key c in a node 
        while (currentNode != nullptr && currentNode->key != c) {
            previousNode = currentNode;
            if (this->relation(currentNode->key, c)) {
                currentNode = currentNode->right;
            }
            else {
                currentNode = currentNode->left;
            }
        }
        // if we found the key, replace the value
        if (currentNode != nullptr) {


            if (currentNode->size == currentNode->capacity) { // resize if the dynamic array of values becomes full
                auto newElements = new TValue[currentNode->capacity * 2];
                for (int i = 0; i < currentNode->size; i++) {
                    newElements[i] = currentNode->values[i];
                }
                currentNode->capacity *= 2;
                currentNode->values = newElements;

            }
            auto indexToAdd = 0;
            for (int i = 0; i < currentNode->size; i++) {
                // 1 2 10
                indexToAdd = i;
                if (!this->relation(currentNode->values[i], v)) {
                    indexToAdd -= 1;
                    break;
                }
            }
            indexToAdd += 1;
            currentNode->size += 1;
            this->treeSize += 1;
            for (int i = currentNode->size - 1; i >= indexToAdd; i--) {
                currentNode->values[i + 1] = currentNode->values[i];
            }
            currentNode->values[indexToAdd] = v;
        }
        else {
            auto node = new BSTNode();
            node->key = c;
            node->left = nullptr;
            node->right = nullptr;
            node->parent = nullptr;
            node->key = c;
            node->values = new TValue[INITIAL_ARRAY_CAPACITY];
            node->capacity = INITIAL_ARRAY_CAPACITY;
            node->size = 1;
            node->values[0] = v;
            // link the node to its parent
            node->parent = previousNode;
            if (this->relation(previousNode->key, c)) {
                previousNode->right = node;
            }
            else {
                previousNode->left = node;
            }
            this->treeSize += 1;
        }
    }
}
//O(n) 
vector<TValue> SortedMultiMap::search(TKey c) const {
    auto values = vector<TValue>();
    auto currentNode = this->treeRoot;
    // loop until we find a null node
    while (currentNode != nullptr) {
        // if we found the key, return its value
        if (currentNode->key == c) {
            for (int i = 0; i < currentNode->size; i++) {
                values.push_back(currentNode->values[i]); // we add here to a vector and return it (the dynamic array)
            }
            return values;
        }
        if (this->relation(currentNode->key, c)) {
            currentNode = currentNode->right;
        }
        else {
            currentNode = currentNode->left;
        }
    }
    return values;
}
// O(nodes)
bool SortedMultiMap::remove(TKey c, TValue v) {
    auto currentNode = this->treeRoot;
    // loop until we find a null node or we find the key
    while (currentNode != nullptr && currentNode->key != c) {
        if (this->relation(currentNode->key, c)) {
            currentNode = currentNode->right;
        }
        else {
            currentNode = currentNode->left;
        }
    }
    // if we haven't found the key, return
    if (currentNode == nullptr) {
        return false;
    }
    for (int i = 0; i < currentNode->size; i++) {
        if (currentNode->values[i] == v) {
            // 1 2 3 4 5
            for (int j = i + 1; j < currentNode->size; j++) {
                currentNode->values[j - 1] = currentNode->values[j];
            } // the algorithm is like sth of removing from a vector in highscool
            currentNode->size -= 1;
            //we decrement the size because we remove a value one by one
            this->treeSize -= 1;
            if (currentNode->size == 0) {
                this->removeNode(currentNode);
            }
            return true;
        }
    }
    return false;
}



// a helpful function which helps us to remove a node from the tree like we did in the drawings at the lecture 
void SortedMultiMap::removeNode(BSTNode* currentNode) {
    if (this->treeSize == 0) {
        // special condition when the node is the root and the only node; we need to set the root to null
        if (this->treeRoot == currentNode) {
            this->treeRoot = nullptr;
        }
    }
    else {
        int childrenCount = 0;
        BSTNode* child = nullptr;
        // save the left child if it is the only child of the node...
        if (currentNode->left != nullptr) {
            child = currentNode->left;
            childrenCount += 1;
        }
        // and the right one otherwise
        if (currentNode->right != nullptr) {
            child = currentNode->right;
            childrenCount += 1;
        }
        if (childrenCount == 0) {
            if (currentNode->parent->left == currentNode) { // if the node is a left one...
                currentNode->parent->left = nullptr;
            }
            else {
                // if the node is a right one...
                currentNode->parent->right = nullptr;
            }
            // either way set it to null in the parent
        }
        else if (childrenCount == 1) {
            if (this->treeRoot == currentNode) { // if the node is the root, the new root will be its child
                this->treeRoot = child;
            }
            else if (currentNode->parent->left == currentNode) { // if the node is a left one
                if (currentNode->left != nullptr) { // if the node has a left, then that one will replace the current node
                    currentNode->parent->left = currentNode->left;
                    currentNode->left->parent = currentNode->parent;
                }
                else { // similar thing when the node has a right
                    currentNode->parent->left = currentNode->right;
                    currentNode->right->parent = currentNode->parent;
                }
            }
            else { // similar thing when the node is a right one
                if (currentNode->left != nullptr) {
                    currentNode->parent->right = currentNode->left;
                    currentNode->left->parent = currentNode->parent;
                }
                else {
                    currentNode->parent->right = currentNode->right;
                    currentNode->right->parent = currentNode->parent;
                }
            }
        }
        else {
            // get the smallest node greater than the node we are removing
            auto nextNode = currentNode->right;
            while (nextNode->left != nullptr) {
                nextNode = nextNode->left;
            }
            currentNode->key = nextNode->key;

            // relink the node
            nextNode->parent->left = nextNode->right;
            nextNode->parent = nullptr;
            nextNode->right = currentNode->right;
            nextNode->left = currentNode->left;
        }
    }
}
// O(nodes)

int SortedMultiMap::size() const {
    return this->treeSize;
    //simply return the size of the tree 
}
//theta(1)

bool SortedMultiMap::isEmpty() const {
    if (this->treeSize == 0) {
        return true;
    }
    else {
        return false;
    }
    //if the tree of size is 0 then return true else false
}
//theta(1)
SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}
//theta(1)
SortedMultiMap::~SortedMultiMap() {}
//theta(1)