#include <iostream>
#include <fstream>
#include <string>

#include "euler.h"

using namespace std;

void Usage() {
    cout << "Usage:\n./genome_sequencer --input_file=<input_file> [--output_file=<output_file>]\n";
}

int ParseInput(int argc, char* argv[], string* input, string* output) {
    if (argc == 1 || argc > 3) {
        cout << "Error: Invalid number of arguments.\n";
        Usage();
        return -1;
    }

    string aux;
    aux = argv[1];
        
    if (aux == "--help") {
        Usage();
        return -1;
    }

    auto found = aux.find("--input_file");
    if (found == string::npos) {
        cout << "Error: input file not found.\n";
        Usage();
        return -1;
    }

    *input = aux.substr(found + 13, aux.length() - 13);

    if (argc == 3) {
        aux = argv[2];

        found = aux.find("--output_file");
        if (found == string::npos) {
            cout << "Error: 3rd argument should be --output_file.\n";
            Usage();
            return -1;
        }
        
        *output = aux.substr(found + 14, aux.length() - 14);
    } else {
        *output = "output_genome.txt";
    }
    
    return 0;
}

int main(int argc, char* argv[]) {
    string input, output;

    int rc = ParseInput(argc, argv, &input, &output);
    if (rc != 0) {
        return 1;
    }
    
    ifstream in(input);
    ofstream out(output);

    deBruijnGraph graph;
    vector<Edge*> eulerian_cycle;

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
    eulerian_cycle = euler::FindEulerianCycle(graph);

    string genome;
    int start = 0;
    for (; start < eulerian_cycle.size(); start++) {
        string prefix = eulerian_cycle[start]->GetFromNode()->GetData();
        if (prefix == graph.GetToExtraEdge()) {
            genome = prefix;
            break;
        }
    }

    for (int i = 0; i < eulerian_cycle.size(); i++) {
        int index = (start + i) % eulerian_cycle.size();
        string suffix = eulerian_cycle[index]->GetToNode()->GetData();
        genome += suffix[suffix.length() - 1];
    }

    out << genome;

    return 1;
}
