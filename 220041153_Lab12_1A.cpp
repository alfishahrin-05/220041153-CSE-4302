#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <fstream>
using namespace std;

class Book 
{
    private:
        string title, author, ISBN;
    public:
    Book(string t, string a, string i) : title(t), author(a), ISBN(i) {}

    string getTitle() const 
    { 
        return title; 
    }
    string getISBN() const 
    { 
        return ISBN; 
    }
    string serialize() const {
        return title + "," + author + "," + ISBN;
    }

    static Book deserialize(const string& data) {
        size_t firstComma = data.find(',');
        size_t secondComma = data.find(',', firstComma + 1);

        string t = data.substr(0, firstComma);
        string a = data.substr(firstComma + 1, secondComma - firstComma - 1);
        string i = data.substr(secondComma + 1);
        return Book(t, a, i);
    }
    void display() const {
        cout << "Title: " << title << ", Author: " << author << ", ISBN: " << ISBN << endl;
    }
};

class Library 
{
    private:
        vector<Book> inventory;
        deque<Book> borrowedBooks;
        list<Book> archivedBooks;

    public:
        void addBook(const Book& book) 
        {
            inventory.push_back(book);
        }
        void borrowBook() {
        if (inventory.empty()) {
            cout << "No books available to borrow.\n";
            return;
        }

        string isbn;
        cout << "Enter ISBN of the book to borrow: ";
        cin >> isbn;

        for (auto it = inventory.begin(); it != inventory.end(); ++it) 
        {
            if (it->getISBN() == isbn) {
                borrowedBooks.push_back(*it);
                inventory.erase(it);
                cout << "Borrowed book: " << borrowedBooks.back().getTitle() << endl;
                return;
            }
        }
        cout << "Book with ISBN " << isbn << " not found in inventory.\n";
    }

    void returnBook() {
        if (borrowedBooks.empty()) {
            cout << "No borrowed books to return.\n";
            return;
        }

        string isbn;
        cout << "Enter ISBN of the book to return: ";
        cin >> isbn;

        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (it->getISBN() == isbn) {
                inventory.push_back(*it);
                borrowedBooks.erase(it);
                cout << "Returned book: " << inventory.back().getTitle() << endl;
                return;
            }
        }
        cout << "Book with ISBN " << isbn << " not found in borrowed books.\n";
    }

    void archiveBook() {
        if (inventory.empty()) {
            cout << "No books available to archive.\n";
            return;
        }

        string isbn;
        cout << "Enter ISBN of the book to archive: ";
        cin >> isbn;

        for (auto it = inventory.begin(); it != inventory.end(); ++it) {
            if (it->getISBN() == isbn) {
                archivedBooks.push_back(*it);
                inventory.erase(it);
                cout << "Archived book: " << archivedBooks.back().getTitle() << endl;
                return;
            }
        }
        cout << "Book with ISBN " << isbn << " not found in inventory.\n";
    }
    void displayAllBooks() const {
        cout << "\nInventory Books:\n";
        for (const auto& book : inventory) book.display();

        cout << "\nBorrowed Books:\n";
        for (const auto& book : borrowedBooks) book.display();

        cout << "\nArchived Books:\n";
        for (const auto& book : archivedBooks) book.display();
    }
    void saveData() {
        ofstream invFile("inventory.txt"), brwFile("borrowed.txt"), arcFile("archived.txt");

        if (!invFile || !brwFile || !arcFile) {
            cout << "Error opening file(s) for writing.\n";
            return;
        }
        for (const auto& book : inventory) invFile << book.serialize() << endl;
        for (const auto& book : borrowedBooks) brwFile << book.serialize() << endl;
        for (const auto& book : archivedBooks) arcFile << book.serialize() << endl;
        cout << "Data saved successfully.\n";
    }
    void loadData() {
        ifstream invFile("inventory.txt"), brwFile("borrowed.txt"), arcFile("archived.txt");
        string line;

        if (!invFile || !brwFile || !arcFile) {
            cout << "Error opening file(s) for reading.\n";
            return;
        }
        inventory.clear();
        borrowedBooks.clear();
        archivedBooks.clear();

        while (getline(invFile, line)) inventory.push_back(Book::deserialize(line));
        while (getline(brwFile, line)) borrowedBooks.push_back(Book::deserialize(line));
        while (getline(arcFile, line)) archivedBooks.push_back(Book::deserialize(line));

        cout << "Data loaded successfully.\n";
    }
};

int main() 
{
    Library library;
    int choice;
    while (true) {
        cout << "1. Add Book\n";
        cout << "2. Borrow Book\n";
        cout << "3. Return Book\n";
        cout << "4. Archive Book\n";
        cout << "5. Save Data\n";
        cout<<"6. Load Data\n";
        cout<<"7. Display Books\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) 
        {
            string title, author, isbn;
            cout << "Enter title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            cout << "Enter ISBN: ";
            cin >> isbn;
            library.addBook(Book(title, author, isbn));
            cout << "Book added successfully.\n";
        } 
        else if (choice == 2) 
        {
            library.borrowBook();
        } 
        else if (choice == 3) 
        {
            library.returnBook();
        } 
        else if (choice == 4) 
        {
            library.archiveBook();
        } 
        else if (choice == 5) {
            library.saveData();
            break;
        }
        else if(choice==6)
        {
            library.loadData();
            break;
        } 
        else if(choice==7)
        {
            library.displayAllBooks();
            break;
        }
        else if(choice==8)
        {
            cout<<"Exit!"<<endl;
            break;
        }
        else 
        {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}