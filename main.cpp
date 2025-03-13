#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Book {
private:
    string title;
    string author;
    string genre;
    double price;
    int numCopies;

public:
    Book(const string& t, const string& a, const string& g, double p, int n) 
        : title(t), author(a), genre(g), price(p), numCopies(n) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getGenre() const { return genre; }
    double getPrice() const { return price; }
    int getNumCopies() const { return numCopies; }
    void decrementCopies() { numCopies--; }
};

vector<Book> books;

// Function to load books from a CSV file
void LoadBooks() {
    ifstream file("books.csv");
    if (!file) {
        cerr << "Error opening the file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string title, author, genre;
        double price;
        int numCopies;
        if (getline(ss, title, ',') && getline(ss, author, ',') && getline(ss, genre, ',') &&
            ss >> price && ss.ignore() && ss >> numCopies) {
            books.push_back(Book(title, author, genre, price, numCopies));
        }
    }

    file.close();
}

// Function to save books to a CSV file
void SaveBooks() {
    ofstream file("books.csv");
    if (!file) {
        cerr << "Error opening the file." << endl;
        return;
    }

    for (const Book& book : books) {
        file << book.getTitle() << "," << book.getAuthor() << "," << book.getGenre() << "," << book.getPrice() << "," << book.getNumCopies() << "\n";
    }

    file.close();
}

void SearchByTitle(const string& title) {
    for (const Book& book : books) {
        if (book.getTitle() == title) {
            cout << "Title: " << book.getTitle() << endl<<", Author: " << book.getAuthor() << endl<<", Genre: " << book.getGenre() <<endl<< ", Price: " << book.getPrice() << endl<<", Copies: " << book.getNumCopies() << endl;
        }
    }
}

void SearchByAuthor(const string& author) {
    for (const Book& book : books) {
        if (book.getAuthor() == author) {
            cout << "Title: " << book.getTitle() << endl<<", Author: " << book.getAuthor() << endl<<", Genre: " << book.getGenre() <<endl<< ", Price: " << book.getPrice() << endl<<", Copies: " << book.getNumCopies() << endl;
        }
    }
}

void SearchByGenre(const string& genre) {
    for (const Book& book : books) {
        if (book.getGenre() == genre) {
            cout << "Title: " << book.getTitle() << endl<<", Author: " << book.getAuthor() << endl<<", Genre: " << book.getGenre() <<endl<< ", Price: " << book.getPrice() << endl<<", Copies: " << book.getNumCopies() << endl;
        }
    }
}

void BuyBook(const string& title) {
    for (Book& book : books) {
        if (book.getTitle() == title) {
            if (book.getNumCopies() > 0) {
                book.decrementCopies();
                cout << "You have successfully purchased " << title << ". Remaining copies: " << book.getNumCopies() << endl;
                SaveBooks();
            } else {
                cout << "Sorry, this book is out of stock." << endl;
            }
            return;
        }
    }
    cout << "Book not found." << endl;
}

int main() {
    LoadBooks();

    while (true) {
        cout << "\nBookshop Management System" << endl;
        cout << "1. Search by Title" << endl;
        cout << "2. Search by Author" << endl;
        cout << "3. Search by Genre" << endl;
        cout << "4. Buy a Book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
    
        switch (choice) {
            case 1: {
                cout << "Enter the title to search: ";
                string title;
                cin.ignore();
                getline(cin, title);
                SearchByTitle(title);
                break;
            }
            case 2: {
                cout << "Enter the author to search: ";
                string author;
                cin.ignore();
                getline(cin, author);
                SearchByAuthor(author);
                break;
            }
            case 3: {
                cout << "Enter the genre to search: ";
                string genre;
                cin.ignore();
                getline(cin, genre);
                SearchByGenre(genre);
                break;
            }
            case 4: {
                cout << "Enter the title of the book you want to buy: ";
                string title;
                cin.ignore();
                getline(cin, title);
                BuyBook(title);
                break;
            }
            case 5:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
