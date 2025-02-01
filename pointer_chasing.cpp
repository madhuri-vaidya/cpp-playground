#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

struct Node {
    int value;
    Node* next;
    
    Node() : value(0), next(nullptr) {};
    Node(int value, Node* next) : value(value), next(next) {};
};

// Do some calculation for NUM_NODES required for specified buffer size
int get_num_nodes() {
    return 10;
}

int main() {
    int NUM_NODES = get_num_nodes(), lines = 15;
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

    return 0;
}