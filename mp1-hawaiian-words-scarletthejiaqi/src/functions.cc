#include "functions.hpp"
#include <string>
// Your function definitions should go in this source file.
std::string DealW(char c, std::string s) {
    switch (c)
    {
    case 'i': case 'e':
        s += 'v';
        break;
    default:
        s += 'w';
        break;
    }
    return s;
}


std::string DealA(char c, std::string s) {
    switch (c)
    {
    case 'i': case 'e':
        s += "eye-";
        break;
    case 'o': case 'u':
        s += "ow-";
        break;
    default:
        s += "ah-";
        break;
    }
    return s;
}

std::string DealE(char prev, std::string s, char nex) {
    if (prev == 'a') {
        return s;
    }
    switch (nex)
    {
    case 'i' :
        s += "ay-";
        break;
    case 'u' :
        s += "eh-oo";
        break;
    default:
        s += "eh-";
        break;
    }
    return s;
}

std::string DealI(char prev, std::string s, char nex, const std::string &substring) {
    if (substring != "au") {
        if (prev == 'a' || prev == 'e' || prev == 'o' || prev == 'u') {
            return s;
        }
    }
    switch (nex)
    {
    case 'u' :
        s += "ew-";
        break;
    default:
        s += "ee-";
        break;
    }
    return s;
}

std::string DealO(char prev, std::string s, char nex) {
    if (prev == 'a') {
        return s;
    }
    switch (nex)
    {
    case 'i' :
        s += "oy-";
        break;
    default:
        s += "oh-";
        break;
    }
    return s;
}

std::string DealU(char prev, std::string s, char nex) {
    if (prev == 'a'|| prev == 'e' || prev == 'i' || prev == 'o') {
        return s;
    }
    switch (nex)
    {
    case 'i' :
        s += "ooey-";
        break;
    default:
        s += "oo-";
        break;
    }
    return s;
}

std::string EndsWith(std::string s) {
    if (s.size() > 1 && s.at(s.size() - 1) == '-') {
        return s.substr(0,s.size() - 1);
    }
    return s;
}

std::string Cases (char prev, std::string substring, char next, std::string phonetics, char current) {
    switch (current) {
      case 'w' :
        phonetics = DealW(prev, phonetics);
        break;
      case 'a' :
        phonetics = DealA(next, phonetics);
        break;
      case 'e' :
        phonetics = DealE(prev, phonetics, next);
        break;
      case 'i' :
        phonetics = DealI(prev, phonetics, next,substring);
        break;
      case 'o' :
        phonetics = DealO(prev, phonetics, next);
        break;
      case 'u' :
        phonetics = DealU(prev, phonetics, next);
        break;
      case ' ' : case '\'':
        phonetics = EndsWith(phonetics);
        phonetics += current;
        break;
      default :
        phonetics += current;
    }
    return phonetics;
}