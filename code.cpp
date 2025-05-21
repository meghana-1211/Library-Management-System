#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

// Book class
class Book
{
private:
    // private variables
    string isbn;
    int copiesAvailable;
    int totalCopies;

public:
    // public variables
    string title;
    string author;
    static map<string, Book *> Books;

    // parameterised constructor
    Book(string t, string a, string i, int c, int tc)
    {
        title = t;
        author = a;
        isbn = i;
        copiesAvailable = c;
        totalCopies = tc;
    }

    // default constructor
    Book()
    {
        title = "UnknownTitle";
        author = "UnknownAuthor";
        isbn = "ISBN";
        copiesAvailable = 0;
        totalCopies = 5;
    }

    // copy constructor
    Book(Book *b, string a_new_isbn)
    {
        title = b->title;
        author = b->author;
        isbn = a_new_isbn;
        copiesAvailable = b->copiesAvailable;
        totalCopies = b->totalCopies;
    }

    // getter methods
    string get_isbn() { return isbn; }
    int get_copies_available() { return copiesAvailable; }
    int get_total_copies() { return totalCopies; }

    // setter method
    void updateCopies(int count)
    {
        if (totalCopies + count < 0 || copiesAvailable + count < 0)
        {
            cout << "Invalid request! Count becomes negative" << endl;
        }
        else
        {
            totalCopies = totalCopies + count;
            copiesAvailable = copiesAvailable + count;
        }
        return;
    }
    bool borrowBook()
    {
        if (copiesAvailable > 0)
        {
            copiesAvailable--;
            return true;
        }
        else
        {
            cout << "Invalid request! Copy of book not available" << endl;
            return false;
        }
    }
    bool returnBook()
    {
        if (copiesAvailable < totalCopies)
        {
            copiesAvailable++;
            return true;
        }
        else
        {
            cout << "Invalid request! Copy of book exceeds total copies" << endl;
            return false;
        }
    }
    void printDetails()
    {
        cout << title << " " << author << endl;
    }
};

// Member class
class Member
{
private:
    // private variables
    string memberID;
    string name;
    map<string, int> borrowedBooks;
    int borrowLimit;

public:
    // parameterised constructor
    Member(string m, string n, int b)
    {
        memberID = m;
        name = n;
        borrowLimit = b;
    }

    // default constructor
    Member(string m, string n)
    {
        memberID = m;
        name = n;
        borrowLimit = 3;
    }

    // getter methods
    string get_member_id()
    {
        return memberID;
    }
    string get_name()
    {
        return name;
    }

    // utility methods
    bool borrowBook(string i)
    {
        int no_of_copies_borrowed = 0;
        for (auto book : borrowedBooks)
        {
            no_of_copies_borrowed = no_of_copies_borrowed + book.second;
        }
        if (Book::Books.find(i) == Book::Books.end() || Book::Books[i]->get_copies_available() <= 0)
        {
            cout << "Invalid request! Copy of book not available" << endl;
            return false;
        }
        else if (no_of_copies_borrowed >= borrowLimit)
        {
            cout << "Invalid request! Borrow limit exceeded" << endl;
            return false;
        }
        else
        {
            bool temp = Book::Books[i]->borrowBook();
            if (temp)
            {
                if (borrowedBooks.find(i) == borrowedBooks.end())
                {
                    borrowedBooks[i] = 1;
                }
                else
                {
                    borrowedBooks[i]++;
                }
            }
            return temp;
        }
    }
    bool returnBook(string i)
    {
        if (Book::Books[i]->get_copies_available() >= Book::Books[i]->get_total_copies())
        {
            cout << "Invalid request! Copy of book exceeds total copies" << endl;
            return false;
        }
        else if (borrowedBooks.find(i) == borrowedBooks.end() || borrowedBooks[i] == 0)
        {
            cout << "Invalid request! Book not borrowed" << endl;

            return false;
        }
        else
        {
            bool temp = Book::Books[i]->returnBook();
            if (temp)
            {
                borrowedBooks[i]--;
            }
            return temp;
        }
    }
    void printDetails()
    {
        for (auto m : borrowedBooks)
        {
            if (m.second > 0)
            {
                cout << memberID << " " << name << " " << m.first << " " << m.second << endl;
            }
        }
    }
};

class Library
{
private:
    static vector<Book *> books;
    static vector<Member *> members;

public:
    static map<string, Member *> Members;
    static bool addBook(Book *b)
    {
        for (auto book : books)
        {
            if (book->get_isbn() == b->get_isbn())
            {
                cout << "Invalid request! Book with same isbn already exists" << endl;
                return false;
            }
        }
        Book::Books[b->get_isbn()] = b;
        books.push_back(b);
        return true;
    }
    static bool registerMember(Member *m)
    {
        for (auto member : members)
        {
            if (member->get_member_id() == m->get_member_id())
            {
                cout << "Invalid request! Member with same id already exists" << endl;
                return false;
            }
        }
        Members[m->get_member_id()] = m;
        members.push_back(m);
        return true;
    }
    static bool borrowBook(string memberID, string isbn)
    {
        return Library::Members[memberID]->borrowBook(isbn);
    }
    static bool returnBook(string memberID, string isbn)
    {
        return Library::Members[memberID]->returnBook(isbn);
    }
    static void printLibraryDetails()
    {
        for (auto book : books)
        {
            cout << book->title << " " << book->author << " " << book->get_copies_available() << endl;
        }
        for (auto member : members)
        {
            cout << member->get_member_id() << " " << member->get_name() << endl;
        }
    }
};
map<string, Book *> Book::Books;
map<string, Member *> Library::Members;
vector<Book *> Library::books;
vector<Member *> Library::members;
int main()
{
    string temp;
    while (true)
    {
        cin >> temp;
        if (temp == "Book")
        {
            string temp1;
            cin >> temp1;
            if (temp1 == "None")
            {
                Book *temp_book = new Book;
                Library::addBook(temp_book);
            }
            else if (temp1 == "ExistingBook")
            {
                string old_isbn;
                string new_isbn;
                cin >> old_isbn >> new_isbn;
                Book *temp_book = new Book(Book::Books[old_isbn], new_isbn);
                Library::addBook(temp_book);
            }
            else
            {
                string temp_a, temp_i;
                int temp_c, temp_tc;
                cin >> temp_a >> temp_i >> temp_c >> temp_tc;
                Book *temp_book = new Book(temp1, temp_a, temp_i, temp_c, temp_tc);
                Library::addBook(temp_book);
            }
        }
        else if (temp == "UpdateCopiesCount")
        {
            string temp_isbn;
            int temp_count;
            cin >> temp_isbn >> temp_count;
            Book::Books[temp_isbn]->updateCopies(temp_count);
        }
        else if (temp == "Member")
        {
            string temp1;
            cin >> temp1;
            if (temp1 == "NoBorrowLimit")
            {
                string temp_m;
                string temp_n;
                cin >> temp_m >> temp_n;
                Member *temp_member = new Member(temp_m, temp_n);
                Library::registerMember(temp_member);
            }
            else
            {
                string temp_n;
                int temp_b;
                cin >> temp_n >> temp_b;
                Member *temp_member = new Member(temp1, temp_n, temp_b);
                Library::registerMember(temp_member);
            }
        }
        else if (temp == "Borrow")
        {
            string temp_i;
            string temp_m;
            cin >> temp_m >> temp_i;
            Library::borrowBook(temp_m, temp_i);
        }
        else if (temp == "Return")
        {
            string temp_i;
            string temp_m;
            cin >> temp_m >> temp_i;
            Library::returnBook(temp_m, temp_i);
        }
        else if (temp == "PrintBook")
        {
            string temp_i;
            cin >> temp_i;
            Book::Books[temp_i]->printDetails();
        }
        else if (temp == "PrintMember")
        {
            string temp_m;
            cin >> temp_m;
            Library::Members[temp_m]->printDetails();
        }
        else if (temp == "PrintLibrary")
        {
            Library::printLibraryDetails();
        }
        else if (temp == "Done")
        {
            break;
        }
    };
}