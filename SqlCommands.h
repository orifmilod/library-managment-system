#pragma once
#include <string>

namespace SqlCommands {
typedef std::string Type;
Type DropBookTable = "DROP TABLE Book";

Type CreateBookTable =
    "CREATE TABLE IF NOT EXISTS Book (id INTEGER PRIMARY KEY, name TEXT, "
    "status TEXT, yearOfPublish TEXT, borrowerId TEXT)";
} // namespace SqlCommands
