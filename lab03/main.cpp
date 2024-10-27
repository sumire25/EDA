#include <functional>
#include <fstream>
#include <string>
#include "FibonacciHeap.h"
using namespace std;

template <typename T>
void generateGraphviz(Node<T>* root, const std::string& filename) {
    std::ofstream dotFile(filename);
    dotFile << "digraph FibonacciHeap {\n";
    dotFile << "    node [shape=record];\n";

    // Find the minimum node
    Node<T>* minNode = root;
    if (root) {
        Node<T>* current = root->right;
        while (current != root) {
            if (current->key < minNode->key) {
                minNode = current;
            }
            current = current->right;
        }
    }

    // Helper lambda to recursively add nodes and edges to the DOT file
    std::function<void(Node<T>*, const std::string&)> addNodes = [&](Node<T>* node, const std::string& parentName) {
        if (!node) return;
        Node<T>* start = node;

        do {
            // Create a unique name for each node based on its address
            std::string nodeName = "node" + std::to_string(reinterpret_cast<uintptr_t>(node));
            dotFile << "    \"" << nodeName << "\" [label=\"Key: " << node->key << "\\nValue: " << node->value << "\"";

            // Highlight the minimum node and marked nodes
            if (node == minNode) {
                dotFile << ", style=filled, fillcolor=yellow";
            } else if (node->mark) {
                dotFile << ", style=filled, fillcolor=red";
            }

            dotFile << "];\n";

            // Connect the node to its parent if applicable
            if (!parentName.empty()) {
                dotFile << "    \"" << parentName << "\" -> \"" << nodeName << "\";\n";
            }

            // Recursively add children of this node
            if (node->child) {
                addNodes(node->child, nodeName);
            }

            // Move to the next sibling
            node = node->right;
        } while (node != start); // Stop when we loop back to the starting node
    };

    // Rank the root nodes together at the same level
    if (root) {
        dotFile << "    {rank=same;\n";
        Node<T>* start = root;
        do {
            std::string rootName = "node" + std::to_string(reinterpret_cast<uintptr_t>(start));
            dotFile << "        \"" << rootName << "\";\n";
            start = start->right;
        } while (start != root);
        dotFile << "    }\n";

        // Start adding nodes from the root list
        addNodes(root, ""); // Pass an empty string since root nodes don't have parents
    }

    dotFile << "}\n";
    dotFile.close();

    // Use Graphviz to generate a PNG file
    system(("dot -Tpng " + filename + " -o heap.png").c_str());
}

int main() {
    // Create a Fibonacci heap instance
    FibonacciHeap<string> heap;

    // Insert some nodes into the heap
    Node<string>* node1 = new Node<string>(10, "A");
    Node<string>* node2 = new Node<string>(20, "B");
    Node<string>* node3 = new Node<string>(5, "C");
    Node<string>* node4 = new Node<string>(30, "D");
    Node<string>* node5 = new Node<string>(8, "E");
    Node<string>* node6 = new Node<string>(3, "F");
    Node<string>* node7 = new Node<string>(15, "G");
    Node<string>* node8 = new Node<string>(25, "H");
    Node<string>* node9 = new Node<string>(7, "I");
    Node<string>* node10 = new Node<string>(17, "J");
    Node<string>* node11 = new Node<string>(35, "K");
    Node<string>* node12 = new Node<string>(40, "L");
    Node<string>* node13 = new Node<string>(50, "M");
    Node<string>* node14 = new Node<string>(60, "N");
    Node<string>* node15 = new Node<string>(70, "O");
    Node<string>* node16 = new Node<string>(80, "P");
    Node<string>* node17 = new Node<string>(90, "Q");
    Node<string>* node18 = new Node<string>(100, "R");
    Node<string>* node19 = new Node<string>(110, "S");
    Node<string>* node20 = new Node<string>(120, "T");


    heap.insert(node1);
    heap.insert(node2);
    heap.insert(node3);
    heap.insert(node4);
    heap.insert(node5);
    heap.insert(node6);
    heap.insert(node7);
    heap.insert(node8);
    heap.insert(node9);
    heap.insert(node10);
    heap.insert(node11);
    heap.insert(node12);
    heap.insert(node13);
    heap.insert(node14);
    heap.insert(node15);
    heap.insert(node16);
    heap.insert(node17);
    heap.insert(node18);
    heap.insert(node19);
    heap.insert(node20);


    // Print the initial heap
    cout << "Initial Heap:" << endl;
    heap.printHeap();
    generateGraphviz(heap.findMin(), "initial_heap.dot");

    // Extract the minimum node and print the heap
    cout << "\nExtracting the minimum node..." << endl;
    Node<string>* minNode = heap.extractMin();
    cout << "\nHeap after extracting minimum:" << endl;
    cin>>minNode->key;
    generateGraphviz(heap.findMin(), "initial_heap.dot");
    heap.printHeap();

    // Decrease the key of node2 and print the heap
    cout << "\nDecreasing key of node with value 'O' from 70 to 2..." << endl;
    heap.decreaseKey(node15, 2);
    cin>>minNode->key;
    generateGraphviz(heap.findMin(), "initial_heap.dot");
    heap.printHeap();

    // Increase the key of node2 back to 15 and print the heap
    cout << "\nIncreasing key of node with value 'P' from 80 to 105..." << endl;
    heap.increaseKey(node16, 150);
    cin>>minNode->key;
    generateGraphviz(heap.findMin(), "initial_heap.dot");
    heap.printHeap();

    // Delete node4 (value "D") from the heap
    cout << "\nDeleting node with value 'D' from the heap..." << endl;
    heap.deleteNode(node4);
    cin>>minNode->key;
    generateGraphviz(heap.findMin(), "initial_heap.dot");
    heap.printHeap();

    // Clean up allocated nodes
    delete node1;
    delete node2;
    delete node4;
    delete node5;

    return 0;
}
