#include <string>
#include <utility>
#include <vector>
#include <map>

#include "graph.h"

using namespace std;

namespace graph {

// Edge methods

// Node methods

Node::Node() {}

Node::Node(const string& data, const long id) : data_(data), id_(id) {}

Node::~Node() {}

string Node::GetData() { return data_; }

void Node::SetData(const string& data) { data_ = data; }

long Node::GetId() { return id_; }

void Node::SetId(const long id) { id_ = id; }

void Node::IncFanOut() { fan_out++; }

void Node::IncVisitedNum() { visited_num++; }

int Node::GetVisitedNum() { return visited_num; }

int Node::GetFanOut() { return fan_out; }

void Node::InsertEdge(const shared_ptr<Node>& node) {
    out_edges.push_back(unique_ptr<Edge>( new Edge(this, node) ));
}  

vetcor<unique_ptr<Edge> > Node::GetEdges() { return out_edges; }

//deBruijnGraph methods

deBruijnGraph::deBruijnGraph() { num_nodes = 0; }

deBruijnGraph::~deBruijnGraph() {}

void deBruijnGraph::AddComponent(const string& data_1, const string& data_2) {
    auto node1 = nodes_map.find(data_1);
    auto node2 = nodes_map.find(data_2);

    if (node1 == nodes_map.end()) {
        AddNode(data_1);
    }

    if (node2 == nodes_map.end()) {
        AddNode(data_2);
    }

    nodes_[node1]->InsertEdge(nodes_[node2]);
}

}  // namespace graph
