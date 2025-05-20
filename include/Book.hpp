#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include <map>

class Book
{
private:
    std::string isbn;
    int copiesAvailable;
    int totalCopies;

public:
    std::string title;
    std::string author;

    static std::map<std::string, Book *> Books;

    Book(std::string t, std::string a, std::string i, int c, int tc);
    Book();
    Book(Book *b, std::string a_new_isbn);

    std::string get_isbn();
    int get_copies_available();
    int get_total_copies();

    void updateCopies(int count);
    bool borrowBook();
    bool returnBook();
    void printDetails();
};

#endif
