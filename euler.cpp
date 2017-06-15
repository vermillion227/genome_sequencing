 #include "euler.h"

namespace euler {

int FindNodeInCycle(const Node* node, const vector<Edge*>& cycle) {
    for (int i = 0; i < cycle.length(); i++) {
        if (cycle[i].GetFromNode() == node) {
            return i;
        }
    } 

    return -1;
}

void WalkCurrentCycle(const Node* node, vector<Edge*>* cycle) {
    if (!cycle->size()) {
        return;
    }

    vector<Edge> aux_cycle = *cycle;
    cycle.clear();
    int found = FindNodeInCycle(node, aux_cycle);
    for (int i = found; i < aux_cycle.length(); i++) {
        cycle.push_back(aux_cycle[i]);
    }

    for (int i = 0; i < found; i++) {
        cycle.push_back(aux_cycle[i]);
    }
}

Edge* GetNextEdge(const Node* node) {
    for (auto e : out_edges) {
        if (!e->IsVisited()) {
            e->SetVisited();
            return e.get();
        }
    }
}

void CreateCycle(Node* start_node, vector<Edge*>* curr_cycle) {
    Node* node = start_node;
    WalkCurrentCycle(node, curr_cycle);
    
    Edge* edge = GetNextEdge(node);

    while (edge != nullptr) {
        curr_cycle->push_back(edge);
        node = edge->GetToNode();
        edge = GetNextEdge(node);
    }
}

Node* GetNonFinishedNode(const vector<Edge*>& cycle) {
    for (auto e : cycle) {
        if (e->GetFromNode()->GetVisitedNum() != e->GetFromNode()->GetFanOut()) {
            return e->GetFromNode();
        }
    }
}

vector<Edge*> FindEulerianCycle(const deBruijnGraph& graph) {
   vector<Edge*> cycle;

   Node* current_node = graph.getFirstNode();
   CreateCycle(current_node, &cycle);

   while(graph.GetNumEdges() != cycle.size()) {
        current_node = GetNonFinishedNode(cycle);
        CreateCycle(current_node, &cycle);
   }
    
   return cycle;
}

}  // namespace euler
