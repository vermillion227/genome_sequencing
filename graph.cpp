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

void Edge::SetVisited() { visited_ = true; }

bool Edge::IsVisited() { return visited_; }

Node* Edge::GetToNode() { return to_node_.get(); }

Node* Edge::GetFromNode() { return from_node_.get(); }


// Node methods

Node::Node() {}

Node::Node(const string& data) : data_(data) {}

Node::~Node() {}

string Node::GetData() { return data_; }

void Node::SetData(const string& data) { data_ = data; }

void Node::IncFanOut() { fan_out++; }

void Node::IncFanIn() { fan_in++; }

void Node::IncVisitedNum() { visited_num++; }

int Node::GetVisitedNum() { return visited_num; }

int Node::GetFanOut() { return fan_out; }

int Node::GetFanIn() { return fan_in; }

void Node::InsertEdge(const shared_ptr<Node>& node) {
    shared_ptr<Node> aux(this);
    out_edges.push_back(new Edge(aux, node));
}  

vector<Edge*> Node::GetEdges() { return out_edges; }

//deBruijnGraph methods

deBruijnGraph::deBruijnGraph() { num_edges = 0; }

deBruijnGraph::~deBruijnGraph() {}

void deBruijnGraph::AddComponent(const string& data_1, const string& data_2) {
    auto n1 = nodes_map.find(data_1);
    auto n2 = nodes_map.find(data_2);
}

void deBruijnGraph::BalanceGraph() {

}

long deBruijnGraph::GetNumEdges() { return num_edges; }

Node* deBruijnGraph::GetFirstNode() {
    return nodes_map.begin()->second.get();
}   

}  // namespace graph
