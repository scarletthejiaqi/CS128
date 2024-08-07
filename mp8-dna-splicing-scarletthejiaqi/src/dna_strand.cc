#include "dna_strand.hpp"

#include <stdexcept>
void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
    if (*pattern == '\0' || to_splice_in.head_ == nullptr) {return;}
    if (&to_splice_in == this) {return;}
    Node* curr = head_;Node* prev = nullptr;Node* start = head_;Node* ultimate = nullptr;Node* left = nullptr;Node* uright = nullptr;bool found = false;
    while (curr != nullptr) {
        unsigned int i = 0;
        for (i = 0; pattern[i] != '\0'; i++) {
            if (curr == nullptr) {
                Helper(uright, pattern,head_, found, to_splice_in, ultimate);
                return;  
            }
            if (curr->data != pattern[i]) {break;}
            prev = curr;curr = curr->next;
        }
        if (pattern[i] == '\0') {found = true;ultimate = left;uright = curr;start = curr;left = prev;continue;}
        left = start;start = start->next;curr = start;
    }
    //do put in, start is the ending, ultimate is beginning
    Helper(uright, pattern,head_, found, to_splice_in, ultimate);
}

void DNAstrand::Freemem(Node* ultimate,const char* pattern) {
    for (int i = 0; pattern[i] != '\0'; i++) {
            Node* todelete = ultimate->next;
            delete ultimate;
            ultimate = todelete;
        } 
}

void DNAstrand::Helper(Node*& uright, const char* pattern,Node*& head_, bool& found, DNAstrand& to_splice_in, Node*& ultimate) {
    if (uright == nullptr && ultimate == nullptr && !found) {
        throw std::exception();
    } 
    if (ultimate == nullptr) {
        Freemem(head_,pattern);
        head_ = to_splice_in.head_;
    } else {
        Freemem(ultimate->next,pattern);
        ultimate->next = to_splice_in.head_;
    }
    Node* temp = to_splice_in.head_;

    while (to_splice_in.head_ != nullptr) {
        to_splice_in.head_ = to_splice_in.head_->next;
        if (to_splice_in.head_ == nullptr) {
            break;
        }
        temp->next = to_splice_in.head_;
        temp = to_splice_in.head_;
    }
    if (uright == nullptr) {
        tail_ = temp;
        temp->next = nullptr;
    } else {
        temp->next = uright;
    }
}

DNAstrand::~DNAstrand() {
    while (head_ != nullptr) {
        Node* temp = head_->next;
        delete head_;
        head_ = temp;
    }
    tail_ = nullptr;
}

