#include "db.hpp"
#include <map>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <initializer_list>

void Database::CreateTable(const std::string& table_name) {
    auto* table = new DbTable;
    tables_.insert({table_name, table});
}
void Database::DropTable(const std::string& table_name) {
    if (!(tables_.contains(table_name))) {
        throw std::invalid_argument("not contain name");
    }
    DbTable* table = tables_.at(table_name);
    delete table;
    table = nullptr;
    tables_.erase(table_name);
}
DbTable& Database::GetTable(const std::string& table_name) {
    return *(tables_.at(table_name));
}

Database::Database(const Database& rhs) {
    for (const auto& pair : rhs.tables_) {
        DbTable* temp = nullptr;
        try {
            temp = new DbTable(*pair.second);
        } catch(...) {
            throw;
        }
        std::string name = pair.first;
        std::pair<std::string, DbTable*> newpair(name,temp);
        tables_.insert(newpair);
    }
}
Database& Database::operator=(const Database& rhs) {
    if (&rhs == this) {
        return *this;
    }
    Helper();
    for (const auto& pair : rhs.tables_) {
        DbTable* temp = nullptr;
        try {
            temp = new DbTable(*pair.second);
        } catch(...) {
            throw;
        }
        std::string name = pair.first;
        std::pair<std::string, DbTable*> newpair(name,temp);
        tables_.insert(newpair);
    }
    return *this;
}
void Database::Helper() {
    for (const auto& pair : tables_) {
        delete pair.second;
        tables_[pair.first] = nullptr;
    }
    tables_.clear();
}
Database::~Database() {
    Helper();
}
// friend std::ostream& operator<<(std::ostream& os, const Database& db);
