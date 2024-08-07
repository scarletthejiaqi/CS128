#include "functions.hpp"
#include <string>
#include <iostream>
int Longest(const std::string& DNA, const std::string& SEQ) {
    int temp = 0;
    int num = 0;
    unsigned int sequence_len =SEQ.size();
    unsigned int len = DNA.size()-sequence_len;
    for (unsigned int i = 0; i <= len; ++i) {
        if (DNA.substr(i,sequence_len) == SEQ) {
            temp++;
            i+=sequence_len - 1;
            if (i >=len) {
                num = Max(num,temp);
            }
        } else {
            num = Max(num,temp);
            temp = 0;
        }
    }
    return num;
}

int Max(int a, int b) {
    if(a > b) {
        return a;
    }
    return b;
}
int FindPerson(std::vector<std::string> first_vector,const std::string& DNA,std::vector<std::string> person) {
    std::string sequence;
    std::vector<int> num_list;
    unsigned int len = first_vector.size();
    for (unsigned int i = 1; i < len; ++i) {
        sequence = first_vector.at(i);
        const std::string& seq = sequence;
        num_list.push_back(Longest(DNA,seq));
    }
    for (unsigned int i = 0; i < num_list.size(); ++i) {
        if(num_list.at(i) != std::stoi(person.at(i+1))) {
            return 0;
        }
    }
    return 1;

}

