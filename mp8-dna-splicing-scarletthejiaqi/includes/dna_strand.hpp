#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();
  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  void Freemem(Node* ultimate,const char* pattern);
  void Helper(Node*& uright, const char* pattern,Node*& head_, bool& found, DNAstrand& to_splice_in, Node*& ultimate);

  // void puthead(Node* a) {head_ = a;}
  // void puttail(Node* a) {tail_ = a;}
  // Node* gethead() {return head_;}


private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif