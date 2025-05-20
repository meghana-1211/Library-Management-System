#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <string>
#include <map>

class Member
{
private:
    std::string memberID;
    std::string name;
    std::map<std::string, int> borrowedBooks;
    int borrowLimit;

public:
    Member(std::string m, std::string n, int b);
    Member(std::string m, std::string n);

    std::string get_member_id();
    std::string get_name();

    bool borrowBook(std::string i);
    bool returnBook(std::string i);
    void printDetails();
};

#endif
