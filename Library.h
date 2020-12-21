#pragma once
#include "Book.h"
#include <iostream>
#include <string>
#include <unordered_map>

class Library {
private:
  int totalNumberOfBooks;
  int totalBooksReserved;
  std::unordered_map<std::string, Book> books;

public:
  Book AddBook(const std::string &bookName, const int &bookYearOfPublish);
  void PrintAllBooks();

  Book UpdateBook(const std::string &bookId, const std::string name,
                  const int yearOfPublish);

  void DeleteBook(const std::string &bookId);

  Book BorrowBook(const std::string &bookId, const std::string &borrowerId);

  void ReturnBook(const std::string &bookId, const std::string &borrowerId);

  BOOK_STATUS GetBookStatus(const std::string &bookId);
};
