#include "Library.h"
#include "Book.h"
#include "SqlCommands.h"

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

/*
 * Arguments:
 *   unused - Ignored in this case, see the documentation for sqlite3_exec
 *    count - The number of columns in the result set
 *     data - The row's data
 *  columns - The column names
 */
static int database_callback(void *list, int count, char **data,
                             char **columns) {
  int index;

  int yearOfPublish;
  std::string bookId, bookName, bookStatus, borrowerId;

  for (index = 0; index < count; index++) {
    if (strcmp(columns[index], "id") == 0) {
      bookId = data[index];
    }

    if (strcmp(columns[index], "name") == 0) {
      bookName = data[index];
    }

    if (strcmp(columns[index], "bookStatus") == 0) {
      bookStatus = data[index];
    }

    if (strcmp(columns[index], "borrowerId") == 0) {
      borrowerId = data[index];
    }

    if (strcmp(columns[index], "yearOfPublish") == 0) {
      yearOfPublish = atoi(data[index]);
    }
  }

  printf("%s %s %s %s %d \n", bookId.c_str(), bookName.c_str(),
         bookStatus.c_str(), borrowerId.c_str(), yearOfPublish);
  return 0;
}

Library::Library() {
  int resultCode = sqlite3_open("test.db", &db);

  if (resultCode) {
    std::cout << "Can't open database: %s\n" << sqlite3_errmsg(db) << std::endl;
    return;
  }

  // sqlite3_exec(db, "", database_callback, NULL, NULL);
  sqlite3_exec(db, SqlCommands::CreateBookTable.c_str(), database_callback,
               &books, NULL);

  std::cout << "Opened database successfully" << std::endl;
}

Library::~Library() {
  std::cout << "Closing database connection!" << std::endl;
  sqlite3_close(db);
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
