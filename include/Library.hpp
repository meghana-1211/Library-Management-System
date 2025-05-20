#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <vector>
#include <string>
#include "Book.hpp"
#include "Member.hpp"

class Library
{
private:
    static std::vector<Book *> books;
    static std::vector<Member *> members;

public:
    static std::map<std::string, Member *> Members;

    static bool addBook(Book *b);
    static bool registerMember(Member *m);
    static bool borrowBook(std::string memberID, std::string isbn);
    static bool returnBook(std::string memberID, std::string isbn);
    static void printLibraryDetails();
};

#endif
