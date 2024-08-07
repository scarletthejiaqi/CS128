#include "cord_utilities.hpp"
SharedPointer<Cord> ConcatCords(const SharedPointer<Cord>& left_cord, const SharedPointer<Cord>& right_cord) {
    if (left_cord.Get() == nullptr || right_cord.Get() == nullptr) {
        throw std::invalid_argument("either is nullptr");
    }
    Cord* concat = new Cord();
    concat->left_ = left_cord;
    concat->right_ = right_cord;
    concat->length_ = left_cord.Get()->length_ + right_cord.Get()->length_;
    SharedPointer<Cord> pointer(concat);
    return pointer;
}

SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord, unsigned int lower_idx, unsigned int upper_idx) {
    if (lower_idx >= upper_idx || upper_idx > curr_cord.Get()->Length() || lower_idx > curr_cord.Get()->Length()) {
        throw std::invalid_argument("lower >=  upper");
    }
        //reuse
    if (upper_idx - lower_idx == curr_cord.Get()->Length()) {
        //whole range
        return curr_cord;
    }

    if (curr_cord.Get()->Left().Get() == nullptr && curr_cord.Get()->Right().Get() == nullptr) {
        //leaf but not whole range, use Data to create substr
        Cord* substrcord = new Cord(curr_cord.Get()->Data().substr(lower_idx, upper_idx - lower_idx));
        SharedPointer<Cord> substrcord_pointer(substrcord);
        return substrcord_pointer;
    }
    if (curr_cord.Get()->Left().Get()->Length() >= upper_idx) {
        //all substr at left, recursive left
        return SubString(curr_cord.Get()->Left(),lower_idx,upper_idx);
    } 
    if (curr_cord.Get()->Left().Get()->Length() <= lower_idx) {
        //all substr at right, recursive right
        return SubString(curr_cord.Get()->Right(),lower_idx - curr_cord.Get()->Left().Get()->Length(),upper_idx - curr_cord.Get()->Left().Get()->Length());
    } 
    //in bewteen, recursive left and right and concat
    SharedPointer<Cord> leftsubstr = SubString(curr_cord.Get()->Left(),lower_idx,curr_cord.Get()->Left().Get()->Length());
    SharedPointer<Cord> rightsubstr = SubString(curr_cord.Get()->Right(),0, upper_idx - curr_cord.Get()->Left().Get()->Length());
    return ConcatCords(leftsubstr,rightsubstr);
    
}

