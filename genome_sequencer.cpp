#include <iostream>
#include <fstream>
#include <string>

#include "euler.h"

using namespace std;

int main(int argc, char* args[]) {
    ifstream in(args[1]);
    ofstream out("output.txt");

    deBruijnGraph graph;

    vector<string> comp;
    string aux;
    while(in >> aux) {
        comp.push_back(aux);
    }

    for (auto s : comp) {
        string prefix = s.substr(0, s.length() - 1);
        string suffix = s.substr(1, s.length() - 1);

        graph.AddComponent(prefix, suffix);
    }

    graph.BalanceGraph();

    return 1;
}
