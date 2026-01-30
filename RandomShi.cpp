#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

class DLL {
private:
    Node* head;

public:
    DLL() { head = nullptr; }

    void insertAtBeginning(int val) {
        Node* newNode = new Node(val);
        if (head != nullptr) {
            head->prev = newNode;
            newNode->next = head;
        }
        head = newNode;
    }

    void insertAtEnd(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }

    void insertAtPosition(int val, int pos) {
        if (pos == 1) {
            insertAtBeginning(val);
            return;
        } else if( pos <= 0 ) {
            cout << "Invalid position\n";
            return;
        }
        Node* newNode = new Node(val);
        Node* temp = head;
        for (int i = 1; temp != nullptr && i < pos - 1; i++) temp = temp->next;

        if (temp == nullptr) {
            cout << "Position out of bounds\n";
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next != nullptr) temp->next->prev = newNode;
        temp->next = newNode;
    }

    void deleteFromBeginning() {
        if (head == nullptr) return;
        Node* temp = head;
        head = head->next;
        if (head != nullptr) head->prev = nullptr;
        delete temp;
    }

    void deleteFromEnd() {
        if (head == nullptr) return;
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->prev->next = nullptr;
        delete temp;
    }

    void deleteFromPosition(int pos) {
        if (head == nullptr) return;
        if (pos == 1) {
            deleteFromBeginning();
            return;
        }
        Node* temp = head;
        for (int i = 1; temp != nullptr && i < pos; i++) temp = temp->next;

        if (temp == nullptr) return;
        if (temp->next != nullptr) temp->next->prev = temp->prev;
        if (temp->prev != nullptr) temp->prev->next = temp->next;
        delete temp;
    }

    bool search(int key) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == key) return true;
            temp = temp->next;
        }
        return false;
    }

    void displayForward() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    void displayReverse() {
        if (head == nullptr) return;
        Node* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    DLL list;

    list.insertAtBeginning(10);
    list.insertAtEnd(30);
    list.insertAtPosition(20, 2);
    
    list.displayForward();
    list.displayReverse();

    if (list.search(20)) {
        cout << "Found" << endl;
    }

    list.deleteFromPosition(2);
    list.deleteFromBeginning();
    list.deleteFromEnd();

    list.displayForward();

    return 0;
}