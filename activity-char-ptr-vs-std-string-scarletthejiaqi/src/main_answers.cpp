#include <iostream>
#include <string>

int main() {
  std::string string_as_string = "Anjali Goel";
  const char* string_as_ptr = "Yug Mittal";
  char string_as_array[] = "Jonathan Sneh";

  // Q1: Can anyone guess why we needed a const before the char*

  // Q2: How can I print out a std::string on the console?
  std::cout << "string as an std::string:" << '\n' <<  string_as_string << '\n' << std::endl;

  //Q3: How can I print out a const char*
  std::cout <<"string as a char pointer:" << '\n' << string_as_ptr << '\n' << std::endl;

  //Q4: How can I print out a char array
  std::cout << "string as a char array" << '\n' << string_as_array << '\n' << std::endl;

  //Q5: Hmm, can I set a static char array as a std::string
  //string_as_array = string_as_string;
  // std::cout << "this isn't going to print! " << string_as_array << std::endl;

  // Answer: No I cannot; at a base level, string_as_string can be thought of as (similar to) a vector.
    //So, this statement effectively tries to set an array equal to a vector, which we know won't work.
    //HOWEVER: we know it works the other way around-- we can set vectors equal to arrays!

  //Q6: Hmm, can I also set a static char array as a char ptr
  // string_as_array = string_as_ptr;
  // std::cout << "this isn't going to print! " << string_as_array << std::endl;

  // Answer: No I cannot; at a base level, string_as_ptr is just a pointer to a char.
    //So I can't assign an array to a pointer the same way I can't assign an int[] = int*
    //HOWEVER: we know it works the other way around (i.e. int* = int[])!

  //Q7: How would I iterate through a std::string
  std::cout << "Iterating through std::string" << std::endl;
  for (size_t i = 0; i < string_as_string.size(); i++) {
    std::cout << string_as_string[i] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;

  //Q8: How would I do the same for const char * 
  std::cout << "Iterating through const char*" << std::endl;
  for (size_t i = 0; string_as_ptr[i] != '\0'; i++) {
    std::cout << string_as_ptr[i] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;

  //Q9: How would I do the same for char[]
  std::cout << "Iterating through char []" << std::endl;
  for (size_t i = 0; string_as_array[i] != '\0'; i++) {
    std::cout << string_as_array[i] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;

  //Q10: What happens if I dereference my const char ptr?
  std::cout << "Dereferenced char pointer: " << '\n' << *(string_as_ptr) << '\n' << std::endl;
  //Answer: I get the very first element of the char ptr*. 
  //A const char* can also store the memory location of an array of characters.

  //Q11: How would I change an element in the std::string
  //Answer: Like this
  string_as_string[2] = 'J';
  string_as_string.at(4) = 'L';
  std::cout << "std::string with modified capitalization: " << '\n' << string_as_string << '\n' << std::endl;

  //Q12: How would I change an element in the const char*?
  //Answer: You can't with current C++ methods. const char* is read only

  //Q13: How would I change an element in the char array?
  //Answer: Like this
  string_as_array[10] = 'N';
  string_as_array[11] = 'E';
  string_as_array[12] = 'H';
  std::cout << "char array with modified capitalization: " << '\n' << string_as_array << '\n' << std::endl;

  //Q14: What would happen if you added the terminating character somewhere in the middle of the char array?
  string_as_array[8] = '\0';
  std::cout << "char array with modified terminating character: " << '\n' << string_as_array << '\n' << std::endl;

  //Q15: What would happen if you added the terminating character somewhere in the middle of the std::string?
  string_as_string[6] = '\0';
  std::cout << "std::string with modified terminating character: " << '\n' << string_as_string << '\n' << std::endl;

  //follow-up to Q14-15: how is iterating over these strings different now?
  //--> Answer: it'll be the same for the std::string, but the char array will finish early once it detects the terminating character
  //follow-up to Q14-15: how does the null-terminating character "count" in terms of string length?
  //--> Answer: https://cplusplus.com/reference/cstring/strlen/
}
