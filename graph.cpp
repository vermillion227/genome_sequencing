#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>

#include "graph.h"

using namespace std;

namespace graph {

// Edge methods

Edge::Edge() {}

Edge::Edge(const shared_ptr<Node> from_node, const shared_ptr<Node>& to_node) {
    from_node_ = from_node;
    to_node_ = to_node;
}

Edge::~Edge() {}

void Edge::SetVisited() { 
    visited_ = true;
}

bool Edge::IsVisited() { 
    return visited_;
}

Node* Edge::GetToNode() {
    return to_node_.get();
}

Node* Edge::GetFromNode() { 
    return from_node_.get(); 
}


// Node methods

Node::Node() {}

Node::Node(const string& data) : data_(data), fan_in(0), fan_out(0) {}

Node::~Node() {}

string Node::GetData() { 
    return data_; 
}

void Node::SetData(const string& data) { 
    data_ = data; 
}

void Node::IncFanOut() { 
    fan_out++;
}

void Node::IncFanIn() { 
    fan_in++; 
}

void Node::IncVisitedNum() {
    visited_num++;
}

int Node::GetVisitedNum() { 
    return visited_num;
}

int Node::GetFanOut() { 
    return fan_out;
}

int Node::GetFanIn() {
    return fan_in;
}

void Node::InsertEdge(const shared_ptr<Node>& node) {
    shared_ptr<Node> aux(this);
    out_edges.push_back(new Edge(aux, node));
    IncFanOut();
    node->IncFanIn();
    cout << "[InsertEdge] Inserted edge " << GetData() << " -> " << node->GetData() << endl;
}  

vector<Edge*> Node::GetEdges() {
    return out_edges;
}


//deBruijnGraph methods

deBruijnGraph::deBruijnGraph() { 
    num_edges = 0;
}

deBruijnGraph::~deBruijnGraph() {}

void deBruijnGraph::AddComponent(const string& data_1, const string& data_2) {

    if (nodes_map.find(data_1) == nodes_map.end()) {
        AddNode(data_1);
    }

    if (nodes_map.find(data_2) == nodes_map.end()) {
        AddNode(data_2);
    }

    auto n1 = nodes_map.find(data_1)->second;
    auto n2 = nodes_map.find(data_2)->second;
    n1->InsertEdge(n2);
    num_edges++;
}

void deBruijnGraph::BalanceGraph() {
    cout << "[BalanceGraph] Enter BalanceGraph\n";
    shared_ptr<Node> aux;
    for (auto it : nodes_map) {
        if (it.second->GetFanIn() < it.second->GetFanOut()) {
            aux = it.second;
            break;
        }
    }
    for (auto it : nodes_map) {
        if (it.second->GetFanIn() > it.second->GetFanOut()) {
            it.second->InsertEdge(aux);
            from_extra_edge = it.second->GetData();
            to_extra_edge = aux->GetData();
        }
    }

    num_edges++;
    cout << "[BalanceGraph] GraphBalanced\n";
}

void deBruijnGraph::AddNode(const string& data) {
    Node* new_node = new Node(data);

    nodes_map.insert(pair<string, shared_ptr<Node> >(data, shared_ptr<Node>(new_node)));
    cout << "[AddNode] Added node " << data << endl;
}

long deBruijnGraph::GetNumEdges() { 
    return num_edges;
}

Node* deBruijnGraph::GetFirstNode() {
    return nodes_map.begin()->second.get();
}   

string deBruijnGraph::GetFromExtraEdge() {
    return from_extra_edge;
}

string deBruijnGraph::GetToExtraEdge() {
    return to_extra_edge;
}

}  // namespace graph
