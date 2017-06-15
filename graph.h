#include <string>
#include <vector>
#include <map>

using namespace std;


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

        string    getData();
        void      setData(const string& data);
        long      getId();
        void      setId(const long id);

    private:
        string data_;
        long id_;
};

/*
 *  Class that defines a graph that has the properties of a deBruijn graph.
 *
 * */
class deBruijnGraph {
    public:
        deBruijnGraph();
        ~deBruijnGraph();

        void AddComponent(const string& key_1, const string& key_2);

    private:
        map<string, Node> nodes_;
        map<string, vector<string> > adjacency_list;
        long num_nodes;
};
