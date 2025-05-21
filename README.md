#  Library Management System

This C++ project simulates a basic **Library Management System** that allows book management, member registration, and operations such as borrowing and returning books. It supports detailed constraints and edge case handling, making it robust for realistic scenarios.

---

##  Features

###  Book Class
- **Attributes**
  - `title` (public): Title of the book.
  - `author` (public): Author of the book.
  - `isbn` (private): Unique book identifier.
  - `copiesAvailable` (private): Available copies.
  - `totalCopies` (private): Total number of copies.

- **Constructors**
  - Parameterized constructor.
  - Constructor with default values (`"UnknownTitle"`, `"UnknownAuthor"`, `"ISBN"`, `0`, `5`).
  - Copy constructor with new ISBN.

- **Methods**
  - Getters for `isbn`, `copiesAvailable`, `totalCopies`.
  - `updateCopies(count)`: Adjusts book count (rejects negative totals).
  - `borrowBook()`: Decreases `copiesAvailable` if possible.
  - `returnBook()`: Increases `copiesAvailable` if not exceeding `totalCopies`.
  - `printDetails()`: Prints book's title and author.

- **Constraints**
  - Unique ISBN enforced.
  - `copiesAvailable` must remain between `0` and `totalCopies`.

---

###  Member Class
- **Attributes**
  - `memberID` (private): Unique member identifier.
  - `name` (public): Member name.
  - `borrowedBooks` (private): Map of ISBN to quantity borrowed.
  - `borrowLimit` (private): Maximum borrowable books (default = 3).

- **Constructors**
  - Parameterized constructor.
  - Constructor with default `borrowLimit`.

- **Methods**
  - `borrowBook(isbn)`: Borrows book if limit not exceeded.
  - `returnBook(isbn)`: Returns book if borrowed.
  - `printDetails()`: Prints member info and borrowed books.

- **Constraints**
  - Can borrow same book multiple times (up to availability).
  - Cannot exceed `borrowLimit` or 15 total borrowed books.

---

###  Library Class
- **Attributes**
  - `books` (private): Vector of all books.
  - `members` (private): Vector of all members.

- **Methods**
  - `addBook(Book&)`: Adds new book (enforces unique ISBN).
  - `registerMember(Member&)`: Registers new member (enforces unique ID).
  - `borrowBook(memberID, isbn)`: Validates and processes borrowing.
  - `returnBook(memberID, isbn)`: Validates and processes returning.
  - `printLibraryDetails()`: Prints book and member details.

- **Constraints**
  - Max 50 books, 150 members.
  - Each book: Max 15 copies.
  - Each member: Max 15 borrowed books.

---

