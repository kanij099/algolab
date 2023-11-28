#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    bool checkedOut;
};

class Library {
private:
    vector<Book> books;

public:
    void addBook(const Book &book) {
        books.push_back(book);
        saveData();
        cout << "Book added successfully." << endl;
    }

    void removeBook(const string &ISBN) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->ISBN == ISBN) {
                books.erase(it);
                saveData();
                cout << "Book removed successfully." << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void displayBooks() {
        cout << "------------------------" << endl;
        cout << setw(20) << "Title" << setw(20) << "Author" << setw(15) << "ISBN" << setw(15) << "Status" << endl;
        cout << "------------------------" << endl;
        for (const auto &book : books) {
            cout << setw(20) << book.title << setw(20) << book.author << setw(15) << book.ISBN << setw(15)
                 << (book.checkedOut ? "Checked Out" : "Available") << endl;
        }
        cout << "------------------------" << endl;
    }

    void loadData() {
        ifstream file("library_data.txt");
        if (file.is_open()) {
            books.clear();
            Book book;
            while (file >> book.title >> book.author >> book.ISBN >> book.checkedOut) {
                books.push_back(book);
            }
            file.close();
        }
    }

    void saveData() {
        ofstream file("library_data.txt");
        for (const auto &book : books) {
            file << book.title << " " << book.author << " " << book.ISBN << " " << book.checkedOut << endl;
        }
        file.close();
    }
};

int main() {
    Library library;
    library.loadData();

    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Display Books\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Book newBook;
                cout << "Enter Title: ";
                cin.ignore();
                getline(cin, newBook.title);
                cout << "Enter Author: ";
                getline(cin, newBook.author);
                cout << "Enter ISBN: ";
                cin >> newBook.ISBN;
                newBook.checkedOut = false;

                library.addBook(newBook);
                break;
            }
            case 2: {
                string ISBN;
                cout << "Enter ISBN of the book to remove: ";
                cin >> ISBN;
                library.removeBook(ISBN);
                break;
            }
            case 3:
                cout << "\nList of Books in the Library:\n";
                library.displayBooks();
                break;
            case 0:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}