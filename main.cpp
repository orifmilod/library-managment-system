#include "Library.h"
#include <ostream>
#include <sqlite3.h>
#include <string>

int main() {
  Library library;
  // std::string name = "Book1";
  // std::string name2 = "Book2";
  //
  // library.AddBook(name, 2020);
  // library.AddBook(name2, 2018);

  // Print everything out
  library.PrintAllBooks();

  return 0;
}
