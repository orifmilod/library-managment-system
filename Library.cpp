#include "Library.h"
#include "Book.h"
#include <cstdlib>

#define ID_LEN 6

std::string RandomString(int len) {
  std::string str =
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  std::string newstr;
  int pos;
  while (newstr.size() != len) {
    pos = ((rand() % (str.size() - 1)));
    newstr += str.substr(pos, 1);
  }
  return newstr;
}

Library::Library() {
  int resultCode = sqlite3_open("test.db", &db);

  if (resultCode) {
    std::cout << "Can't open database: %s\n" << sqlite3_errmsg(db) << std::endl;
    return;
  }

  std::cout << "Opened database successfully" << std::endl;
}

Book Library::AddBook(const std::string &bookName,
                      const int &bookYearOfPublish) {

  std::string bookId = RandomString(ID_LEN);
  std::cout << "New book id" << bookId << std::endl;

  // Make sure the id does not exist already
  while (books.find(bookId) != books.end()) {
    bookId = RandomString(ID_LEN);
  }

  Book newBook(bookId, bookName, bookYearOfPublish);
  books.insert(std::make_pair(bookId, newBook));

  return newBook;
};

void Library::PrintAllBooks() {
  for (auto &book : books) {
    std::cout << book.second.name << std::endl;
  }
}

Book Library::UpdateBook(const std::string &bookId, const std::string name,
                         const int yearOfPublish) {
  // TODO: Throw an exception if cant find key
  auto it = books.find(bookId);

  it->second.name = name;
  it->second.yearOfPublish = yearOfPublish;

  return books.at(bookId);
}

void Library::DeleteBook(const std::string &bookId) { books.erase(bookId); }

Book Library::BorrowBook(const std::string &bookId,
                         const std::string &borrowerId) {
  auto it = books.find(bookId);
  // TODO: Throw an exception if cant find key
  // If already reserved

  if (it->second.status == RESERVED) {
    // TODO: Throw exception because book is already reserved
  }

  it->second.status = RESERVED;
  it->second.borrowerId = borrowerId;

  return books.at(bookId);
}

void Library::ReturnBook(const std::string &bookId,
                         const std::string &borrowerId) {
  auto it = books.find(bookId);
  // TODO: Throw an exception if cant find key
  // TODO: Throw an exception if this borrow did not reserved it and is trying
  // to return it

  if (it->second.borrowerId == borrowerId) {
    it->second.status = FREE;
    it->second.borrowerId = "";
  }
}

BOOK_STATUS Library::GetBookStatus(const std::string &bookId) {
  auto it = books.find(bookId);
  // TODO: Throw an exception if cant find key

  return books.at(bookId).status;
}
