#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    int value;
    Node* next;
    
    Node() : value(0), next(nullptr) {};
    Node(int value, Node* next) : value(value), next(next) {};
};

// Do some calculation for NUM_NODES required for specified buffer size
int getNumNodes() {
    return 10;
}


// Do some calculation for array size required for the specified buffer
int getArraySize() {
    return 10;
}


void pointerChaseLinkedList(int lines) {
    int NUM_NODES = getNumNodes();
    vector<Node*> nodes(NUM_NODES);

    // Initialise vector
    // Move this section to separate function
    for(int i = 0; i < NUM_NODES; i++) {
        nodes[i] = new Node(i, nullptr);
        cout << "Initialising Node with value " << nodes[i]->value << endl;

        if(i > 0) { nodes[i - 1]->next = nodes[i]; }
        if(i == NUM_NODES - 1) { nodes[i]->next = nodes[0]; }
    }

    // Run pointer chasing for specified time / lines
    Node* current = nodes[0];
    for(int i = 0; i < lines; i++) {
        cout << "i is " << i << " and value at node is " << current->value << endl;
        current = current->next;
    }
}


void pointerChaseArray(int lines) {
    int array_size = getArraySize();
    vector<int*> arr{10, nullptr};
    int* ptr;

    // Initialise the vector. Move this to a separate function in future
    for(int i = 0; i < array_size - 1; i++) { arr[i] = arr[i + 1]; }
    arr[array_size - 1] = arr[0];

    // Run pointer chasing for specified lines / time
    for(int i = 0; i < lines; i++) { ptr = arr[i]; }
}


int main(int argc, char *argv[]) {
    int buffer;
    string type;

    if(argc == 3) {
        type = argv[1];
        buffer = stoi(argv[2]);
    }

    else {
        cout << "Incorrect arguments. Please check again..." << endl;
        cout << "Usage: ./pointer_chasing <linked_list / array> <buffer_size>" << endl;
        throw exception();
    }

    cout << "Input type is " << type << " with buffer " << buffer << endl;

    if(type == "linked_list") { pointerChaseLinkedList(buffer); }
    else if(type == "array") { pointerChaseArray(buffer); }

    return 0;
}