#pragma once
#include <string>

enum BOOK_STATUS {
  FREE,
  RESERVED,
};

class Book {
private:
  std::string id;

public:
  std::string name;
  int yearOfPublish;
  BOOK_STATUS status;
  std::string borrowerId;

  Book(const std::string &bookId, const std::string &_name,
       const int &_yearOfPublish);

  std::string getId();
};
