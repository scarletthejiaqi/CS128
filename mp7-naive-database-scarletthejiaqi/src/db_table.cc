#include "db_table.hpp"

#include <initializer_list>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
// const unsigned int kRowGrowthRate = 2;

// member function
void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (col_descs_.size() == row_col_capacity_) {
    for (unsigned int i = 0; i < next_unique_id_; ++i) {
      if (!(rows_.contains(i))) {
        continue;
      }
      void** row = rows_.at(i);
      unsigned int newcap = row_col_capacity_ * 2;
      void** newrow = new void*[newcap];
      for (unsigned int col = 0; col < row_col_capacity_; ++col) {
        newrow[col] = row[col];
      }
      //new comment
      delete[] rows_.at(i);
      rows_.at(i) = newrow;
    }
    row_col_capacity_ *= 2;
  }
  col_descs_.push_back(col_desc);
  for (unsigned int i = 0; i < next_unique_id_; ++i) {
    void** row = rows_.at(i);
    if (col_desc.second == DataType::kDouble) {
      row[col_descs_.size() - 1] = static_cast<void*>(new double(0.0));
    } else if (col_desc.second == DataType::kInt) {
      row[col_descs_.size() - 1] = static_cast<void*>(new int(0));
    } else if (col_desc.second == DataType::kString) {
      row[col_descs_.size() - 1] = static_cast<void*>(new std::string(""));
    }
  }
}
void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if (col_idx < 0 || col_idx >= col_descs_.size()) {
    throw std::out_of_range("out of range");
  }
  if (col_descs_.size() == 1 && !(rows_.empty())) {
    throw std::runtime_error(
        "any table with at least one row must have at least one column");
  }
  for (unsigned int i = 0; i < next_unique_id_; ++i) {
    if (!(rows_.contains(i))) {
      continue;
    }
    if (col_descs_.at(col_idx).second == DataType::kDouble) {
      delete static_cast<double*>(rows_[i][col_idx]);
    } else if (col_descs_.at(col_idx).second == DataType::kInt) {
      delete static_cast<int*>(rows_[i][col_idx]);
    } else if (col_descs_.at(col_idx).second == DataType::kString){
      delete static_cast<std::string*>(rows_[i][col_idx]);
    }
    rows_[i][col_idx] = nullptr;
    for (unsigned int col = col_idx; col < col_descs_.size() - 1; ++col) {
      rows_[i][col] = rows_[i][col + 1];
    }
    rows_[i][col_descs_.size() - 1] = nullptr;
  }
  col_descs_.erase(col_descs_.begin() + col_idx);
}

void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  if (col_data.size() != col_descs_.size()) {
    throw std::invalid_argument("not the same size");
  }
  void** newline = new void*[row_col_capacity_];

  for (unsigned int i = 0; i < col_descs_.size(); ++i) {
    unsigned int dataindex = 0;
    std::pair<std::string, DataType> col_desc = col_descs_.at(i);
    for (const std::string& str : col_data) {
      if (dataindex != i) {
        dataindex++;
        continue;
      }
      if (col_desc.second == DataType::kDouble) {
        newline[i] = static_cast<void*>(new double(std::stod(str)));
      } else if (col_desc.second == DataType::kInt) {
        newline[i] = static_cast<void*>(new int(std::stoi(str)));
      } else if (col_desc.second == DataType::kString) {
        newline[i] = static_cast<void*>(new std::string(str));
      }
      break;
    }
  }
  rows_.insert(std::pair<unsigned int, void**>(next_unique_id_, newline));
  next_unique_id_ += 1;
}
void DbTable::DeleteRowById(unsigned int id) {
  if (id < 0 || id >= next_unique_id_) {
    throw std::out_of_range("cannot delete");
  }
  for (unsigned int i = 0; i < col_descs_.size(); ++i) {
    if (col_descs_[i].second == DataType::kDouble) {
      delete static_cast<double*>(rows_.at(id)[i]);
    } else if (col_descs_[i].second == DataType::kInt) {
      delete static_cast<int*>(rows_.at(id)[i]);
    } else if (col_descs_[i].second == DataType::kString){
      delete static_cast<std::string*>(rows_.at(id)[i]);
    }
  }
  delete[] rows_.at(id);
  rows_.at(id) = nullptr;
  rows_.erase(id);
}

// initialization
DbTable::DbTable(const DbTable& rhs):
    next_unique_id_(rhs.next_unique_id_),
    row_col_capacity_(rhs.row_col_capacity_),
    col_descs_(rhs.col_descs_) {
  // rows
  
  for (unsigned int i = 0; i < rhs.next_unique_id_; ++i) {
    if (!(rhs.rows_.contains(i))) {
      continue;
    }
    void** temp = new void*[row_col_capacity_];
    void** eachcol = rhs.rows_.at(i);
    for (unsigned int col = 0; col < rhs.col_descs_.size(); ++col) {
      if (col_descs_[col].second == DataType::kDouble) {
        temp[col] = static_cast<void*>(new double(*static_cast<double*>(eachcol[col])));
      } else if (col_descs_[col].second == DataType::kInt) {
        temp[col] = static_cast<void*>(new int(*static_cast<int*>(eachcol[col])));
      } else if (col_descs_[col].second == DataType::kString){
        temp[col] = static_cast<void*>(new std::string(*static_cast<std::string*>(eachcol[col])));
      }
    }
    std::pair<const unsigned int, void**> mypair(i, temp);
    rows_.insert(mypair);
  }
}

DbTable& DbTable::operator=(const DbTable& rhs) {
  if (&rhs == this) {
    return *this;
  }
  Dehelper();
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_ = rhs.col_descs_;
  // rows_
  
  for (unsigned int i = 0; i < rhs.next_unique_id_; ++i) {
    if (!(rhs.rows_.contains(i))) {
      continue;
    }
    void** temp = new void*[row_col_capacity_];
    void** eachcol = rhs.rows_.at(i);
    for (unsigned int col = 0; col < rhs.col_descs_.size(); ++col) {
      if (col_descs_[col].second == DataType::kDouble) {
        temp[col] = static_cast<void*>(new double(*static_cast<double*>(eachcol[col])));
      } else if (col_descs_[col].second == DataType::kInt) {
        temp[col] = static_cast<void*>(new int(*static_cast<int*>(eachcol[col])));
      } else if (col_descs_[col].second == DataType::kString){
        temp[col] = static_cast<void*>(new std::string(*static_cast<std::string*>(eachcol[col])));
      }
    }
    std::pair<const unsigned int, void**> mypair(i, temp);
    rows_.insert(mypair);
  }
  return *this;
}
void DbTable::Dehelper() {
  for (unsigned int row_id = 0; row_id < next_unique_id_; ++row_id) {
    if (rows_.contains(row_id)) {
      DeleteRowById(row_id);
    }
  }
  rows_.clear();
  col_descs_.clear();
}
DbTable::~DbTable() {
  Dehelper();
}
std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  for (unsigned int i = 0; i < table.col_descs_.size(); ++i) {
    os << table.col_descs_.at(i).first;
    if (table.col_descs_.at(i).second == DataType::kDouble) {
      os << "(double)";
    } else if (table.col_descs_.at(i).second == DataType::kInt) {
      os << "(int)";
    } else if (table.col_descs_.at(i).second == DataType::kString) {
      os << "(std::string)";
    }
    if (i != table.col_descs_.size() - 1) {
      os << ", ";
    }
  }
  os << std::endl;
  // put in rows_
  for (unsigned int row = 0; row < table.next_unique_id_; ++row) {
    if (!(table.rows_.contains(row))) {
      continue;
    }
    void** eachrow = table.rows_.at(row);
    for (unsigned int col = 0; col < table.col_descs_.size(); ++col) {
      if (table.col_descs_.at(col).second == DataType::kDouble) {
        os << *(static_cast<double*>(eachrow[col]));
      } else if (table.col_descs_.at(col).second == DataType::kInt) {
        os << *(static_cast<int*>(eachrow[col]));
      } else if (table.col_descs_.at(col).second == DataType::kString) {
        os << *(static_cast<std::string*>(eachrow[col]));
      }
      if (col != table.col_descs_.size() - 1) {
        os << ",";
      }
    }
    // if the last one is deleted, then is not correct, how to not let the last line newline
    if (row != table.rows_.size() - 1) {
      os << std::endl;
    }
  }
  return os;
}
