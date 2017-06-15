#include <string>
#include <utility>
#include <vector>
#include <map>

#include "graph.h"

using namespace std;

// Node methods

Node::Node() {}

Node::Node(const string& data, const long id) : data_(data), id_(id) {}

Node::~Node() {}

string Node::getData() { return data_; }

void Node::setData(const string& data) { data_ = data; }

long Node::getId() { return id_; }

void Node::setId(const long id) { id_ = id; }

//deBruijnGraph methods

deBruijnGraph::deBruijnGraph() { num_nodes = 0; }

deBruijnGraph::~deBruijnGraph() {}

void deBruijnGraph::AddComponent(const string& key_1, const string& key_2) {
    if (nodes_.find(key_1) == nodes_.end()) {
        Node node1(key_1, num_nodes);
        num_nodes++;
        nodes_[key_1] = node1;
    }

    if (nodes_.find(key_2) == nodes_.end()) {
        Node node2(key_2, num_nodes);
        num_nodes++;
        nodes_[key_2] = node2;
    }

    adjacency_list[key_1].push_back(key_2);
}

