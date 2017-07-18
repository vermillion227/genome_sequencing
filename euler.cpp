#include <iostream>

#include "euler.h"

namespace euler {

/*
 *  Function that finds the index of the edge in the cycle that starts
 *  from the given node. If the node was not found it returns -1.
 * */
int FindNodeInCycle(const Node* node, const vector<Edge*>& cycle) {
    for (int i = 0; i < cycle.size(); i++) {
        if (cycle[i]->GetFromNode() == node) {
            return i;
        }
    } 

    return -1;


}

/*
 *  Function that rearranges the edges in cycle, such that the cycle starts from
 *  the given node. This function recreates the cycle in place such that when exiting
 *  this function 'cycle' will be updated to the new order of edges.
 * */
void WalkCurrentCycle(const Node* node, vector<Edge*>* cycle) {
    cout << "[WalkCurrentCycle] Enter.\n";
    if (!cycle->size()) {
        return;
    }

    vector<Edge*> aux_cycle = *cycle;
    cycle->clear();
    int found = FindNodeInCycle(node, aux_cycle);
    for (int i = found; i < aux_cycle.size(); i++) {
        cycle->push_back(aux_cycle[i]);
    }

    for (int i = 0; i < found; i++) {
        cycle->push_back(aux_cycle[i]);
    }
}

/*
 *  Function that gets the next edge that was not visited starting from the
 *  given node. If all edges starting from that node are visited, then it
 *  returns nullptr.
 * */
Edge* GetNextEdge(Node* node) {
    for (auto e : node->GetEdges()) {
        if (!e->IsVisited()) {
            e->SetVisited();
            cout << "[GetNextEdge] Return edge " << e->GetFromNode()->GetData() << "->"
                << e->GetToNode()->GetData() << endl;
            return e;
        }
    }

    cout << "[GetNextEdge] Returns nullptr.\n";
    return nullptr;
}

/*
 * Function that starts traversing the graph from the given node and walks through 
 * it until it gets stuck in a cycle. This function takes care of first walking
 * through the previous found cycle.
 * */
void CreateCycle(Node* start_node, vector<Edge*>* curr_cycle) {
    cout << "[CreateCycle] Enter CreateCycle starting from node " << start_node->GetData() << endl; 
    Node* node = start_node;
    WalkCurrentCycle(node, curr_cycle);
    
    Edge* edge = GetNextEdge(node);

    while (edge != nullptr) {
        curr_cycle->push_back(edge);
        node = edge->GetToNode();
        edge = GetNextEdge(node);
    }
}

/*
 *  Returns a node from cycle that still has edges that were not visited.
 * */
Node* GetNonFinishedNode(const vector<Edge*>& cycle) {
    for (auto e : cycle) {
        if (e->GetFromNode()->GetVisitedNum() != e->GetFromNode()->GetFanOut()) {
            return e->GetFromNode();
        }
    }

    return nullptr;
}

void RemoveExtraEdge(vector<Edge*>* cycle, deBruijnGraph graph) {
    for (int i = 0; i < cycle->size(); i++) {
        if ((*cycle)[i]->GetFromNode()->GetData() == graph.GetFromExtraEdge() &&
            (*cycle)[i]->GetToNode()->GetData() == graph.GetToExtraEdge()) {
            cycle->erase(cycle->begin() + i);
            return;
        }
    }
}

/*
 * Function that implements the algorithm for finding an Eulerian cycle in a 
 * deBruijn graph.
 * */
vector<Edge*> FindEulerianCycle(deBruijnGraph& graph) {
    cout << "[FindEulerianCycle] Enter FindEulerianCycle\n";
    vector<Edge*> cycle;

    Node* current_node = graph.GetFirstNode();
    cout << "Current node = " << current_node->GetData() << endl;
    CreateCycle(current_node, &cycle);

    while(graph.GetNumEdges() != cycle.size()) {
        current_node = GetNonFinishedNode(cycle);
        CreateCycle(current_node, &cycle);
    }
   
    RemoveExtraEdge(&cycle, graph);
    return cycle;
}

}  // namespace euler
