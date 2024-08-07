#include <iostream>

#include "db.hpp"
#include "db_table.hpp"

int main() {
  // write informal tests here
  //Table: DeleteColumnByIdx(1) from table with (2 rows; 3 columns {kString kInt kString})
  DbTable my_table;
  Database base;
  base.CreateTable("my_table");
  Database base2(base);
  my_table.AddColumn({"string", DataType::kString});
  my_table.AddColumn({"age", DataType::kInt});
  my_table.AddColumn({"another string", DataType::kString});


  // my_table.AddColumn({"Age", DataType::kInt});
  // // my_table.AddColumn({"Salary", DataType::kDouble});


  my_table.AddRow({"apple","1","ant"});
  my_table.AddRow({"banana","2","ant"});
  // my_table.AddRow({"pear","3","ant"});


  // my_table.AddRow({"Bob Johnson", "42", "60000.00"});
  my_table.DeleteColumnByIdx(1); 
  // my_table.DeleteRowById(2); 

  // DbTable another(my_table);
  // DbTable third;
  // third=my_table;
  
  std::cout << my_table << std::endl;
}

//cast to void, temp the location in for loop, col or row
//cannot access the second row, the first one(string3)