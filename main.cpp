#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// A Structure that hold a contact details Named as (Contact)
struct Contact {
    string name;
    string phone;
    string email;
};

//  A Class for managing the contact book Named as(ContactBook)
class ContactBook {
private:
    vector<Contact> contacts; // Vector to hold contacts
    const string fileName = "contacts.txt"; // File to store contacts

    // Load the contacts from file
    void loadContacts() {
        ifstream file(fileName);
        if (file.is_open()) {
            Contact contact;
            while (getline(file, contact.name) && getline(file, contact.phone) && getline(file, contact.email)) {
                contacts.push_back(contact);
            }
            file.close();
        }
    }

    // Save the contacts to file
    void saveContacts() {
        ofstream file(fileName);
        if (file.is_open()) {
            for (const auto &contact : contacts) {
                file << contact.name << endl
                     << contact.phone << endl
                     << contact.email << endl;
            }
            file.close();
        }
    }

public:
    ContactBook() {
        loadContacts(); // Load contacts when the object is created
    }

    ~ContactBook() {
        saveContacts(); // Save contacts when the object is destroyed
    }

    // This is a function to Add a new contact
    void addContact() {
        Contact contact;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, contact.name);
        cout << "Enter phone: ";
        getline(cin, contact.phone);
        cout << "Enter email: ";
        getline(cin, contact.email);

        contacts.push_back(contact);
        cout << "Contact added successfully!" << endl;
    }

    // This is a function to Display all contacts
    void displayContacts() const {
        if (contacts.empty()) {
            cout << "No contacts found!" << endl;
            return;
        }
        for (size_t i = 0; i < contacts.size(); ++i) {
            cout << "Contact " << i + 1 << ":" << endl;
            cout << "Name: " << contacts[i].name << endl;
            cout << "Phone: " << contacts[i].phone << endl;
            cout << "Email: " << contacts[i].email << endl;
            cout << "------------------------" << endl;
        }
    }

    // This is a function to Search for a contact by name
    void searchContact() const {
        string name;
        cout<<"Enter the name to search: ";
        cin.ignore();
        getline(cin,name);
        bool found = false;
        for (const auto& contact : contacts) {
            if (contact.name == name) {
                cout << "Contact Found:" << endl;
                cout << "Name: " << contact.name << endl;
                cout << "Phone: " << contact.phone << endl;
                cout << "Email: " << contact.email << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Contact not found." << endl;
        }
    }

    // This is a function to Update a contact by name (updates name and email, preserves phone)
    void updateContact() {
        string nameToUpdate;
        cout << "Enter name of the contact to update: ";
        cin.ignore();
        getline(cin, nameToUpdate);

        bool found = false;
        for (auto &contact : contacts) {
            if (contact.name == nameToUpdate) {
                string newName, newEmail;
                cout << "Updating contact details for: " << contact.name << endl;
                cout << "Phone: " << contact.phone << " (This will remain unchanged)" << endl;

                cout << "Enter new name: ";
                getline(cin, newName);

                cout << "Enter new email: ";
                getline(cin, newEmail);

                contact.name = newName;
                contact.email = newEmail;

                cout << "Contact name and email updated successfully! Phone number remains the same." << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Contact not found!" << endl;
        }
    }
    // This is a function to Delete a contact by name
    void deleteContact() {
        string name;
        cout << "Enter name of the contact to delete: ";
        cin.ignore();
        getline(cin, name);

        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it->name == name) {
                contacts.erase(it);
                cout << "Contact deleted successfully!" << endl;
                return;
            }
        }

        cout << "Contact not found!" << endl;
    }
};

// Main function
int main() {
    ContactBook contactBook;
    int choice;

    do {
        cout << "\n Welcome to Contact Book:" << endl;
        cout << "\nContact Book Menu:" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Display Contacts" << endl;
        cout << "3. Search Contact" << endl;
        cout << "4. Update Contact" << endl;
        cout << "5. Delete Contact" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
// A switch case to give a choice what the person wants
        switch (choice) {
            case 1:
                contactBook.addContact();
                break;
            case 2:
                contactBook.displayContacts();
                break;
            case 3:
                contactBook.searchContact();
                break;
            case 4:
                contactBook.updateContact();
                break;
            case 5:
                contactBook.deleteContact();
                break;
            case 6:
                cout << "Exiting Contact Book. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
