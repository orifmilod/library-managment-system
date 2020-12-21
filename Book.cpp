#include "Book.h"
#include <string>

Book::Book(const std::string &_bookId, const std::string &_name,
           const int &_yearOfPublish)
    : id(_bookId), name(_name), yearOfPublish(_yearOfPublish) {}

std::string Book::getId() { return id; }

