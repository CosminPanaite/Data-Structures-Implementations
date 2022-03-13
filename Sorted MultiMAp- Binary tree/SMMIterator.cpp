#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    this->first();
}
//theta(1)

void SMMIterator::first() {
    this->valueIndexArray = 0;
    this->currentNode = this->map.treeRoot;
    if (this->currentNode != nullptr) {
        while (this->currentNode->left != nullptr) {
            this->currentNode = this->currentNode->left;
        }
    }
}
//0(nodes)


void SMMIterator::next() {
    if (this->currentNode == nullptr) {
        throw std::exception();
    }
    if (this->valueIndexArray != this->currentNode->size - 1) {
        this->valueIndexArray += 1;
    }
    else {
        this->valueIndexArray = 0;
        if (this->currentNode->right != nullptr) {
            this->currentNode = this->currentNode->right;
            while (this->currentNode->left != nullptr) {
                this->currentNode = this->currentNode->left;
            }
        }
        else {
            while (this->currentNode->parent != nullptr && this->currentNode->parent->right == this->currentNode) {
                this->currentNode = this->currentNode->parent;
            }
            this->currentNode = this->currentNode->parent;
        }
    }
}
// O(nodes)

bool SMMIterator::valid() const {
    if (this->currentNode == nullptr) {
        return false;
    }
    else {
        return true;
    }
}
//theta(1)

TElem SMMIterator::getCurrent() const {
    if (this->currentNode == nullptr) {
        throw std::exception();
    }
    // echivalent cu make_pair
    return { this->currentNode->key, this->currentNode->values[this->valueIndexArray] };
}

//theta(1)
