#include "illini_book.hpp"

// Your code here!
IlliniBook::IlliniBook(const std::string &people_fpath, const std::string &relations_fpath) {
    std::ifstream people(people_fpath);
    std::ifstream relations(relations_fpath);
    std::string s;
    std::string eachrelationline;
    while (std::getline(people,s)) {
        int num = std::stoi(s);
        if (num > maxuin_) {
            maxuin_ = num;
        }
        map_.insert({num,std::list<std::vector<std::string>>()});
    }
    while (std::getline(relations,eachrelationline)) {
        std::vector<std::string> each = utilities::Split(eachrelationline, ',');
        int firstnum = std::stoi(each.at(0));
        int secondnum = std::stoi(each.at(1));
        std::vector<std::string> firstrelation = each;
        std::vector<std::string> secondrelation = each;
        firstrelation.erase(firstrelation.begin());
        secondrelation.erase(secondrelation.begin()+1);
        Getvec(firstnum).push_back(firstrelation);
        Getvec(secondnum).push_back(secondrelation);
    }

}
bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
    std::set<int> visited;
    std::list<std::vector<std::string>> list1 = map_.find(uin_1)->second;
    std::queue<int> q;
    for (std::vector<std::string> vec : list1) {
        int curr = std::stoi(vec.at(0));
        q.push(curr);
    }
    while (!q.empty()) {
        if (q.front() == uin_2) {
            return true;
        }
        visited.insert(q.front());
        std::list<std::vector<std::string>> eachlist = map_.find(q.front())->second;
        for (std::vector<std::string> vec : eachlist) {
            int curr =std::stoi(vec[0]);
            if (visited.find(curr) == visited.end()) {
                visited.insert(curr);
                q.push(curr);
            }
        }
        q.pop();
    }
    return false;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
    std::map<int,int> distance;
    distance.insert({uin_1,0});
    std::set<int> visited;
    std::list<std::vector<std::string>> list1 = map_.find(uin_1)->second;
    std::queue<int> q;
    for (std::vector<std::string> vec : list1) {
        int curr = std::stoi(vec.at(0));
        distance.insert({curr,1});
        q.push(curr);
    }
    while (!q.empty()) {
        visited.insert(q.front());
        std::list<std::vector<std::string>> eachlist = map_.find(q.front())->second;
        for (std::vector<std::string> vec : eachlist) {
            int curr =std::stoi(vec[0]);
            if (visited.find(curr) == visited.end()) {
                int value = distance.find(q.front())->second + 1;
                distance.insert({curr,value});
                visited.insert(curr);
                q.push(curr);
            }
        }
        q.pop();
    }
    if (distance.find(uin_2) == distance.end()) {
        return -1;
    }
    return distance.find(uin_2)->second;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const {
    std::set<int> visited;
    std::list<std::vector<std::string>> list1 = map_.find(uin_1)->second;
    std::queue<int> q;
    for (std::vector<std::string> vec : list1) {
        std::string currelation = vec.at(1);
        if (currelation == relationship) {
            int curr = std::stoi(vec.at(0));
            q.push(curr);
        }
    }
    while (!q.empty()) {
        if (q.front() == uin_2) {
            return true;
        }
        visited.insert(q.front());
        std::list<std::vector<std::string>> eachlist = map_.find(q.front())->second;
        for (std::vector<std::string> vec : eachlist) {
            std::string currelation = vec.at(1);
            if (currelation == relationship) {
                int curr =std::stoi(vec[0]);
                if (visited.find(curr) == visited.end()) {
                    visited.insert(curr);
                    q.push(curr);
                }
            }
        }
        q.pop();
    }
    return false;
}
int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
    std::map<int,int> distance;
    distance.insert({uin_1,0});
    std::set<int> visited;
    std::list<std::vector<std::string>> list1 = map_.find(uin_1)->second;
    std::queue<int> q;
    for (std::vector<std::string> vec : list1) {
        std::string currelation = vec.at(1);
        if (currelation == relationship) {
            int curr = std::stoi(vec.at(0));
            distance.insert({curr,1});
            q.push(curr);
        }
    }
    while (!q.empty()) {
        visited.insert(q.front());
        std::list<std::vector<std::string>> eachlist = map_.find(q.front())->second;
        for (std::vector<std::string> vec : eachlist) {
            std::string currelation = vec.at(1);
            if (currelation == relationship) {
                int curr =std::stoi(vec[0]);
                if (visited.find(curr) == visited.end()) {
                    int value = distance.find(q.front())->second + 1;
                    distance.insert({curr,value});
                    visited.insert(curr);
                    q.push(curr);
                }
            }
        }
        q.pop();
    }
    if (distance.find(uin_2) == distance.end()) {
        return -1;
    }
    return distance.find(uin_2)->second;
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
    std::set<int> visited;
    std::list<std::vector<std::string>> list = map_.find(uin)->second;
    std::queue<int> q;
    std::map<int,int> path;
    std::vector<int> result;
    std::set<int> resultset;
    if (n == 0) {
        result.push_back(uin);
        return result;
    }
    path.insert({uin,0});
    visited.insert(uin);
    for (std::vector<std::string> vec : list) {
        int curr = std::stoi(vec.at(0));
        path.insert({curr,1});
        q.push(curr);
    }
    while (!q.empty()) {
        if (path.find(q.front()) != path.end() && path.find(q.front()) ->second == n) {
            resultset.insert(q.front());
        }
        visited.insert(q.front());
        std::list<std::vector<std::string>> currlist = map_.find(q.front())->second;
        for (std::vector vec : currlist) {
            int key = std::stoi(vec.at(0));
            if (visited.find(key) == visited.end()) {
                int value = path.find(q.front()) ->second + 1;
                path.insert({key,value});
                visited.insert(key);
                q.push(key);
            }
        }
        q.pop();
    }
    for (int i : resultset) {
        result.push_back(i);
    }
    return result;
}

size_t IlliniBook::CountGroups() const {
    std::map<int,std::string> node;
    int count = 0;
    for (auto vec = map_.begin(); vec != map_.end(); ++vec) {
        node.insert({vec->first,"unseen"});
    }
    std::queue<int> q;
    for (auto vec = map_.begin(); vec != map_.end(); ++vec) {
        if (node.at(vec->first) == "unseen") {
            count++;
            std::list<std::vector<std::string>> list = vec->second;
            for (std::vector<std::string> each : list) {
                int curr = std::stoi(each.at(0));
                node.at(curr) = "visited";
                q.push(curr);
            }
            while (!q.empty()) {
                std::list<std::vector<std::string>> eachlist = map_.find(q.front())->second;
                for (std::vector<std::string> child : eachlist) {
                    int curr =std::stoi(child[0]);
                    if (node.at(curr) == "unseen") {
                        node.at(curr) = "visited";
                        q.push(curr);
                    }
                }
                q.pop();
            }
        }
    }
    return count;
}

size_t IlliniBook::CountGroups(const std::string &relationship) const {
    std::map<int,std::string> node;
    int count = 0;
    for (auto vec = map_.begin(); vec != map_.end(); ++vec) {
        node.insert({vec->first,"unseen"});
    }
    std::queue<int> q;
    for (auto vec = map_.begin(); vec != map_.end(); ++vec) {
        if (node.at(vec->first) == "unseen") {
            count++;
            std::list<std::vector<std::string>> list = vec->second;
            for (std::vector<std::string> each : list) {
                if (each.at(1) == relationship) {
                    int curr = std::stoi(each.at(0));
                    node.at(curr) = "visited";
                    q.push(curr);
                }
            }
            while (!q.empty()) {
                std::list<std::vector<std::string>> eachlist = map_.find(q.front())->second;
                for (std::vector<std::string> child : eachlist) {
                    if (child.at(1) == relationship) {
                        int curr =std::stoi(child.at(0));
                        if (node.at(curr) == "unseen") {
                            node.at(curr) = "visited";
                            q.push(curr);
                        }
                    }
                }
                q.pop();
            }
        }
    }
    return count;
}

size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
    std::map<int,std::string> node;
    int count = 0;
    for (auto vec = map_.begin(); vec != map_.end(); ++vec) {
        node.insert({vec->first,"unseen"});
    }
    std::queue<int> q;
    for (auto vec = map_.begin(); vec != map_.end(); ++vec) {
        if (node.at(vec->first) == "unseen") {
            count++;
            std::list<std::vector<std::string>> list = vec->second;
            for (std::vector<std::string> each : list) {
                for (const std::string& relationship : relationships) {
                    if (each.at(1) == relationship) {
                        int curr = std::stoi(each.at(0));
                        node.at(curr) = "visited";
                        q.push(curr);
                        break;
                    }
                }
            }
            while (!q.empty()) {
                std::list<std::vector<std::string>> eachlist = map_.find(q.front())->second;
                for (std::vector<std::string> child : eachlist) {
                    for (const std::string& relationship : relationships) {
                        if (child.at(1) == relationship) {
                            int curr =std::stoi(child.at(0));
                            if (node.at(curr) == "unseen") {
                                node.at(curr) = "visited";
                                q.push(curr);
                            }
                        }
                    }
                }
                q.pop();
            }
        }
    }
    return count;
}


