// COMSC-210 | Midterm 2 | Ibrahim Bello
// This program creates a driver for a DLL
// to simulate a line at a coffee shop.


#include <iostream>
#include <string>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int MINS = 20;
const string names[99] = {
    "Adam", "Alex", "Andy", "Anne", "Aria", "Beau", "Beth",
    "Bill", "Brad", "Cara", "Chad", "Cole", "Dana", "Dave",
    "Dean", "Drew", "Elle", "Emma", "Eric", "Erik", "Evan",
    "Faye", "Finn", "Gabe", "Gary", "Gina", "Greg", "Gwen",
    "Hank", "Hope", "Iris", "Ivan", "Jack", "Jade", "Jake",
    "Jane", "Jean", "Jett", "Jill", "Joan", "Joel", "John",
    "Judy", "June", "Kate", "Katy", "Kirk", "Kyle", "Lana",
    "Lane", "Leah", "Lena", "Liam", "Lily", "Lisa", "Lucy",
    "Luna", "Lyle", "Lynn", "Mark", "Mary", "Matt", "Maya",
    "Mike", "Milo", "Mina", "Neal", "Neil", "Nell", "Nina",
    "Noah", "Noel", "Nora", "Omar", "Otis", "Owen", "Paul",
    "Pete", "Reed", "Rene", "Rita", "Ross", "Ruby", "Ryan",
    "Sage", "Sara", "Seth", "Tara", "Tess", "Tina", "Toby",
    "Tony", "Troy", "Vera", "Wade", "Will", "Yara", "Zane",
    "Zara"
};


class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

// Function Prototypes for each coffee line operation:
// 1. Adding a person
void personJoinsLine(DoublyLinkedList list);
// 2 Customer is served
void personIsServed(DoublyLinkedList list);
// 3. Any customer leaves
void anyoneLeaves(DoublyLinkedList list);
// 4. Last customer leaves
void lastPersonLeaves(DoublyLinkedList list);
// 5. VIP skips line
void vipSkipsLine(DoublyLinkedList list);

int main() {
    srand(time(0));
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning
    // Algorithm:
    // Create empty DLL to represent the queue
    DoublyLinkedList theLine;
    // For loop (runs 20 times, one for each minute)
    for (int i = 1; i >= 20; i++) {
        // Print out "Store opens"
        cout << "Store opens: " << endl;
        // If i = 0 (first minute): for loop to add 5 random names (use function)
        // Else:
            // print out "Time step #i"
            cout << "Time step #" << i << ": " << endl;
            // Run 5 functions, one for each possible outcome
            // Each function recieves the DLL as its argument?
            // Each function runs the probability,  does the action if needed,
            // and puts out the necessary output
            // Once all 5 functions run, output out the line
    }

    
    return 0;
}

// Functions for each coffee line operation:
// 1. Adding a person
void personJoinsLine(DoublyLinkedList list) {
    // Algorithm:
    // Get random name from list
    string name = names[rand() % ];
    // create new node with that name
    // use list.push_back to add that name
    // output "name" joined the line
}
// 2 Customer is served
void personIsServed(DoublyLinkedList list) {

}
// 3. Any customer leaves
void anyoneLeaves(DoublyLinkedList list) {

}
// 4. Last customer leaves
void lastPersonLeaves(DoublyLinkedList list) { 

}
// 5. VIP skips line
void vipSkipsLine(DoublyLinkedList list) { 

}