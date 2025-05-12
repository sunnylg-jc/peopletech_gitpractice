#include <iostream>
#include <list>
using namespace std;

class LinkedList {
private:
    list<int> myList;

public:
    // Function to insert an element at the front of the list
    void insertFront(int value) {
        myList.push_front(value);
    }

    // Function to insert an element at the end of the list
    void insertEnd(int value) {
        myList.push_back(value);
    }

    // Function to insert an element at a specified position
    void insertAtPosition(int value, int pos) {
        if (pos < 1 || pos > myList.size() + 1) {
            cout << "Invalid position!" << endl;
            return;
        }

        auto it = myList.begin();
        advance(it, pos - 1); // Move iterator to the specified position
        myList.insert(it, value);
    }

    // Function to delete an element from the front of the list
    void deleteFront() {
        if (!myList.empty()) {
            myList.pop_front();
        } else {
            cout << "List is empty!" << endl;
        }
    }

    // Function to delete an element from the end of the list
    void deleteEnd() {
        if (!myList.empty()) {
            myList.pop_back();
        } else {
            cout << "List is empty!" << endl;
        }
    }

    // Function to delete an element at a specified position
    void deleteAtPosition(int pos) {
        if (pos < 1 || pos > myList.size()) {
            cout << "Invalid position!" << endl;
            return;
        }

        auto it = myList.begin();
        advance(it, pos - 1); // Move iterator to the specified position
        myList.erase(it);
    }

    // Function to display the list
    void display() {
        if (myList.empty()) {
            cout << "List is empty!" << endl;
            return;
        }

        for (int value : myList) {
            cout << value << " ";
        }
        cout << endl;
    }
};

int main() {
    LinkedList list;
    int n, value, pos;
    int choice;

    cout << "Enter the number of elements to insert initially: ";
    cin >> n;

    // Insert initial elements into the list
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        list.insertEnd(value);
    }

    // Main menu for operations
    do {
        cout << "\nChoose an operation:\n";
        cout << "1. Insert at front\n";
        cout << "2. Insert at end\n";
        cout << "3. Insert at position\n";
        cout << "4. Delete from front\n";
        cout << "5. Delete from end\n";
        cout << "6. Delete from position\n";
        cout << "7. Display list\n";
        cout << "8. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert at front: ";
                cin >> value;
                list.insertFront(value);
                break;
            case 2:
                cout << "Enter value to insert at end: ";
                cin >> value;
                list.insertEnd(value);
                break;
            case 3:
                cout << "Enter value to insert: ";
                cin >> value;
                cout << "Enter position to insert at: ";
                cin >> pos;
                list.insertAtPosition(value, pos);
                break;
            case 4:
                list.deleteFront();
                break;
            case 5:
                list.deleteEnd();
                break;
            case 6:
                cout << "Enter position to delete from: ";
                cin >> pos;
                list.deleteAtPosition(pos);
                break;
            case 7:
                list.display();
                break;
            case 8:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 8);

    return 0;
}
