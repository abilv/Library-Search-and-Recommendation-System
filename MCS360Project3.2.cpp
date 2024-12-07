#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    string data;          
    vector<Node*> children; // Children nodes

    Node(string val) : data(val) {} 
};

class BookTree {
private:
    Node* root; 

public:
    BookTree() {
        root = new Node("Root"); 
    }
    void Bookinsertion(string title, string author, string genre) {
        cout << "Adding book: \"" << title << "\", \"" << author << "\", \"" << genre << "\"" << endl;
        Node* titleNode = findOrCreateChild(root, title);
        Node* authorNode = findOrCreateChild(titleNode, author);
        findOrCreateChild(authorNode, genre);
        cout << "Book added successfully." << endl;
    }

    void Titlesearching(string title) { //Searches for a book by its title.
        title = removeSurroundingQuotes(title);
        cout << "Searching for: Title \"" << title << "\"" << endl;
        for (int i = 0; i < root->children.size(); i++) {
            Node* titleNode = root->children[i];
            if (titleNode->data == title) {
                if (!titleNode->children.empty()) {
                    string author = titleNode->children[0]->data;
                    cout << "Found: \"" << title << "\" by " << author << endl;
                }
                else {
                    cout << "Found: \"" << title << "\", but author data is missing." << endl;
                }
                return;
            }
        }
        cout << "Title \"" << title << "\" not found." << endl;
    }

    void SearchcingWithAuthor(string author) { //Searches for all books by a given author
        author = removeSurroundingQuotes(author);
        cout << "Searching for: Author \"" << author << "\"" << endl;
        for (int i = 0; i < root->children.size(); i++) {
            Node* titleNode = root->children[i];
            for (int j = 0; j < titleNode->children.size(); j++) {
                Node* authorNode = titleNode->children[j];
                if (authorNode->data == author) {
                    cout << "Found: \"" << titleNode->data << "\" by " << author << endl;
                    return;
                }
            }
        }
        cout << "Author \"" << author << "\" not found." << endl;
    }

    void recommendationOfGenre(string genre) { // Lists books of a given genre
        genre = removeSurroundingQuotes(genre); 
        cout << "Recommending books in the genre \"" << genre << "\":" << endl;
        bool found = false;
        for (int i = 0; i < root->children.size(); i++) {
            Node* titleNode = root->children[i];
            for (int j = 0; j < titleNode->children.size(); j++) {
                Node* authorNode = titleNode->children[j];
                for (int k = 0; k < authorNode->children.size(); k++) {
                    Node* genreNode = authorNode->children[k];
                    if (genreNode->data == genre) {
                        if (!found) {
                            cout << "Recommendations:" << endl;
                            found = true;
                        }
                        cout << "- \"" << titleNode->data << "\" by " << authorNode->data << endl;
                    }
                }
            }
        }
        if (!found) {
            cout << "No recommendations found in this genre." << endl;
        }
    }

    void displayAllBooks() { //Displays all books in the library
        cout << "Displaying all books:" << endl;
        for (int i = 0; i < root->children.size(); i++) {
            Node* titleNode = root->children[i];
            if (!titleNode->children.empty()) {
                string author = titleNode->children[0]->data;
                string genre = titleNode->children[0]->children.empty() ? "Unknown" : titleNode->children[0]->children[0]->data;
                cout << "- \"" << titleNode->data << "\" by " << author << " (Genre: " << genre << ")" << endl;
            }
        }
    }

private:
    Node* findOrCreateChild(Node* parent, string data) { //Finds or creates a child node for a given parent.
        for (int i = 0; i < parent->children.size(); i++) {
            if (parent->children[i]->data == data) {
                return parent->children[i];
            }
        }
        Node* newChild = new Node(data);
        parent->children.push_back(newChild);
        return newChild;
    }

    string removeSurroundingQuotes(const string& str) { //Removes extra quotes from input strings
        if (str.size() >= 2 && str.front() == '"' && str.back() == '"') {
            return str.substr(1, str.size() - 2);
        }
        return str;
    }
};

int main() {
    BookTree library;
    string userinput;
    cout << "Welcome to the Library Search and Recommendation System" << endl;

    while (true) {
        getline(cin, userinput);

        if (userinput == "Exit") {
            break;
        }
        else if (userinput.find("Add Book:") == 0) {
            string data = userinput.substr(10);
            size_t firstQuote = data.find('"');
            size_t secondQuote = data.find('"', firstQuote + 1);
            size_t thirdQuote = data.find('"', secondQuote + 1);
            size_t fourthQuote = data.find('"', thirdQuote + 1);
            size_t fifthQuote = data.find('"', fourthQuote + 1);
            size_t sixthQuote = data.find('"', fifthQuote + 1);

            string title = data.substr(firstQuote + 1, secondQuote - firstQuote - 1);
            string author = data.substr(thirdQuote + 1, fourthQuote - thirdQuote - 1);
            string genre = data.substr(fifthQuote + 1, sixthQuote - fifthQuote - 1);

            library.Bookinsertion(title, author, genre);

        }
        else if (userinput.find("Search by Title:") == 0) {
            string title = userinput.substr(17);
            library.Titlesearching(title);

        }
        else if (userinput.find("Search by Author:") == 0) {
            string author = userinput.substr(18);
            library.SearchcingWithAuthor(author);

        }
        else if (userinput.find("Recommend Books by Genre:") == 0) {
            string genre = userinput.substr(26);
            library.recommendationOfGenre(genre);

        }
        else if (userinput == "Display All Books") {
            library.displayAllBooks();
        }
    }

    return 0;
}
