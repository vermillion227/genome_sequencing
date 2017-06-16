#include <string>
#include <vector>
#include <map>

using namespace std;

namespace graph {

class Node;

/*
 *  Class that defines an edge of the de Bruijn graph.
 *
 * */
class Edge {
    public:
        Edge();
        Edge(const shared_ptr<Node>& from_node, const shared_ptr<Node>& to_node);
        ~Edge();

        void SetVisited();
        bool IsVisited();
        Node* GetToNode();
        Node* GetFromNode();

    private:
        shared_ptr<Node> from_node;
        shared_ptr<Node> to_node;
        bool visited_;
}

/*
 *  Class that defines a node in a graph. The type of the data contained in this
 *  graph will be std::string, since for this problem strings are the main data.
 *
 * */
class Node {
    public:
        Node();
        Node(const string& data, const long id);
        ~Node();

        string    GetData();
        void      SetData(const string& data);
        void      IncVisitedNum();
        void      IncFanOut();
        void      IncFanIn();
        int       GetVisitedNum();
        int       GetFanOut();
        int       GetFanOut();
        void      InsertEdge(const shared_ptr<Node>& node);
        vector<unique_ptr<Edge> > GetEdges();

    private:
        string data_;
        int visited_num;
        int fan_in;
        int fan_out;
        vector<unique_ptr<Edge> > out_edges;
};

/*
 *  Class that defines a graph that has the properties of a deBruijn graph.
 *
 * */
class deBruijnGraph {
    public:
        deBruijnGraph();
        ~deBruijnGraph();

        void AddComponent(const string& data_1, const string& data_2);
        void BalanceGraph();
        long GetNumEdges();
        Node* GetFirstNode();

    private:
        void AddNode(const string& data);

        map<string, shared_ptr<Node> > nodes_map;
        long num_edges;
};

}  // namespace graph
